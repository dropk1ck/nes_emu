#ifndef __CPU_H
#define __CPU_H

#include "types.hh"

#define FLAG_CARRY     0x01
#define FLAG_ZERO      0x02
#define FLAG_INTERRUPT 0x04
#define FLAG_DECIMAL   0x08
#define FLAG_BREAK     0x10
#define FLAG_CONSTANT  0x20
#define FLAG_OVERFLOW  0x40
#define FLAG_SIGN      0x80

#define STACK_PAGE 0x100

#define INT_RESET 0x1

namespace CPU {

// declarations
void power();
u8 getA();
u8 getX();
u8 getY();
u8 getS();
u8 getP();
u16 getPC();
u8 readMem(u16);

};

#endif