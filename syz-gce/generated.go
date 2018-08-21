// AUTOGENERATED FILE

package main

const syzconfig = `


CONFIG_KCOV=y
CONFIG_KCOV_INSTRUMENT_ALL=y
CONFIG_DEBUG_FS=y
CONFIG_DEBUG_INFO=y

CONFIG_KASAN=y
CONFIG_KASAN_INLINE=y
CONFIG_SLAB=y

CONFIG_NAMESPACES=y
CONFIG_USER_NS=y
CONFIG_UTS_NS=y
CONFIG_IPC_NS=y
CONFIG_PID_NS=y
CONFIG_NET_NS=y

CONFIG_LOCKDEP=y
CONFIG_PROVE_LOCKING=y
CONFIG_DEBUG_ATOMIC_SLEEP=y
CONFIG_PROVE_RCU=y
CONFIG_DEBUG_VM=y
CONFIG_DEBUG_VM_VMACACHE=y
CONFIG_DEBUG_VM_RB=y
CONFIG_DEBUG_VM_PGFLAGS=y

CONFIG_RCU_CPU_STALL_TIMEOUT=60

CONFIG_BPF_SYSCALL=y
CONFIG_BPF_JIT=y
CONFIG_BPF_EVENTS=y
CONFIG_NET_CLS_BPF=y
CONFIG_NET_ACT_BPF=y
CONFIG_CGROUP_BPF=y
CONFIG_TUN=y
CONFIG_USERFAULTFD=y
CONFIG_USER_RETURN_NOTIFIER=y
CONFIG_PREEMPT_NOTIFIERS=y
CONFIG_PADATA=y
CONFIG_ASN1=y
CONFIG_AF_KCM=y
CONFIG_KSM=y
CONFIG_TRANSPARENT_HUGEPAGE=y
CONFIG_TRANSPARENT_HUGEPAGE_ALWAYS=y
CONFIG_TRANSPARENT_HUGE_PAGECACHE=y
CONFIG_X86_INTEL_MPX=y
CONFIG_PCI_IOV=y
CONFIG_NF_LOG_COMMON=y
CONFIG_NF_NAT=y
CONFIG_NF_NAT_FTP=y
CONFIG_NF_NAT_IRC=y
CONFIG_NF_NAT_SIP=y
CONFIG_NETFILTER_XT_MARK=y
CONFIG_NETFILTER_XT_TARGET_LOG=y
CONFIG_NETFILTER_XT_NAT=y
CONFIG_NETFILTER_XT_MATCH_ADDRTYPE=y
CONFIG_NF_NAT_IPV4=y
CONFIG_NF_NAT_MASQUERADE_IPV4=y
CONFIG_IP_NF_NAT=y
CONFIG_IP_NF_TARGET_MASQUERADE=y
CONFIG_NF_LOG_IPV6=y
CONFIG_IRDA=y
CONFIG_IRLAN=y
CONFIG_IRCOMM=y
CONFIG_IRDA_ULTRA=y
CONFIG_IRDA_CACHE_LAST_LSAP=y
CONFIG_IRDA_FAST_RR=y
CONFIG_IRDA_DEBUG=y
CONFIG_IRTTY_SIR=y
CONFIG_DONGLE=y
CONFIG_USB_IRDA=y
CONFIG_BT=y
CONFIG_BT_BREDR=y
CONFIG_BT_RFCOMM=y
CONFIG_BT_RFCOMM_TTY=y
CONFIG_BT_BNEP=y
CONFIG_BT_BNEP_MC_FILTER=y
CONFIG_BT_BNEP_PROTO_FILTER=y
CONFIG_BT_HIDP=y
CONFIG_BT_HS=y
CONFIG_BT_LE=y
CONFIG_BT_LEDS=y
CONFIG_BT_INTEL=y
CONFIG_BT_RTL=y
CONFIG_BT_HCIBTUSB=y
CONFIG_BT_HCIBTUSB_RTL=y
CONFIG_STREAM_PARSER=y
CONFIG_NFC=y
CONFIG_NFC_DIGITAL=y
CONFIG_NFC_NCI=y
CONFIG_NFC_NCI_UART=y
CONFIG_NFC_HCI=y
CONFIG_NFC_SHDLC=y
CONFIG_NFC_SIM=y
CONFIG_NFC_FDP=y
CONFIG_SYS_HYPERVISOR=y
CONFIG_HVC_IRQ=y
CONFIG_EFIVAR_FS=y
CONFIG_RPCSEC_GSS_KRB5=y
CONFIG_PAGE_EXTENSION=y
CONFIG_PAGE_POISONING=y
CONFIG_PAGE_POISONING_NO_SANITY=y
CONFIG_CRYPTO_AKCIPHER=y
CONFIG_CRYPTO_KPP=y
CONFIG_CRYPTO_RSA=y
CONFIG_CRYPTO_DH=y
CONFIG_CRYPTO_ECDH=y
CONFIG_CRYPTO_USER=y
CONFIG_CRYPTO_PCRYPT=y
CONFIG_CRYPTO_CRYPTD=y
CONFIG_CRYPTO_MCRYPTD=y
CONFIG_CRYPTO_ABLK_HELPER=y
CONFIG_CRYPTO_SIMD=y
CONFIG_CRYPTO_GLUE_HELPER_X86=y
CONFIG_CRYPTO_CHACHA20POLY1305=y
CONFIG_CRYPTO_CTS=y
CONFIG_CRYPTO_ECB=y
CONFIG_CRYPTO_LRW=y
CONFIG_CRYPTO_PCBC=y
CONFIG_CRYPTO_XTS=y
CONFIG_CRYPTO_KEYWRAP=y
CONFIG_CRYPTO_CMAC=y
CONFIG_CRYPTO_XCBC=y
CONFIG_CRYPTO_VMAC=y
CONFIG_CRYPTO_CRC32C_INTEL=y
CONFIG_CRYPTO_CRC32=y
CONFIG_CRYPTO_CRC32_PCLMUL=y
CONFIG_CRYPTO_CRCT10DIF=y
CONFIG_CRYPTO_POLY1305=y
CONFIG_CRYPTO_POLY1305_X86_64=y
CONFIG_CRYPTO_MD4=y
CONFIG_CRYPTO_MICHAEL_MIC=y
CONFIG_CRYPTO_RMD128=y
CONFIG_CRYPTO_RMD160=y
CONFIG_CRYPTO_RMD256=y
CONFIG_CRYPTO_RMD320=y
CONFIG_CRYPTO_SHA1_SSSE3=y
CONFIG_CRYPTO_SHA256_SSSE3=y
CONFIG_CRYPTO_SHA512_SSSE3=y
CONFIG_CRYPTO_SHA1_MB=y
CONFIG_CRYPTO_SHA256_MB=y
CONFIG_CRYPTO_SHA512_MB=y
CONFIG_CRYPTO_SHA512=y
CONFIG_CRYPTO_SHA3=y
CONFIG_CRYPTO_TGR192=y
CONFIG_CRYPTO_WP512=y
CONFIG_CRYPTO_GHASH_CLMUL_NI_INTEL=y
CONFIG_CRYPTO_AES_X86_64=y
CONFIG_CRYPTO_AES_NI_INTEL=y
CONFIG_CRYPTO_ANUBIS=y
CONFIG_CRYPTO_BLOWFISH=y
CONFIG_CRYPTO_BLOWFISH_COMMON=y
CONFIG_CRYPTO_BLOWFISH_X86_64=y
CONFIG_CRYPTO_CAMELLIA=y
CONFIG_CRYPTO_CAMELLIA_X86_64=y
CONFIG_CRYPTO_CAMELLIA_AESNI_AVX_X86_64=y
CONFIG_CRYPTO_CAMELLIA_AESNI_AVX2_X86_64=y
CONFIG_CRYPTO_CAST_COMMON=y
CONFIG_CRYPTO_CAST5=y
CONFIG_CRYPTO_CAST5_AVX_X86_64=y
CONFIG_CRYPTO_CAST6=y
CONFIG_CRYPTO_CAST6_AVX_X86_64=y
CONFIG_CRYPTO_DES3_EDE_X86_64=y
CONFIG_CRYPTO_FCRYPT=y
CONFIG_CRYPTO_KHAZAD=y
CONFIG_CRYPTO_SALSA20=y
CONFIG_CRYPTO_SALSA20_X86_64=y
CONFIG_CRYPTO_CHACHA20=y
CONFIG_CRYPTO_CHACHA20_X86_64=y
CONFIG_CRYPTO_SEED=y
CONFIG_CRYPTO_SERPENT=y
CONFIG_CRYPTO_SERPENT_SSE2_X86_64=y
CONFIG_CRYPTO_SERPENT_AVX_X86_64=y
CONFIG_CRYPTO_SERPENT_AVX2_X86_64=y
CONFIG_CRYPTO_TEA=y
CONFIG_CRYPTO_TWOFISH=y
CONFIG_CRYPTO_TWOFISH_COMMON=y
CONFIG_CRYPTO_TWOFISH_X86_64=y
CONFIG_CRYPTO_TWOFISH_X86_64_3WAY=y
CONFIG_CRYPTO_TWOFISH_AVX_X86_64=y
CONFIG_CRYPTO_DEFLATE=y
CONFIG_CRYPTO_LZO=y
CONFIG_CRYPTO_842=y
CONFIG_CRYPTO_LZ4=y
CONFIG_CRYPTO_LZ4HC=y
CONFIG_CRYPTO_ANSI_CPRNG=y
CONFIG_CRYPTO_DRBG_HASH=y
CONFIG_CRYPTO_DRBG_CTR=y
CONFIG_CRYPTO_USER_API=y
CONFIG_CRYPTO_USER_API_HASH=y
CONFIG_CRYPTO_USER_API_SKCIPHER=y
CONFIG_CRYPTO_USER_API_RNG=y
CONFIG_CRYPTO_USER_API_AEAD=y
CONFIG_CRYPTO_DEV_PADLOCK=y
CONFIG_CRYPTO_DEV_PADLOCK_AES=y
CONFIG_CRYPTO_DEV_PADLOCK_SHA=y
CONFIG_CRYPTO_DEV_CCP=y
CONFIG_CRYPTO_DEV_CCP_DD=y
CONFIG_CRYPTO_DEV_CCP_CRYPTO=y
CONFIG_CRYPTO_DEV_QAT=y
CONFIG_CRYPTO_DEV_QAT_DH895xCC=y
CONFIG_CRYPTO_DEV_QAT_C3XXX=y
CONFIG_CRYPTO_DEV_QAT_C62X=y
CONFIG_CRYPTO_DEV_QAT_DH895xCCVF=y
CONFIG_CRYPTO_DEV_QAT_C3XXXVF=y
CONFIG_CRYPTO_DEV_QAT_C62XVF=y
CONFIG_CRYPTO_DEV_VIRTIO=y
CONFIG_KVM_MMIO=y
CONFIG_KVM_ASYNC_PF=y
CONFIG_KVM_VFIO=y
CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT=y
CONFIG_KVM_COMPAT=y
CONFIG_KVM=y
CONFIG_KVM_INTEL=y
CONFIG_KVM_AMD=y
CONFIG_KVM_DEVICE_ASSIGNMENT=y
CONFIG_CRC_ITU_T=y
CONFIG_842_COMPRESS=y
CONFIG_842_DECOMPRESS=y
CONFIG_LZ4_COMPRESS=y
CONFIG_LZ4HC_COMPRESS=y
CONFIG_RADIX_TREE_MULTIORDER=y
CONFIG_CLZ_TAB=y
CONFIG_MPILIB=y
CONFIG_XEN=y
CONFIG_XEN_DOM0=y
CONFIG_XEN_PVHVM=y
CONFIG_XEN_512GB=y
CONFIG_XEN_SAVE_RESTORE=y
CONFIG_XEN_PVH=y
CONFIG_PCI_XEN=y
CONFIG_XEN_PCIDEV_FRONTEND=y
CONFIG_XEN_BLKDEV_FRONTEND=y
CONFIG_XEN_NETDEV_FRONTEND=y
CONFIG_INPUT_XEN_KBDDEV_FRONTEND=y
CONFIG_HVC_XEN=y
CONFIG_HVC_XEN_FRONTEND=y
CONFIG_XEN_FBDEV_FRONTEND=y
CONFIG_XEN_BALLOON=y
CONFIG_XEN_SCRUB_PAGES=y
CONFIG_XEN_DEV_EVTCHN=y
CONFIG_XEN_BACKEND=y
CONFIG_XENFS=y
CONFIG_XEN_COMPAT_XENFS=y
CONFIG_XEN_SYS_HYPERVISOR=y
CONFIG_XEN_XENBUS_FRONTEND=y
CONFIG_XEN_GNTDEV=y
CONFIG_XEN_GRANT_DEV_ALLOC=y
CONFIG_SWIOTLB_XEN=y
CONFIG_XEN_PCIDEV_BACKEND=y
CONFIG_XEN_PRIVCMD=y
CONFIG_XEN_ACPI_PROCESSOR=y
CONFIG_XEN_MCE_LOG=y
CONFIG_XEN_EFI=y
CONFIG_XEN_AUTO_XLATE=y
CONFIG_XEN_ACPI=y
CONFIG_XEN_SYMS=y
CONFIG_X86_X2APIC=y
CONFIG_PARAVIRT_DEBUG=y
CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS=y
CONFIG_NET_KEY=y
CONFIG_NET_KEY_MIGRATE=y
CONFIG_IP_DCCP=y
CONFIG_IP_DCCP_CCID3=y
CONFIG_IP_SCTP=y
CONFIG_RDS=y
CONFIG_RDS_TCP=y
CONFIG_TIPC=y
CONFIG_TIPC_MEDIA_UDP=y
CONFIG_L2TP=y
CONFIG_L2TP_IP=y
CONFIG_VSOCKETS=y
CONFIG_VHOST_VSOCK=y
CONFIG_VIRTIO_VSOCKETS=y
CONFIG_WIMAX=y
CONFIG_EXT4_ENCRYPTION=y
CONFIG_FUSE_FS=y
CONFIG_CUSE=y
CONFIG_OVERLAY_FS=y
CONFIG_HARDENED_USERCOPY=y
CONFIG_ATM=y
CONFIG_ATM_CLIP=y
CONFIG_ATM_LANE=y
CONFIG_ATM_MPOA=y
CONFIG_ATM_BR2684=y
CONFIG_ATM_DRIVERS=y
CONFIG_ATM_TCP=y
CONFIG_USB_ATM=y
CONFIG_LLC=y
CONFIG_LLC2=y
CONFIG_TIPC=y
CONFIG_TIPC_MEDIA_UDP=y
`

const createImageScript = `#!/bin/bash


set -eux

if [ ! -e $1/sbin/init ]; then
	echo "usage: create-gce-image.sh /dir/with/user/space/system /path/to/bzImage /path/to/vmlinux 'image tag'"
	exit 1
fi

if [ "$(basename $2)" != "bzImage" ]; then
	echo "usage: create-gce-image.sh /dir/with/user/space/system /path/to/bzImage /path/to/vmlinux 'image tag'"
	exit 1
fi

if [ "$(basename $3)" != "vmlinux" ]; then
	echo "usage: create-gce-image.sh /dir/with/user/space/system /path/to/bzImage /path/to/vmlinux 'image tag'"
	exit 1
fi

sudo umount disk.mnt || true
sudo qemu-nbd -d /dev/nbd0 || true
rm -rf disk.mnt disk.raw tag obj || true

sudo modprobe nbd
fallocate -l 2G disk.raw
sudo qemu-nbd -c /dev/nbd0 --format=raw disk.raw
mkdir -p disk.mnt
echo -en "o\nn\np\n1\n2048\n\na\n1\nw\n" | sudo fdisk /dev/nbd0
until [ -e /dev/nbd0p1 ]; do sleep 1; done
sudo mkfs.ext4 /dev/nbd0p1
sudo mount /dev/nbd0p1 disk.mnt
sudo cp -a $1/. disk.mnt/.
sudo cp $2 disk.mnt/vmlinuz
sudo sed -i "/^root/ { s/:x:/::/ }" disk.mnt/etc/passwd
echo "T0:23:respawn:/sbin/getty -L ttyS0 115200 vt100" | sudo tee -a disk.mnt/etc/inittab
echo -en "\nauto eth0\niface eth0 inet dhcp\n" | sudo tee -a disk.mnt/etc/network/interfaces
echo "debugfs /sys/kernel/debug debugfs defaults 0 0" | sudo tee -a disk.mnt/etc/fstab
echo "kernel.printk = 7 4 1 3" | sudo tee -a disk.mnt/etc/sysctl.conf
echo "debug.exception-trace = 0" | sudo tee -a disk.mnt/etc/sysctl.conf
echo "net.core.bpf_jit_enable = 1" | sudo tee -a disk.mnt/etc/sysctl.conf
echo "net.core.bpf_jit_harden = 2" | sudo tee -a disk.mnt/etc/sysctl.conf
echo "net.ipv4.ping_group_range = 0 65535" | sudo tee -a disk.mnt/etc/sysctl.conf
echo -en "127.0.0.1\tlocalhost\n" | sudo tee disk.mnt/etc/hosts
echo "nameserver 8.8.8.8" | sudo tee -a disk.mnt/etc/resolve.conf
echo "ClientAliveInterval 420" | sudo tee -a disk.mnt/etc/ssh/sshd_config
echo "syzkaller" | sudo tee disk.mnt/etc/hostname
rm -f key key.pub
ssh-keygen -f key -t rsa -N ""
sudo mkdir -p disk.mnt/root/.ssh
sudo cp key.pub disk.mnt/root/.ssh/authorized_keys
sudo chown root disk.mnt/root/.ssh/authorized_keys
sudo mkdir -p disk.mnt/boot/grub
cat << EOF | sudo tee disk.mnt/boot/grub/grub.cfg
terminal_input console
terminal_output console
set timeout=0
menuentry 'linux' --class gnu-linux --class gnu --class os {
	insmod vbe
	insmod vga
	insmod video_bochs
	insmod video_cirrus
	insmod gzio
	insmod part_msdos
	insmod ext2
	set root='(hd0,1)'
	linux /vmlinuz root=/dev/sda1 console=ttyS0 earlyprintk=serial vsyscall=native rodata=n ftrace_dump_on_oops=orig_cpu oops=panic panic_on_warn=1 panic=86400 kvm-intel.nested=1 kvm-intel.unrestricted_guest=1 kvm-intel.vmm_exclusive=1 kvm-intel.fasteoi=1 kvm-intel.ept=1 kvm-intel.flexpriority=1 kvm-intel.vpid=1 kvm-intel.emulate_invalid_guest_state=1 kvm-intel.eptad=1 kvm-intel.enable_shadow_vmcs=1 kvm-intel.pml=1 kvm-intel.enable_apicv=1
}
EOF
sudo grub-install --boot-directory=disk.mnt/boot --no-floppy /dev/nbd0
sudo umount disk.mnt
rm -rf disk.mnt
sudo qemu-nbd -d /dev/nbd0
tar -Szcf disk.tar.gz disk.raw
mkdir -p obj
cp $3 obj/
echo -n "$4" > tag
tar -czvf image.tar.gz disk.tar.gz key tag obj/vmlinux
rm -rf tag obj
`
