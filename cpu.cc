#include "cartridge.hh"
#include "cpu.hh"
#include "log.hh"
#include "types.hh"

#include <cstring>

#define setcarry() P |= FLAG_CARRY
#define clearcarry() P &= (~FLAG_CARRY)
#define setzero() P |= FLAG_ZERO
#define clearzero() P &= (~FLAG_ZERO)
#define setinterrupt() P |= FLAG_INTERRUPT
#define clearinterrupt() P &= (~FLAG_INTERRUPT)
#define setdecimal() P |= FLAG_DECIMAL
#define cleardecimal() P &= (~FLAG_DECIMAL)
#define setoverflow() P |= FLAG_OVERFLOW
#define clearoverflow() P &= (~FLAG_OVERFLOW)
#define setsign() P |= FLAG_SIGN
#define clearsign() P &= (~FLAG_SIGN)

#define decSP() S = (S-1) & 0xff
#define incSP() S = (S+1) & 0xff

namespace CPU {

// registers
u8 A, X, Y, S, P;
u16 PC;

// internal RAM
u8 ram[0x800];

void interrupt(u8 i)
{
    switch (i) {
        case INT_RESET:
            PC = (u16)Cartridge::readMem(0xFFFC) | ((u16)Cartridge::readMem(0xFFFD) << 8);
            break;
        default:
            break;
    }
}

void power()
{
    A = X = Y = 0;
    S = 0xFD;
    P = 0x34;

    // initialize all RAM to 0x00
    memset(ram, 0x00, sizeof(ram));

    // reset system
    interrupt(INT_RESET);
}

u8 getA()
{
    return A;
}

u8 getX()
{
    return X;
}

u8 getY()
{
    return Y;
}

u8 getS()
{
    return S;
}

u8 getP()
{
    return P;
}

u16 getPC()
{
    return PC;
}

// helper functions
void push8(u8 val)
{
    ram[STACK_PAGE + S] = val;
    decSP();
    if (S == 0xff) {
        log_warning("stack pointer overflow occured during push8");
    }
}

void push16(u16 val)
{
    ram[STACK_PAGE + S] = (val >> 8);
    decSP();
    ram[STACK_PAGE + S] = (val & 0xff);
    decSP();
    if (S == 0xff || S == 0xfe) {
        log_warning("stack pointer overflow occured during push16");
    }
}

u8 pull8()
{
    incSP();
    u8 val = ram[STACK_PAGE + S];
    if (S == 0x00) {
        log_warning("stack underflow occured during pull8");
    }
    return val;
}

u16 pull16()
{
    incSP();
    u16 val = ram[STACK_PAGE + S] & 0xff;
    incSP();
    val |= (ram[STACK_PAGE + S] & 0xff) << 8;
    if (S == 0x00 || S == 0x01) {
        log_warning("stack underflow occured during pull16");
    }
    return val;
}

u8 readMem(u16 addr)
{
    switch (addr) {
        case 0x0000 ... 0x1FFF:
            return ram[addr % 0x800];
        case 0x4018 ... 0xFFFF:
            return Cartridge::readMem(addr);
        default:
            log_warning("reading from address 0x%04x is unimplemented", addr);
            return 0;
    }
}

// instruction handling routines

// clear carry flag
void clc()
{
    clearcarry();
}

// clear decimal flag
void cld()
{
    cleardecimal();
}

// clear interrupt flag
void cli()
{
    clearinterrupt();
}

// clear overflow flag
void clv()
{
    clearoverflow();
}

// push accumulator
void pha()
{
    push8(A);
}

// set carry flag
void sec()
{
    setcarry();
}

// set decimal flag
void sed()
{
    setdecimal();
}

// set interrupt flag
void sei()
{
    setinterrupt();
}

} // namespace CPU 