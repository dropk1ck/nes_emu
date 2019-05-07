#ifndef __MAPPER_H
#define __MAPPER_H

#include "types.hh"

class Mapper {
public:
    Mapper(u8 *);
    ~Mapper();
    virtual u8 readMem(u16) = 0;

protected:
    u8 *rom;
    u8 *prg;
    u32 prgSize;
    u32 chrSize;
};

#endif