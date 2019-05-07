#ifndef __DISASM_H
#define __DISASM_H

#include "types.hh"
#include <string>

using std::string;

enum AddressMode {
    acc,        // accumulator
    ab,         // absolute
    abX,        // absolute, X-indexed
    abY,        // absolute, Y-indexed
    imm,        // immediate
    imp,        // implied
    ind,        // indirect
    inX,        // X-indexed, indirect
    inY,        // Y-indexed, indirect
    rel,        // relative
    zpg,        // zeropage
    zpX,        // zeropage, X-indexed
    zpY,        // zeropage, Y-indexed
    und         // undefined instruction
};

typedef struct insn_props {
    string opcode;
    int bytes;
    AddressMode addrMode; 
} insn_props;

typedef struct insn {
    string opcode;
    string operands;
    int size;
} insn;

insn *disasm(u8 *);

#endif