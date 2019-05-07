#ifndef __CARTRIDGE_H
#define __CARTRIDGE_H

#include "types.hh"

namespace Cartridge {

// declared functions
void load(const char *);
u8 readMem(u16);
    
}

#endif