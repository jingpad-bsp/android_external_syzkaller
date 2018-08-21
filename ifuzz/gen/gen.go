// Copyright 2017 syzkaller project authors. All rights reserved.
// Use of this source code is governed by Apache 2 LICENSE that can be found in the LICENSE file.

// gen generates instruction tables (ifuzz/insns.go) from Intel XED tables.
// Tables used to generate insns.go are checked in in all-enc-instructions.txt.
package main

import (
	"bufio"
	"fmt"
	"os"
	"reflect"
	"strconv"
	"strings"

	"github.com/google/syzkaller/ifuzz"
)

func main() {
	if len(os.Args) != 2 {
		failf("usage: gen instructions.txt")
	}
	f, err := os.Open(os.Args[1])
	if err != nil {
		failf("failed to open input file: %v", err)
	}
	defer f.Close()

	skipped := 0
	saved := ""
	var insns []*ifuzz.Insn
	var insn, insn1 *ifuzz.Insn
	s := bufio.NewScanner(f)
	for i := 1; s.Scan(); i++ {
		reportError := func(msg string, args ...interface{}) {
			fmt.Fprintf(os.Stderr, "line %v: %v\n", i, s.Text())
			failf(msg, args...)
		}
		line := s.Text()
		if comment := strings.IndexByte(line, '#'); comment != -1 {
			line = line[:comment]
		}
		line = strings.TrimSpace(line)
		if line == "" {
			continue
		}
		if line[len(line)-1] == '\\' {
			saved += line[:len(line)-1]
			continue
		}
		line = saved + line
		saved = ""
		if line == "{" {
			insn = new(ifuzz.Insn)
			continue
		}
		if line == "}" {
			if insn1 != nil {
				insns = append(insns, insn1)
				insn1 = nil
				insn = nil
			}
			continue
		}
		colon := strings.IndexByte(line, ':')
		if colon == -1 {
			reportError("no colon")
		}
		name := strings.TrimSpace(line[:colon])
		if name == "" {
			reportError("empty attribute name")
		}
		var vals []string
		for _, v := range strings.Split(line[colon+1:], " ") {
			v = strings.TrimSpace(v)
			if v == "" {
				continue
			}
			vals = append(vals, v)
		}
		switch name {
		case "ICLASS":
			if len(vals) != 1 {
				reportError("ICLASS has more than one value")
			}
			insn.Name = vals[0]
		case "CPL":
			if len(vals) != 1 {
				reportError("CPL has more than one value")
			}
			if vals[0] != "0" && vals[0] != "3" {
				reportError("unknown CPL value: %v", vals[0])
			}
			insn.Priv = vals[0] == "0"
		case "EXTENSION":
			if len(vals) != 1 {
				reportError("EXTENSION has more than one value")
			}
			insn.Extension = vals[0]
			switch insn.Extension {
			case "FMA", "AVX2", "AVX", "F16C", "BMI2", "BMI", "XOP", "FMA4", "AVXAES", "BMI1", "AVX2GATHER":
				insn.Mode = 1<<ifuzz.ModeLong64 | 1<<ifuzz.ModeProt32
			}
			insn.Avx2Gather = insn.Extension == "AVX2GATHER"
		case "PATTERN":
			if insn1 != nil {
				insns = append(insns, insn1)
			}
			insn1 = new(ifuzz.Insn)
			*insn1 = *insn
			if err := parsePattern(insn1, vals); err != nil {
				if _, ok := err.(errSkip); !ok {
					reportError(err.Error())
				}
				if err.Error() != "" {
					fmt.Fprintf(os.Stderr, "skipping %v on line %v (%v)\n", insn.Name, i, err)
				}
				skipped++
				insn1 = nil
			}
		case "OPERANDS":
			if insn1 == nil {
				break
			}
			if err := parseOperands(insn1, vals); err != nil {
				if _, ok := err.(errSkip); !ok {
					reportError(err.Error())
				}
				if err.Error() != "" {
					fmt.Fprintf(os.Stderr, "skipping %v on line %v (%v)\n", insn.Name, i, err)
				}
				skipped++
				insn1 = nil
			}
		}
	}

	var deduped []*ifuzz.Insn
nextInsn:
	for i, insn := range insns {
		mod0 := insn.Mod
		for j := 0; j < i; j++ {
			insn1 := insns[j]
			if insn.Mod == 3 && insn1.Mod == -3 || insn.Mod == -3 && insn1.Mod == 3 {
				insn.Mod = insn1.Mod
			}
			if reflect.DeepEqual(insn, insn1) {
				if insn.Mod != mod0 {
					insn1.Mod = -1
				}
				continue nextInsn
			}
			insn.Mod = mod0
		}
		deduped = append(deduped, insn)
	}
	fmt.Fprintf(os.Stderr, "deduped %v instructions\n", len(insns)-len(deduped))
	insns = deduped

	fmt.Printf("// AUTOGENERATED FILE\n")
	fmt.Printf("package ifuzz\n\n")
	fmt.Printf("var Insns = []*Insn{\n")
	for _, insn := range insns {
		if insn.Extension == "AVX512VEX" || insn.Extension == "AVX512EVEX" {
			skipped++
			continue
		}

		text := fmt.Sprintf("%#v", insn)
		text = strings.Replace(text, "ifuzz.Insn", "Insn", -1)
		text = strings.Replace(text, ", generator:(func(*ifuzz.Config, *rand.Rand) []uint8)(nil)", "", -1)
		fmt.Printf("	%v,\n", text)
	}
	fmt.Printf("}\n")

	fmt.Fprintf(os.Stderr, "handled %v, skipped %v\n", len(insns), skipped)
}

type errSkip string

func (err errSkip) Error() string {
	return string(err)
}

func parsePattern(insn *ifuzz.Insn, vals []string) error {
	if insn.Opcode != nil {
		return fmt.Errorf("PATTERN is already parsed for the instruction")
	}
	// As spelled these have incorrect format for 16-bit addressing mode and with 67 prefix.
	if insn.Name == "NOP5" || insn.Name == "NOP6" || insn.Name == "NOP7" || insn.Name == "NOP8" || insn.Name == "NOP9" {
		return errSkip("")
	}
	if insn.Mode == 0 {
		insn.Mode = 1<<ifuzz.ModeLast - 1
	}
	insn.Mod = -100
	insn.Reg = -100
	insn.Rm = -100
	insn.VexP = -1
	for _, v := range vals {
		switch {
		case strings.HasPrefix(v, "0x"):
			op, err := strconv.ParseUint(v, 0, 8)
			if err != nil {
				return fmt.Errorf("failed to parse hex pattern: %v", v)
			}
			if !insn.Modrm {
				insn.Opcode = append(insn.Opcode, byte(op))
			} else {
				insn.Suffix = append(insn.Suffix, byte(op))
			}
		case strings.HasPrefix(v, "0b"):
			if len(v) != 8 || v[6] != '_' {
				return fmt.Errorf("failed to parse bin pattern: %v", v)
			}
			var op byte
			if v[2] == '1' {
				op |= 1 << 7
			}
			if v[3] == '1' {
				op |= 1 << 6
			}
			if v[4] == '1' {
				op |= 1 << 5
			}
			if v[5] == '1' {
				op |= 1 << 4
			}
			if v[7] == '1' {
				op |= 1 << 3
			}
			insn.Opcode = append(insn.Opcode, op)
		case strings.HasPrefix(v, "MOD["):
			insn.Modrm = true
			vv, err := parseModrm(v[3:])
			if err != nil {
				return fmt.Errorf("failed to parse %v: %v", v, err)
			}
			insn.Mod = vv
		case strings.HasPrefix(v, "REG["):
			insn.Modrm = true
			vv, err := parseModrm(v[3:])
			if err != nil {
				return fmt.Errorf("failed to parse %v: %v", v, err)
			}
			insn.Reg = vv
		case strings.HasPrefix(v, "RM["):
			insn.Modrm = true
			vv, err := parseModrm(v[2:])
			if err != nil {
				return fmt.Errorf("failed to parse %v: %v", v, err)
			}
			insn.Rm = vv
		case v == "RM=4":
			insn.Rm = 4
		case strings.HasPrefix(v, "SRM["):
			vv, err := parseModrm(v[3:])
			if err != nil {
				return fmt.Errorf("failed to parse %v: %v", v, err)
			}
			insn.Rm = vv
			insn.Srm = true
		case v == "SRM=0", v == "SRM!=0":
		case v == "MOD!=3":
			if !insn.Modrm || insn.Mod != -1 {
				return fmt.Errorf("MOD!=3 without MOD")
			}
			insn.Mod = -3
		case v == "MOD=3":
			// Most other instructions contain "MOD[0b11] MOD=3",
			// but BNDCL contains "MOD[mm] MOD=3"
			insn.Mod = 3
		case v == "MOD=0":
			insn.Mod = 0
		case v == "MOD=1":
			insn.Mod = 1
		case v == "MOD=2":
			insn.Mod = 2
		case v == "MODRM()":
		case v == "lock_prefix":
			insn.Prefix = append(insn.Prefix, 0xF0)
		case v == "nolock_prefix":

		// Immediates.
		case v == "UIMM8()", v == "SIMM8()":
			addImm(insn, 1)
		case v == "UIMM16()":
			addImm(insn, 2)
		case v == "UIMM32()":
			addImm(insn, 4)
		case v == "SIMMz()":
			addImm(insn, -1)
		case v == "UIMMv()":
			addImm(insn, -3)
		case v == "UIMM8_1()":
			addImm(insn, 1)
		case v == "BRDISP8()":
			addImm(insn, 1)
		case v == "BRDISP32()":
			addImm(insn, 4)
		case v == "BRDISPz()":
			addImm(insn, -1)
		case v == "MEMDISPv()":
			addImm(insn, -2)

		// VOP/VEX
		case v == "XOPV":
			insn.Vex = 0x8f
			insn.Mode &^= 1 << ifuzz.ModeReal16
		case v == "EVV":
			insn.Vex = 0xc4
		case v == "VV1":
			insn.Vex = 0xc4
		case v == "VMAP0":
			insn.VexMap = 0
		case v == "V0F":
			insn.VexMap = 1
		case v == "V0F38":
			insn.VexMap = 2
		case v == "V0F3A":
			insn.VexMap = 3
		case v == "XMAP8":
			insn.VexMap = 8
		case v == "XMAP9":
			insn.VexMap = 9
		case v == "XMAPA":
			insn.VexMap = 10
		case v == "VNP":
			insn.VexP = 0
		case v == "V66":
			insn.VexP = 1
		case v == "VF2":
			insn.VexP = 3
		case v == "VF3":
			insn.VexP = 2
		case v == "VL128", v == "VL=0":
			insn.VexL = -1
		case v == "VL256", v == "VL=1":
			insn.VexL = 1
		case v == "VL512":
			// VL=2
		case v == "NOVSR":
			insn.VexNoR = true
		case v == "NOEVSR":
			insn.VexNoR = true
			// VEXDEST3=0b1 VEXDEST210=0b111 VEXDEST4=0b0
		case v == "SE_IMM8()":
			addImm(insn, 1)
		case v == "VMODRM_XMM()":
		case v == "VMODRM_YMM()":
		case v == "BCRC=0":
		case v == "BCRC=1":
		case v == "ESIZE_8_BITS()":
		case v == "ESIZE_16_BITS()":
		case v == "ESIZE_32_BITS()":
		case v == "ESIZE_64_BITS()":
		case v == "NELEM_GPR_WRITER_STORE()":
		case v == "NELEM_GPR_WRITER_STORE_BYTE()":
		case v == "NELEM_GPR_WRITER_STORE_WORD()":
		case v == "NELEM_GPR_WRITER_LDOP_Q()":
		case v == "NELEM_GPR_WRITER_LDOP_D()":
		case v == "NELEM_GPR_READER()":
		case v == "NELEM_GPR_READER_BYTE()":
		case v == "NELEM_GPR_READER_WORD()":
		case v == "NELEM_GSCAT()":
		case v == "NELEM_HALF()":
		case v == "NELEM_FULL()":
		case v == "NELEM_FULLMEM()":
		case v == "NELEM_QUARTERMEM()":
		case v == "NELEM_EIGHTHMEM()":
		case v == "NELEM_HALFMEM()":
		case v == "NELEM_QUARTERMEM()":
		case v == "NELEM_MEM128()":
		case v == "NELEM_SCALAR()":
		case v == "NELEM_TUPLE1()":
		case v == "NELEM_TUPLE2()":
		case v == "NELEM_TUPLE4()":
		case v == "NELEM_TUPLE8()":
		case v == "NELEM_TUPLE1_4X()":
		case v == "NELEM_TUPLE1_BYTE()":
		case v == "NELEM_TUPLE1_WORD()":
		case v == "NELEM_MOVDDUP()":
		case v == "UISA_VMODRM_XMM()":
		case v == "UISA_VMODRM_YMM()":
		case v == "UISA_VMODRM_ZMM()":
		case v == "MASK=0":
		case v == "FIX_ROUND_LEN128()":
		case v == "FIX_ROUND_LEN512()":
		case v == "AVX512_ROUND()":
		case v == "ZEROING=0":
		case v == "SAE()":

		// Modes
		case v == "mode64":
			insn.Mode &= 1 << ifuzz.ModeLong64
		case v == "not64":
			insn.Mode &^= 1 << ifuzz.ModeLong64
		case v == "mode32":
			insn.Mode &= 1 << ifuzz.ModeProt32
		case v == "mode16":
			insn.Mode &= 1<<ifuzz.ModeProt16 | 1<<ifuzz.ModeReal16
		case v == "eamode64":
		case v == "eamode32":
		case v == "eamode16":
		case v == "eanot16":

		case v == "no_refining_prefix":
			insn.NoRepPrefix = true
			insn.No66Prefix = true
		case v == "no66_prefix":
			insn.No66Prefix = true
		case v == "not_refining_f3":
		case v == "f2_refining_prefix", v == "refining_f2", v == "repne", v == "REP=2":
			insn.Prefix = append(insn.Prefix, 0xF2)
			insn.NoRepPrefix = true
		case v == "f3_refining_prefix", v == "refining_f3", v == "repe", v == "REP=3":
			insn.Prefix = append(insn.Prefix, 0xF3)
			insn.NoRepPrefix = true
		case v == "norep", v == "not_refining", v == "REP=0":
			insn.NoRepPrefix = true
		case v == "osz_refining_prefix":
			insn.Prefix = append(insn.Prefix, 0x66)
			insn.NoRepPrefix = true
		case v == "rexw_prefix", v == "W1":
			insn.Rexw = 1
		case v == "norexw_prefix", v == "W0":
			insn.Rexw = -1
		case v == "MPXMODE=1", v == "MPXMODE=0":
		case v == "TZCNT=1", v == "TZCNT=0":
		case v == "LZCNT=1", v == "LZCNT=0":
		case v == "CR_WIDTH()":
		case v == "DF64()":
		case v == "IMMUNE_REXW()":
		case v == "FORCE64()":
		case v == "eosz32", v == "eosz64":
			insn.No66Prefix = true
		case v == "EOSZ=1", v == "EOSZ!=1", v == "EOSZ=2", v == "EOSZ!=2", v == "EOSZ=3", v == "EOSZ!=3":
		case v == "BRANCH_HINT()":
		case v == "P4=1", v == "P4=0":
		case v == "rexb_prefix", v == "norexb_prefix":
		case strings.HasPrefix(v, "MODEP5="):
		case v == "IMMUNE66()", v == "REFINING66()", v == "IGNORE66()", v == "IMMUNE66_LOOP64()":
		case v == "OVERRIDE_SEG0()", v == "OVERRIDE_SEG1()", v == "REMOVE_SEGMENT()":
		case v == "ONE()":
		default:
			return errSkip(fmt.Sprintf("unknown pattern %v", v))
		}
	}
	if insn.Modrm {
		switch insn.Mod {
		case -3, -1, 0, 1, 2, 3:
		default:
			return fmt.Errorf("bad MOD value: %v", insn.Mod)
		}
		if insn.Reg < -1 || insn.Reg > 7 {
			return fmt.Errorf("bad REG value: %v", insn.Mod)
		}
		if insn.Rm < -1 || insn.Rm > 7 {
			return fmt.Errorf("bad RM value: %v", insn.Mod)
		}
	}
	if insn.Imm != 0 && len(insn.Suffix) != 0 {
		return fmt.Errorf("both immediate and suffix opcode")
	}
	if insn.Mode == 0 {
		return errSkip("no modes for instruction")
	}
	return nil
}

func parseOperands(insn *ifuzz.Insn, vals []string) error {
	for _, v := range vals {
		switch v {
		case "REG0=SEG():r", "REG1=SEG():r", "REG0=SEG():w":
			if insn.Reg != -1 {
				return fmt.Errorf("REG=SEG() operand, but fixed reg")
			}
			insn.Reg = -6
		case "REG0=CR_R():w", "REG1=CR_R():r":
			if insn.Reg != -1 {
				return fmt.Errorf("REG=CR_R() operand, but fixed reg")
			}
			insn.Reg = -8
			insn.NoSibDisp = true
		case "REG0=DR_R():w", "REG1=DR_R():r":
			insn.NoSibDisp = true
		case "MEM0:r:mem16", "MEM0:w:mem16", "MEM0:r:mem16int", "MEM0:w:mem16int":
			insn.Mem16 = true
		case "MEM0:r:mem32real", "MEM0:r:mem32int", "MEM0:w:mem32real", "MEM0:w:mem32int":
			insn.Mem32 = true
		}
	}
	return nil
}

func parseModrm(v string) (int8, error) {
	if len(v) < 4 || len(v) > 7 || v[0] != '[' || v[len(v)-1] != ']' {
		return 0, fmt.Errorf("malformed")
	}
	if v == "[mm]" || v == "[rrr]" || v == "[nnn]" {
		return -1, nil
	}
	if !strings.HasPrefix(v, "[0b") {
		return 0, fmt.Errorf("malformed")
	}
	var vv int8
	for i := 3; i < len(v)-1; i++ {
		if v[i] != '0' && v[i] != '1' {
			return 0, fmt.Errorf("malformed")
		}
		vv *= 2
		if v[i] == '1' {
			vv += 1
		}
	}
	return vv, nil
}

func addImm(insn *ifuzz.Insn, imm int8) {
	if insn.Imm == 0 {
		insn.Imm = imm
		return
	}
	if insn.Imm2 == 0 {
		insn.Imm2 = imm
		return
	}
	panic("too many immediates")
}

func failf(msg string, args ...interface{}) {
	fmt.Fprintf(os.Stderr, msg+"\n", args...)
	os.Exit(1)
}
