#include "disasm.hh"
#include "types.hh"
#include <cstdio>

#define INV {"UND",0,und}

// instruction property table
insn_props insn_table[] = {
    {"BRK",1,imp},      // 00
    {"ORA",2,ind},      // 01
    INV,                // 02
    INV,                // 03
    INV,                // 04
    {"ORA",2,zpg},      // 05
    {"ASL",2,zpg},      // 06
    INV,                // 07
    {"PHP",1,imp},      // 08
    {"ORA",2,imm},      // 09
    {"ASL",2,acc},      // 0a
    INV,                // 0b
    INV,                // 0c
    {"ORA",3,ab},       // 0d
    {"ASL",3,ab},       // 0e
    INV,                // 0f
    {"BPL",2,rel},      // 10
    {"ORA",2,inY},      // 11
    INV,                // 12
    INV,                // 13
    INV,                // 14
    {"ORA",2,zpX},      // 15
    {"ASL",2,zpX},      // 16
    INV,                // 17
    {"CLC",1,imp},      // 18
    {"ORA",3,abY},      // 19
    INV,                // 1a
    INV,                // 1b
    INV,                // 1c
    {"ORA",3,abX},      // 1d
    {"ASL",3,abX},      // 1e
    INV,                // 1f
    {"JSR",3,ab},       // 20
    {"AND",2,ind},      // 21
    INV,                // 22
    INV,                // 23
    {"BIT",2,zpg},      // 24
    {"AND",2,zpg},      // 25
    {"ROL",2,zpg},      // 26
    INV,                // 27
    {"PLP",1,imp},      // 28
    {"AND",2,imm},      // 29
    {"ROL",1,acc},      // 2a
    INV,                // 2b
    {"BIT",3,ab},       // 2c
    {"AND",3,ab},       // 2d
    {"ROL",3,ab},       // 2e
    INV,                // 2f
    {"BMI",2,rel},      // 30
    {"AND",2,inY},      // 31
    INV,                // 32
    INV,                // 33
    INV,                // 34
    {"AND",2,zpX},      // 35
    {"ROL",2,zpX},      // 36
    INV,                // 37
    {"SEC",1,imp},      // 38
    {"AND",3,abY},      // 39
    INV,                // 3a
    INV,                // 3b
    INV,                // 3c
    {"AND",3,abX},      // 3d
    {"ROL",3,abX},      // 3e
    INV,                // 3f
    {"RTI",1,imp},      // 40
    {"EOR",2,inX},      // 41
    INV,                // 42
    INV,                // 43
    INV,                // 44
    {"EOR",2,zpg},      // 45
    {"LSL",2,zpg},      // 46
    INV,                // 47
    {"PHA",1,imp},      // 48
    {"EOR",2,imm},      // 49
    {"LSR",1,acc},      // 4a
    INV,                // 4b
    {"JMP",3,ab},       // 4c
    {"EOR",3,ab},       // 4d
    {"LSR",3,ab},       // 4e
    INV,                // 4f
    {"BVC",2,rel},      // 50
    {"EOR",2,inY},      // 51
    INV,                // 52
    INV,                // 53
    INV,                // 54
    {"EOR",2,zpX},      // 55
    {"LSR",2,zpX},      // 56
    INV,                // 57
    {"CLI",1,imp},      // 58
    {"EOR",3,abY},      // 59
    INV,                // 5a
    INV,                // 5b
    INV,                // 5c
    {"EOR",3,abX},      // 5d
    {"LSR",3,abX},      // 5e
    INV,                // 5f
    {"RTS",1,imp},      // 60
    {"ADC",2,ind},      // 61
    INV,                // 62
    INV,                // 63
    INV,                // 64
    {"ADC",2,zpg},      // 65
    {"ROR",2,zpg},      // 66
    INV,                // 67
    {"PLA",1,imp},      // 68
    {"ADC",2,imm},      // 69
    {"ROR",1,acc},      // 6a
    INV,                // 6b
    {"JMP",3,ind},      // 6c
    {"ADC",3,ab},       // 6d
    {"ROR",3,ab},       // 6e
    INV,                // 6f
    {"BVS",2,rel},      // 70
    {"ADC",2,inY},      // 71
    INV,                // 72
    INV,                // 73
    INV,                // 74
    {"ADC",2,zpX},      // 75
    {"ROR",2,zpX},      // 76
    INV,                // 77
    {"SEI",1,imp},      // 78
    {"ADC",3,abY},      // 79
    INV,                // 7a
    INV,                // 7b
    INV,                // 7c
    {"ADC",3,abX},      // 7d
    {"ROR",3,abX},      // 7e
    INV,                // 7f
    INV,                // 80
    {"STA",2,ind},      // 81
    INV,                // 82
    INV,                // 83
    {"STY",2,zpg},      // 84
    {"STA",2,zpg},      // 85
    {"STX",2,zpg},      // 86
    INV,                // 87
    {"DEY",1,imp},      // 88
    INV,                // 89
    {"TXA",1,imp},      // 8a
    INV,                // 8b
    {"STY",3,ab},       // 8c
    {"STA",3,ab},       // 8d
    {"STX",3,ab},       // 8e
    INV,                // 8f
    {"BCC",2,rel},      // 90
    {"STA",2,inY},      // 91
    INV,                // 92
    INV,                // 93
    {"STY",2,zpX},      // 94
    {"STA",2,zpX},      // 95
    {"STX",2,zpY},      // 96
    INV,                // 97
    {"TYA",1,imp},      // 98
    {"STA",3,abY},      // 99
    {"TXS",1,imp},      // 9a
    INV,                // 9b
    INV,                // 9c
    {"STA",3,abX},      // 9d
    INV,                // 9e
    INV,                // 9f
    {"LDY",2,imm},      // a0
    {"LDA",2,ind},      // a1
    {"LDX",2,imm},      // a2
    INV,                // a3
    {"LDY",2,zpg},      // a4
    {"LDA",2,zpg},      // a5
    {"LDX",2,zpg},      // a6
    INV,                // a7
    {"TAY",1,imp},      // a8
    {"LDA",2,imm},      // a9
    {"TAX",1,imp},      // aa
    INV,                // ab
    {"LDY",3,ab},       // ac
    {"LDA",3,ab},       // ad
    {"LDX",3,ab},       // ae
    INV,                // af
    {"BCS",2,rel},      // b0
    {"LDA",2,inY},      // b1
    INV,                // b2
    INV,                // b3
    {"LDY",2,zpX},      // b4
    {"LDA",2,zpX},      // b5
    {"LDX",2,zpY},      // b6
    INV,                // b7
    {"CLV",1,imp},      // b8
    {"LDA",3,abY},      // b9
    {"TSX",1,imp},      // ba
    INV,                // bb
    {"LDY",3,abX},      // bc
    {"LDA",3,abX},      // bd
    {"LDX",3,abY},      // be
    INV,                // bf
    {"CPY",2,imm},      // c0
    {"CMP",2,inX},      // c1
    INV,                // c2
    INV,                // c3
    {"CPY",2,zpg},      // c4
    {"CMP",2,zpg},      // c5
    {"DEC",2,zpg},      // c6
    INV,                // c7
    {"INY",1,imp},      // c8
    {"CMP",2,imm},      // c9
    {"DEX",1,imp},      // ca
    INV,                // cb
    {"CPY",3,ab},       // cc
    {"CMP",3,ab},       // cd
    {"DEC",3,ab},       // ce
    INV,                // cf
    {"BNE",2,rel},      // d0
    {"CMP",2,inY},      // d1
    INV,                // d2
    INV,                // d3
    INV,                // d4
    {"CMP",2,zpX},      // d5
    {"DEC",2,zpX},      // d6
    INV,                // d7
    {"CLD",1,imp},      // d8
    {"CMP",3,abY},      // d9
    INV,                // da
    INV,                // db
    INV,                // dc
    {"CMP",3,abX},      // dd
    {"DEC",3,abX},      // de
    INV,                // df
    {"CPX",2,imm},      // e0
    {"SBC",2,ind},      // e1
    INV,                // e2
    INV,                // e3
    {"CPX",2,zpg},      // e4
    {"SBC",2,zpg},      // e5
    {"INC",2,zpg},      // e6
    INV,                // e7
    {"INX",1,imp},      // e8
    {"SBC",2,imm},      // e9
    {"NOP",1,imp},      // ea
    INV,                // eb
    {"CPX",3,ab},       // ec
    {"SBC",3,ab},       // ed
    {"INC",3,ab},       // ee
    INV,                // ef
    {"BEQ",2,rel},      // f0
    {"SBC",2,inY},      // f1
    INV,                // f2
    INV,                // f3
    INV,                // f4
    {"SBC",2,zpX},      // f5
    {"INC",2,zpX},      // f6
    INV,                // f7
    {"SED",1,imp},      // f8
    {"SBC",3,abY},      // f9
    INV,                // fa
    INV,                // fb
    INV,                // fc
    {"SBC",3,abX},      // fd
    {"INC",3,abX},      // fe
    INV                 // ff
};

// disassembles one instruction from the byte stream pointed to by 'code'
// returns a pointer to insn struct 
insn *disasm(u8 *code)
{
    char buf[64];
    u8 op = *code;
    insn *i = new insn;
    if (insn_table[op].opcode == "UND") {
        i->opcode = "INVALID";
        i->size = 1;
        i->operands = "";
        return i;
    }
    
    i->opcode = insn_table[op].opcode;
    i->size = insn_table[op].bytes;
    switch (insn_table[op].addrMode) {
        case acc:
            i->operands = "A";
            break;
        case ab:
            snprintf(buf, sizeof(buf), "$%02X%02X", *(code+2), *(code+1));
            i->operands = buf;
            break;
        case abX:
            snprintf(buf, sizeof(buf), "$%02X%02X,X", *(code+2), *(code+1));
            i->operands = buf;
            break;
        case abY:
            snprintf(buf, sizeof(buf), "$%02X%02X,Y", *(code+2), *(code+1));
            i->operands = buf;
            break;
        case imm:
            snprintf(buf, sizeof(buf), "$%02X", *(code+1));
            i->operands = buf;
            break;
        case imp:
            i->operands = "";
            break;
        case ind:
            snprintf(buf, sizeof(buf), "($%02X%02X)", *(code+2), *(code+1));
            i->operands = buf;
            break;
        case inX:
            snprintf(buf, sizeof(buf), "($%02X,X)", *(code+1));
            i->operands = buf;
            break;
        case inY:
            snprintf(buf, sizeof(buf), "($%02X),Y", *(code+1));
            i->operands = buf;
            break;
        case rel:
            snprintf(buf, sizeof(buf), "$%02X", *(code+1));
            i->operands = buf;
            break;
        case zpg:
            snprintf(buf, sizeof(buf), "$%02X", *(code+1));
            i->operands = buf;
            break;
        case zpX:
            snprintf(buf, sizeof(buf), "$%02X,X", *(code+1));
            i->operands = buf;
            break;
        case zpY:
            snprintf(buf, sizeof(buf), "$%02X,Y", *(code+1));
            i->operands = buf;
            break;
        default:
            break;
    }

    return i;
}
