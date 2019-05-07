#ifndef __MAPPER0_H
#define __MAPPER0_H

#include "mapper.hh"
#include "types.hh"

class Mapper0 : public Mapper {
public:
    Mapper0(u8 *rom) : Mapper(rom) { }

    u8 readMem(u16 addr)
    {
        return rom[addr-0x8000+16];
    }
};

#endif