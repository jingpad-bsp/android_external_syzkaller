// Copyright 2017 syzkaller project authors. All rights reserved.
// Use of this source code is governed by Apache 2 LICENSE that can be found in the LICENSE file.

// This file is shared between executor and csource package.

// Implementation of syz_kvm_setup_cpu pseudo-syscall.
// See Intel Software Developer’s Manual Volume 3: System Programming Guide
// for details on what happens here.

#include "kvm.S.h"
#include "kvm.h"

#ifndef KVM_SMI
#define KVM_SMI _IO(KVMIO, 0xb7)
#endif

#define CR0_PE 1
#define CR0_MP (1 << 1)
#define CR0_EM (1 << 2)
#define CR0_TS (1 << 3)
#define CR0_ET (1 << 4)
#define CR0_NE (1 << 5)
#define CR0_WP (1 << 16)
#define CR0_AM (1 << 18)
#define CR0_NW (1 << 29)
#define CR0_CD (1 << 30)
#define CR0_PG (1 << 31)

#define CR4_VME 1
#define CR4_PVI (1 << 1)
#define CR4_TSD (1 << 2)
#define CR4_DE (1 << 3)
#define CR4_PSE (1 << 4)
#define CR4_PAE (1 << 5)
#define CR4_MCE (1 << 6)
#define CR4_PGE (1 << 7)
#define CR4_PCE (1 << 8)
#define CR4_OSFXSR (1 << 8)
#define CR4_OSXMMEXCPT (1 << 10)
#define CR4_UMIP (1 << 11)
#define CR4_VMXE (1 << 13)
#define CR4_SMXE (1 << 14)
#define CR4_FSGSBASE (1 << 16)
#define CR4_PCIDE (1 << 17)
#define CR4_OSXSAVE (1 << 18)
#define CR4_SMEP (1 << 20)
#define CR4_SMAP (1 << 21)
#define CR4_PKE (1 << 22)

#define EFER_SCE 1
#define EFER_LME (1 << 8)
#define EFER_LMA (1 << 10)
#define EFER_NXE (1 << 11)
#define EFER_SVME (1 << 12)
#define EFER_LMSLE (1 << 13)
#define EFER_FFXSR (1 << 14)
#define EFER_TCE (1 << 15)

// 32-bit page directory entry bits
#define PDE32_PRESENT 1
#define PDE32_RW (1 << 1)
#define PDE32_USER (1 << 2)
#define PDE32_PS (1 << 7)

// 64-bit page * entry bits
#define PDE64_PRESENT 1
#define PDE64_RW (1 << 1)
#define PDE64_USER (1 << 2)
#define PDE64_ACCESSED (1 << 5)
#define PDE64_DIRTY (1 << 6)
#define PDE64_PS (1 << 7)
#define PDE64_G (1 << 8)

struct tss16 {
	uint16_t prev;
	uint16_t sp0;
	uint16_t ss0;
	uint16_t sp1;
	uint16_t ss1;
	uint16_t sp2;
	uint16_t ss2;
	uint16_t ip;
	uint16_t flags;
	uint16_t ax;
	uint16_t cx;
	uint16_t dx;
	uint16_t bx;
	uint16_t sp;
	uint16_t bp;
	uint16_t si;
	uint16_t di;
	uint16_t es;
	uint16_t cs;
	uint16_t ss;
	uint16_t ds;
	uint16_t ldt;
} __attribute__((packed));

struct tss32 {
	uint16_t prev, prevh;
	uint32_t sp0;
	uint16_t ss0, ss0h;
	uint32_t sp1;
	uint16_t ss1, ss1h;
	uint32_t sp2;
	uint16_t ss2, ss2h;
	uint32_t cr3;
	uint32_t ip;
	uint32_t flags;
	uint32_t ax;
	uint32_t cx;
	uint32_t dx;
	uint32_t bx;
	uint32_t sp;
	uint32_t bp;
	uint32_t si;
	uint32_t di;
	uint16_t es, esh;
	uint16_t cs, csh;
	uint16_t ss, ssh;
	uint16_t ds, dsh;
	uint16_t fs, fsh;
	uint16_t gs, gsh;
	uint16_t ldt, ldth;
	uint16_t trace;
	uint16_t io_bitmap;
} __attribute__((packed));

struct tss64 {
	uint32_t reserved0;
	uint64_t rsp[3];
	uint64_t reserved1;
	uint64_t ist[7];
	uint64_t reserved2;
	uint32_t reserved3;
	uint32_t io_bitmap;
} __attribute__((packed));

static void fill_segment_descriptor(uint64_t* dt, uint64_t* lt, struct kvm_segment* seg)
{
	uint16_t index = seg->selector >> 3;
	uint64_t limit = seg->g ? seg->limit >> 12 : seg->limit;
	uint64_t sd = (limit & 0xffff) | (seg->base & 0xffffff) << 16 | (uint64_t)seg->type << 40 | (uint64_t)seg->s << 44 | (uint64_t)seg->dpl << 45 | (uint64_t)seg->present << 47 | (limit & 0xf0000ULL) << 48 | (uint64_t)seg->avl << 52 | (uint64_t)seg->l << 53 | (uint64_t)seg->db << 54 | (uint64_t)seg->g << 55 | (seg->base & 0xff000000ULL) << 56;
	NONFAILING(dt[index] = sd);
	NONFAILING(lt[index] = sd);
}

static void fill_segment_descriptor_dword(uint64_t* dt, uint64_t* lt, struct kvm_segment* seg)
{
	fill_segment_descriptor(dt, lt, seg);
	uint16_t index = seg->selector >> 3;
	NONFAILING(dt[index + 1] = 0);
	NONFAILING(lt[index + 1] = 0);
}

static void setup_syscall_msrs(int cpufd, uint16_t sel_cs, uint16_t sel_cs_cpl3)
{
	char buf[sizeof(struct kvm_msrs) + 5 * sizeof(struct kvm_msr_entry)];
	memset(buf, 0, sizeof(buf));
	struct kvm_msrs* msrs = (struct kvm_msrs*)buf;
	msrs->nmsrs = 5;
	msrs->entries[0].index = MSR_IA32_SYSENTER_CS;
	msrs->entries[0].data = sel_cs;
	msrs->entries[1].index = MSR_IA32_SYSENTER_ESP;
	msrs->entries[1].data = ADDR_STACK0;
	msrs->entries[2].index = MSR_IA32_SYSENTER_EIP;
	msrs->entries[2].data = ADDR_VAR_SYSEXIT;
	msrs->entries[3].index = MSR_IA32_STAR;
	msrs->entries[3].data = ((uint64_t)sel_cs << 32) | ((uint64_t)sel_cs_cpl3 << 48);
	msrs->entries[4].index = MSR_IA32_LSTAR;
	msrs->entries[4].data = ADDR_VAR_SYSRET;
	ioctl(cpufd, KVM_SET_MSRS, msrs);
}

static void setup_32bit_idt(struct kvm_sregs* sregs, char* host_mem, uintptr_t guest_mem)
{
	sregs->idt.base = guest_mem + ADDR_VAR_IDT;
	sregs->idt.limit = 0x1ff;
	uint64_t* idt = (uint64_t*)(host_mem + sregs->idt.base);
	for (int i = 0; i < 32; i++) {
		struct kvm_segment gate;
		gate.selector = i << 3;
		switch (i % 6) {
		case 0:
			// 16-bit interrupt gate
			gate.type = 6;
			gate.base = SEL_CS16;
			break;
		case 1:
			// 16-bit trap gate
			gate.type = 7;
			gate.base = SEL_CS16;
			break;
		case 2:
			// 16-bit task gate
			gate.type = 3;
			gate.base = SEL_TGATE16;
			break;
		case 3:
			// 32-bit interrupt gate
			gate.type = 14;
			gate.base = SEL_CS32;
			break;
		case 4:
			// 32-bit trap gate
			gate.type = 15;
			gate.base = SEL_CS32;
			break;
		case 6:
			// 32-bit task gate
			gate.type = 11;
			gate.base = SEL_TGATE32;
			break;
		}
		gate.limit = guest_mem + ADDR_VAR_USER_CODE2; // entry offset
		gate.present = 1;
		gate.dpl = 0;
		gate.s = 0;
		gate.g = 0;
		gate.db = 0;
		gate.l = 0;
		gate.avl = 0;
		fill_segment_descriptor(idt, idt, &gate);
	}
}

static void setup_64bit_idt(struct kvm_sregs* sregs, char* host_mem, uintptr_t guest_mem)
{
	sregs->idt.base = guest_mem + ADDR_VAR_IDT;
	sregs->idt.limit = 0x1ff;
	uint64_t* idt = (uint64_t*)(host_mem + sregs->idt.base);
	for (int i = 0; i < 32; i++) {
		struct kvm_segment gate;
		gate.selector = (i * 2) << 3;
		gate.type = (i & 1) ? 14 : 15; // interrupt or trap gate
		gate.base = SEL_CS64;
		gate.limit = guest_mem + ADDR_VAR_USER_CODE2; // entry offset
		gate.present = 1;
		gate.dpl = 0;
		gate.s = 0;
		gate.g = 0;
		gate.db = 0;
		gate.l = 0;
		gate.avl = 0;
		fill_segment_descriptor_dword(idt, idt, &gate);
	}
}

struct kvm_text {
	uintptr_t typ;
	const void* text;
	uintptr_t size;
};

struct kvm_opt {
	uint64_t typ;
	uint64_t val;
};

#define KVM_SETUP_PAGING (1 << 0)
#define KVM_SETUP_PAE (1 << 1)
#define KVM_SETUP_PROTECTED (1 << 2)
#define KVM_SETUP_CPL3 (1 << 3)
#define KVM_SETUP_VIRT86 (1 << 4)
#define KVM_SETUP_SMM (1 << 5)
#define KVM_SETUP_VM (1 << 6)

// syz_kvm_setup_cpu(fd fd_kvmvm, cpufd fd_kvmcpu, usermem vma[24], text ptr[in, array[kvm_text, 1]], ntext len[text], flags flags[kvm_setup_flags], opts ptr[in, array[kvm_setup_opt, 0:2]], nopt len[opts])
static uintptr_t syz_kvm_setup_cpu(uintptr_t a0, uintptr_t a1, uintptr_t a2, uintptr_t a3, uintptr_t a4, uintptr_t a5, uintptr_t a6, uintptr_t a7)
{
	const int vmfd = a0;
	const int cpufd = a1;
	char* const host_mem = (char*)a2;
	const struct kvm_text* const text_array_ptr = (struct kvm_text*)a3;
	const uintptr_t text_count = a4;
	const uintptr_t flags = a5;
	const struct kvm_opt* const opt_array_ptr = (struct kvm_opt*)a6;
	uintptr_t opt_count = a7;

	const uintptr_t page_size = 4 << 10;
	const uintptr_t ioapic_page = 10;
	const uintptr_t guest_mem_size = 24 * page_size;
	const uintptr_t guest_mem = 0;

	if (text_count != 1)
		fail("syz_kvm_setup_cpu: bad text count %d, want 1", text_count);
	int text_type = 0;
	const void* text = 0;
	int text_size = 0;
	NONFAILING(text_type = text_array_ptr[0].typ);
	NONFAILING(text = text_array_ptr[0].text);
	NONFAILING(text_size = text_array_ptr[0].size);

	uintptr_t i;
	for (i = 0; i < guest_mem_size / page_size; i++) {
		struct kvm_userspace_memory_region memreg;
		memreg.slot = i;
		memreg.flags = 0; // can be KVM_MEM_LOG_DIRTY_PAGES | KVM_MEM_READONLY
		memreg.guest_phys_addr = guest_mem + i * page_size;
		if (i == ioapic_page)
			memreg.guest_phys_addr = 0xfec00000;
		memreg.memory_size = page_size;
		memreg.userspace_addr = (uintptr_t)host_mem + i * page_size;
		ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &memreg);
	}
	// SMRAM
	struct kvm_userspace_memory_region memreg;
	memreg.slot = 1 + (1 << 16);
	memreg.flags = 0;
	memreg.guest_phys_addr = 0x30000;
	memreg.memory_size = 64 << 10;
	memreg.userspace_addr = (uintptr_t)host_mem;
	ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &memreg);

	struct kvm_sregs sregs;
	if (ioctl(cpufd, KVM_GET_SREGS, &sregs))
		return -1;

	struct kvm_regs regs;
	memset(&regs, 0, sizeof(regs));
	regs.rip = guest_mem + ADDR_TEXT;
	regs.rsp = ADDR_STACK0;

	if (opt_count > 2)
		opt_count = 2;
	for (i = 0; i < opt_count; i++) {
		uint64_t typ = 0;
		uint64_t val = 0;
		NONFAILING(typ = opt_array_ptr[i].typ);
		NONFAILING(val = opt_array_ptr[i].val);
		switch (typ) {
		case 1:
			sregs.cr0 ^= val & (CR0_MP | CR0_EM | CR0_ET | CR0_NE | CR0_WP | CR0_AM | CR0_NW | CR0_CD);
			break;
		case 2:
			sregs.cr4 ^= val & (CR4_VME | CR4_PVI | CR4_TSD | CR4_DE | CR4_MCE | CR4_PGE | CR4_PCE |
					    CR4_OSFXSR | CR4_OSXMMEXCPT | CR4_UMIP | CR4_VMXE | CR4_SMXE | CR4_FSGSBASE | CR4_PCIDE |
					    CR4_OSXSAVE | CR4_SMEP | CR4_SMAP | CR4_PKE);
			break;
		case 3:
			sregs.efer ^= val & (EFER_SCE | EFER_NXE | EFER_SVME | EFER_LMSLE | EFER_FFXSR | EFER_TCE);
			break;
		case 4:
			regs.rflags ^= val & ((1 << 8) | (1 << 9) | (1 << 10) | (1 << 12) | (1 << 13) | (1 << 14) |
					      (1 << 15) | (1 << 18) | (1 << 19) | (1 << 20) | (1 << 21));
			break;
		}
	}
	regs.rflags |= 2; // bit 1 is always set

	sregs.gdt.base = guest_mem + ADDR_GDT;
	sregs.gdt.limit = 256 * sizeof(uint64_t) - 1;
	uint64_t* gdt = (uint64_t*)(host_mem + sregs.gdt.base);

	struct kvm_segment seg_ldt;
	seg_ldt.selector = SEL_LDT;
	seg_ldt.type = 2;
	seg_ldt.base = guest_mem + ADDR_LDT;
	seg_ldt.limit = 256 * sizeof(uint64_t) - 1;
	seg_ldt.present = 1;
	seg_ldt.dpl = 0;
	seg_ldt.s = 0;
	seg_ldt.g = 0;
	seg_ldt.db = 1;
	seg_ldt.l = 0;
	uint64_t* ldt = (uint64_t*)(host_mem + sregs.ldt.base);
	fill_segment_descriptor(gdt, ldt, &seg_ldt);
	sregs.ldt = seg_ldt;

	struct kvm_segment seg_cs16;
	seg_cs16.selector = SEL_CS16;
	seg_cs16.type = 11;
	seg_cs16.base = 0;
	seg_cs16.limit = 0xfffff;
	seg_cs16.present = 1;
	seg_cs16.dpl = 0;
	seg_cs16.s = 1;
	seg_cs16.g = 0;
	seg_cs16.db = 0;
	seg_cs16.l = 0;
	fill_segment_descriptor(gdt, ldt, &seg_cs16);

	struct kvm_segment seg_ds16 = seg_cs16;
	seg_ds16.selector = SEL_DS16;
	seg_ds16.type = 3;
	fill_segment_descriptor(gdt, ldt, &seg_ds16);

	struct kvm_segment seg_cs16_cpl3 = seg_cs16;
	seg_cs16_cpl3.selector = SEL_CS16_CPL3;
	seg_cs16_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_cs16_cpl3);

	struct kvm_segment seg_ds16_cpl3 = seg_ds16;
	seg_ds16_cpl3.selector = SEL_DS16_CPL3;
	seg_ds16_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_ds16_cpl3);

	struct kvm_segment seg_cs32 = seg_cs16;
	seg_cs32.selector = SEL_CS32;
	seg_cs32.db = 1;
	fill_segment_descriptor(gdt, ldt, &seg_cs32);

	struct kvm_segment seg_ds32 = seg_ds16;
	seg_ds32.selector = SEL_DS32;
	seg_ds32.db = 1;
	fill_segment_descriptor(gdt, ldt, &seg_ds32);

	struct kvm_segment seg_cs32_cpl3 = seg_cs32;
	seg_cs32_cpl3.selector = SEL_CS32_CPL3;
	seg_cs32_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_cs32_cpl3);

	struct kvm_segment seg_ds32_cpl3 = seg_ds32;
	seg_ds32_cpl3.selector = SEL_DS32_CPL3;
	seg_ds32_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_ds32_cpl3);

	struct kvm_segment seg_cs64 = seg_cs16;
	seg_cs64.selector = SEL_CS64;
	seg_cs64.l = 1;
	fill_segment_descriptor(gdt, ldt, &seg_cs64);

	struct kvm_segment seg_ds64 = seg_ds32;
	seg_ds64.selector = SEL_DS64;
	fill_segment_descriptor(gdt, ldt, &seg_ds64);

	struct kvm_segment seg_cs64_cpl3 = seg_cs64;
	seg_cs64_cpl3.selector = SEL_CS64_CPL3;
	seg_cs64_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_cs64_cpl3);

	struct kvm_segment seg_ds64_cpl3 = seg_ds64;
	seg_ds64_cpl3.selector = SEL_DS64_CPL3;
	seg_ds64_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_ds64_cpl3);

	struct kvm_segment seg_tss32;
	seg_tss32.selector = SEL_TSS32;
	seg_tss32.type = 9;
	seg_tss32.base = ADDR_VAR_TSS32;
	seg_tss32.limit = 0x1ff;
	seg_tss32.present = 1;
	seg_tss32.dpl = 0;
	seg_tss32.s = 0;
	seg_tss32.g = 0;
	seg_tss32.db = 0;
	seg_tss32.l = 0;
	fill_segment_descriptor(gdt, ldt, &seg_tss32);

	struct kvm_segment seg_tss32_2 = seg_tss32;
	seg_tss32_2.selector = SEL_TSS32_2;
	seg_tss32_2.base = ADDR_VAR_TSS32_2;
	fill_segment_descriptor(gdt, ldt, &seg_tss32_2);

	struct kvm_segment seg_tss32_cpl3 = seg_tss32;
	seg_tss32_cpl3.selector = SEL_TSS32_CPL3;
	seg_tss32_cpl3.base = ADDR_VAR_TSS32_CPL3;
	fill_segment_descriptor(gdt, ldt, &seg_tss32_cpl3);

	struct kvm_segment seg_tss32_vm86 = seg_tss32;
	seg_tss32_vm86.selector = SEL_TSS32_VM86;
	seg_tss32_vm86.base = ADDR_VAR_TSS32_VM86;
	fill_segment_descriptor(gdt, ldt, &seg_tss32_vm86);

	struct kvm_segment seg_tss16 = seg_tss32;
	seg_tss16.selector = SEL_TSS16;
	seg_tss16.base = ADDR_VAR_TSS16;
	seg_tss16.limit = 0xff;
	seg_tss16.type = 1;
	fill_segment_descriptor(gdt, ldt, &seg_tss16);

	struct kvm_segment seg_tss16_2 = seg_tss16;
	seg_tss16_2.selector = SEL_TSS16_2;
	seg_tss16_2.base = ADDR_VAR_TSS16_2;
	seg_tss16_2.dpl = 0;
	fill_segment_descriptor(gdt, ldt, &seg_tss16_2);

	struct kvm_segment seg_tss16_cpl3 = seg_tss16;
	seg_tss16_cpl3.selector = SEL_TSS16_CPL3;
	seg_tss16_cpl3.base = ADDR_VAR_TSS16_CPL3;
	seg_tss16_cpl3.dpl = 3;
	fill_segment_descriptor(gdt, ldt, &seg_tss16_cpl3);

	struct kvm_segment seg_tss64 = seg_tss32;
	seg_tss64.selector = SEL_TSS64;
	seg_tss64.base = ADDR_VAR_TSS64;
	seg_tss64.limit = 0x1ff;
	fill_segment_descriptor_dword(gdt, ldt, &seg_tss64);

	struct kvm_segment seg_tss64_cpl3 = seg_tss64;
	seg_tss64_cpl3.selector = SEL_TSS64_CPL3;
	seg_tss64_cpl3.base = ADDR_VAR_TSS64_CPL3;
	seg_tss64_cpl3.dpl = 3;
	fill_segment_descriptor_dword(gdt, ldt, &seg_tss64_cpl3);

	struct kvm_segment seg_cgate16;
	seg_cgate16.selector = SEL_CGATE16;
	seg_cgate16.type = 4;
	seg_cgate16.base = SEL_CS16 | (2 << 16); // selector + param count
	seg_cgate16.limit = ADDR_VAR_USER_CODE2; // entry offset
	seg_cgate16.present = 1;
	seg_cgate16.dpl = 0;
	seg_cgate16.s = 0;
	seg_cgate16.g = 0;
	seg_cgate16.db = 0;
	seg_cgate16.l = 0;
	seg_cgate16.avl = 0;
	fill_segment_descriptor(gdt, ldt, &seg_cgate16);

	struct kvm_segment seg_tgate16 = seg_cgate16;
	seg_tgate16.selector = SEL_TGATE16;
	seg_tgate16.type = 3;
	seg_cgate16.base = SEL_TSS16_2;
	seg_tgate16.limit = 0;
	fill_segment_descriptor(gdt, ldt, &seg_tgate16);

	struct kvm_segment seg_cgate32 = seg_cgate16;
	seg_cgate32.selector = SEL_CGATE32;
	seg_cgate32.type = 12;
	seg_cgate32.base = SEL_CS32 | (2 << 16); // selector + param count
	fill_segment_descriptor(gdt, ldt, &seg_cgate32);

	struct kvm_segment seg_tgate32 = seg_cgate32;
	seg_tgate32.selector = SEL_TGATE32;
	seg_tgate32.type = 11;
	seg_tgate32.base = SEL_TSS32_2;
	seg_tgate32.limit = 0;
	fill_segment_descriptor(gdt, ldt, &seg_tgate32);

	struct kvm_segment seg_cgate64 = seg_cgate16;
	seg_cgate64.selector = SEL_CGATE64;
	seg_cgate64.type = 12;
	seg_cgate64.base = SEL_CS64;
	fill_segment_descriptor_dword(gdt, ldt, &seg_cgate64);

	int kvmfd = open("/dev/kvm", O_RDWR);
	char buf[sizeof(kvm_cpuid2) + 128 * sizeof(struct kvm_cpuid_entry2)];
	memset(buf, 0, sizeof(buf));
	struct kvm_cpuid2* cpuid = (struct kvm_cpuid2*)buf;
	cpuid->nent = 128;
	ioctl(kvmfd, KVM_GET_SUPPORTED_CPUID, cpuid);
	ioctl(cpufd, KVM_SET_CPUID2, cpuid);
	close(kvmfd);

	const char* text_prefix;
	int text_prefix_size = 0;
	char* host_text = host_mem + ADDR_TEXT;

	if (text_type == 16) {
		if (flags & KVM_SETUP_SMM) {
			if (flags & KVM_SETUP_PROTECTED) {
				sregs.cs = seg_cs16;
				sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds16;
				sregs.cr0 |= CR0_PE;
			} else {
				sregs.cs.selector = 0;
				sregs.cs.base = 0;
			}

			NONFAILING(*(host_mem + ADDR_TEXT) = 0xf4); // hlt for rsm
			host_text = host_mem + 0x8000;

			ioctl(cpufd, KVM_SMI, 0);
		} else if (flags & KVM_SETUP_VIRT86) {
			sregs.cs = seg_cs32;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32;
			sregs.cr0 |= CR0_PE;
			sregs.efer |= EFER_SCE;

			setup_syscall_msrs(cpufd, SEL_CS32, SEL_CS32_CPL3);
			setup_32bit_idt(&sregs, host_mem, guest_mem);

			if (flags & KVM_SETUP_PAGING) {
				uint64_t pd_addr = guest_mem + ADDR_PD;
				uint64_t* pd = (uint64_t*)(host_mem + ADDR_PD);
				// A single 4MB page to cover the memory region
				NONFAILING(pd[0] = PDE32_PRESENT | PDE32_RW | PDE32_USER | PDE32_PS);
				sregs.cr3 = pd_addr;
				sregs.cr4 |= CR4_PSE;

				text_prefix = kvm_asm32_paged_vm86;
				text_prefix_size = sizeof(kvm_asm32_paged_vm86) - 1;
			} else {
				text_prefix = kvm_asm32_vm86;
				text_prefix_size = sizeof(kvm_asm32_vm86) - 1;
			}
		} else if (flags & KVM_SETUP_PROTECTED) {
			sregs.cr0 |= CR0_PE;
			sregs.cs = seg_cs16;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds16;
		} else if (flags & KVM_SETUP_CPL3) {
			sregs.cs = seg_cs16;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds16;

			text_prefix = kvm_asm16_cpl3;
			text_prefix_size = sizeof(kvm_asm16_cpl3) - 1;
		} else {
			sregs.cs.selector = 0;
			sregs.cs.base = 0;
		}
	} else if (text_type == 32) {
		sregs.cr0 |= CR0_PE;
		sregs.efer |= EFER_SCE;

		setup_syscall_msrs(cpufd, SEL_CS32, SEL_CS32_CPL3);
		setup_32bit_idt(&sregs, host_mem, guest_mem);

		if (flags & KVM_SETUP_SMM) {
			sregs.cs = seg_cs32;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32;

			NONFAILING(*(host_mem + ADDR_TEXT) = 0xf4); // hlt for rsm
			host_text = host_mem + 0x8000;

			ioctl(cpufd, KVM_SMI, 0);
		} else if (flags & KVM_SETUP_PAGING) {
			sregs.cs = seg_cs32;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32;

			uint64_t pd_addr = guest_mem + ADDR_PD;
			uint64_t* pd = (uint64_t*)(host_mem + ADDR_PD);
			// A single 4MB page to cover the memory region
			NONFAILING(pd[0] = PDE32_PRESENT | PDE32_RW | PDE32_USER | PDE32_PS);
			sregs.cr3 = pd_addr;
			sregs.cr4 |= CR4_PSE;

			text_prefix = kvm_asm32_paged;
			text_prefix_size = sizeof(kvm_asm32_paged) - 1;
		} else if (flags & KVM_SETUP_CPL3) {
			sregs.cs = seg_cs32_cpl3;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32_cpl3;
		} else {
			sregs.cs = seg_cs32;
			sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32;
		}
	} else {
		sregs.efer |= EFER_LME | EFER_SCE;
		sregs.cr0 |= CR0_PE;

		setup_syscall_msrs(cpufd, SEL_CS64, SEL_CS64_CPL3);
		setup_64bit_idt(&sregs, host_mem, guest_mem);

		sregs.cs = seg_cs32;
		sregs.ds = sregs.es = sregs.fs = sregs.gs = sregs.ss = seg_ds32;

		uint64_t pml4_addr = guest_mem + ADDR_PML4;
		uint64_t* pml4 = (uint64_t*)(host_mem + ADDR_PML4);
		uint64_t pdpt_addr = guest_mem + ADDR_PDP;
		uint64_t* pdpt = (uint64_t*)(host_mem + ADDR_PDP);
		uint64_t pd_addr = guest_mem + ADDR_PD;
		uint64_t* pd = (uint64_t*)(host_mem + ADDR_PD);
		NONFAILING(pml4[0] = PDE64_PRESENT | PDE64_RW | PDE64_USER | pdpt_addr);
		NONFAILING(pdpt[0] = PDE64_PRESENT | PDE64_RW | PDE64_USER | pd_addr);
		NONFAILING(pd[0] = PDE64_PRESENT | PDE64_RW | PDE64_USER | PDE64_PS);
		sregs.cr3 = pml4_addr;
		sregs.cr4 |= CR4_PAE;

		if (flags & KVM_SETUP_VM) {
			sregs.cr0 |= CR0_NE;

			NONFAILING(*((uint64_t*)(host_mem + ADDR_VAR_VMXON_PTR)) = ADDR_VAR_VMXON);
			NONFAILING(*((uint64_t*)(host_mem + ADDR_VAR_VMCS_PTR)) = ADDR_VAR_VMCS);
			NONFAILING(memcpy(host_mem + ADDR_VAR_VMEXIT_CODE, kvm_asm64_vm_exit, sizeof(kvm_asm64_vm_exit) - 1));
			NONFAILING(*((uint64_t*)(host_mem + ADDR_VAR_VMEXIT_PTR)) = ADDR_VAR_VMEXIT_CODE);

			text_prefix = kvm_asm64_init_vm;
			text_prefix_size = sizeof(kvm_asm64_init_vm) - 1;
		} else if (flags & KVM_SETUP_CPL3) {
			text_prefix = kvm_asm64_cpl3;
			text_prefix_size = sizeof(kvm_asm64_cpl3) - 1;
		} else {
			text_prefix = kvm_asm64_enable_long;
			text_prefix_size = sizeof(kvm_asm64_enable_long) - 1;
		}
	}

	NONFAILING(
	    struct tss16* tss = (struct tss16*)(host_mem + seg_tss16_2.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->ss0 = tss->ss1 = tss->ss2 = SEL_DS16;
	    tss->sp0 = tss->sp1 = tss->sp2 = ADDR_STACK0;
	    tss->ip = ADDR_VAR_USER_CODE2;
	    tss->flags = (1 << 1);
	    tss->cs = SEL_CS16;
	    tss->es = tss->ds = tss->ss = SEL_DS16;
	    tss->ldt = SEL_LDT);
	NONFAILING(
	    struct tss16* tss = (struct tss16*)(host_mem + seg_tss16_cpl3.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->ss0 = tss->ss1 = tss->ss2 = SEL_DS16;
	    tss->sp0 = tss->sp1 = tss->sp2 = ADDR_STACK0;
	    tss->ip = ADDR_VAR_USER_CODE2;
	    tss->flags = (1 << 1);
	    tss->cs = SEL_CS16_CPL3;
	    tss->es = tss->ds = tss->ss = SEL_DS16_CPL3;
	    tss->ldt = SEL_LDT);
	NONFAILING(
	    struct tss32* tss = (struct tss32*)(host_mem + seg_tss32_vm86.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->ss0 = tss->ss1 = tss->ss2 = SEL_DS32;
	    tss->sp0 = tss->sp1 = tss->sp2 = ADDR_STACK0;
	    tss->ip = ADDR_VAR_USER_CODE;
	    tss->flags = (1 << 1) | (1 << 17);
	    tss->ldt = SEL_LDT;
	    tss->cr3 = sregs.cr3;
	    tss->io_bitmap = offsetof(struct tss32, io_bitmap));
	NONFAILING(
	    struct tss32* tss = (struct tss32*)(host_mem + seg_tss32_2.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->ss0 = tss->ss1 = tss->ss2 = SEL_DS32;
	    tss->sp0 = tss->sp1 = tss->sp2 = ADDR_STACK0;
	    tss->ip = ADDR_VAR_USER_CODE;
	    tss->flags = (1 << 1);
	    tss->cr3 = sregs.cr3;
	    tss->es = tss->ds = tss->ss = tss->gs = tss->fs = SEL_DS32;
	    tss->cs = SEL_CS32;
	    tss->ldt = SEL_LDT;
	    tss->cr3 = sregs.cr3;
	    tss->io_bitmap = offsetof(struct tss32, io_bitmap));
	NONFAILING(
	    struct tss64* tss = (struct tss64*)(host_mem + seg_tss64.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->rsp[0] = ADDR_STACK0;
	    tss->rsp[1] = ADDR_STACK0;
	    tss->rsp[2] = ADDR_STACK0;
	    tss->io_bitmap = offsetof(struct tss64, io_bitmap));
	NONFAILING(
	    struct tss64* tss = (struct tss64*)(host_mem + seg_tss64_cpl3.base);
	    memset(tss, 0, sizeof(*tss));
	    tss->rsp[0] = ADDR_STACK0;
	    tss->rsp[1] = ADDR_STACK0;
	    tss->rsp[2] = ADDR_STACK0;
	    tss->io_bitmap = offsetof(struct tss64, io_bitmap));

	if (text_size > 1000)
		text_size = 1000;
	if (text_prefix) {
		NONFAILING(memcpy(host_text, text_prefix, text_prefix_size));
		void* patch = 0;
		// Replace 0xbadc0de in LJMP with offset of a next instruction.
		NONFAILING(patch = memmem(host_text, text_prefix_size, "\xde\xc0\xad\x0b", 4));
		if (patch)
			NONFAILING(*((uint32_t*)patch) = guest_mem + ADDR_TEXT + ((char*)patch - host_text) + 6);
		uint16_t magic = PREFIX_SIZE;
		patch = 0;
		NONFAILING(patch = memmem(host_text, text_prefix_size, &magic, sizeof(magic)));
		if (patch)
			NONFAILING(*((uint16_t*)patch) = guest_mem + ADDR_TEXT + text_prefix_size);
	}
	NONFAILING(memcpy((void*)(host_text + text_prefix_size), text, text_size));
	NONFAILING(*(host_text + text_prefix_size + text_size) = 0xf4); // hlt

	NONFAILING(memcpy(host_mem + ADDR_VAR_USER_CODE, text, text_size));
	NONFAILING(*(host_mem + ADDR_VAR_USER_CODE + text_size) = 0xf4); // hlt

	NONFAILING(*(host_mem + ADDR_VAR_HLT) = 0xf4); // hlt
	NONFAILING(memcpy(host_mem + ADDR_VAR_SYSRET, "\x0f\x07\xf4", 3));
	NONFAILING(memcpy(host_mem + ADDR_VAR_SYSEXIT, "\x0f\x35\xf4", 3));

	if (ioctl(cpufd, KVM_SET_SREGS, &sregs))
		return -1;
	if (ioctl(cpufd, KVM_SET_REGS, &regs))
		return -1;
	return 0;
}
