#include "cartridge.hh"
#include "log.hh"
#include "mapper0.hh"
#include "types.hh"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#define NES_MAGIC_HEADER "NES\x1a"

namespace Cartridge {

Mapper *mapper = NULL;

void load(const char *fname)
{
    FILE* f = fopen(fname, "rb");
    if (f == NULL) {
        log_error("can't open ROM file %s: %s", fname, strerror(errno));
        exit(-1);
    }

    fseek(f, 0, SEEK_END);
    int romsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (romsize < 16) {
        log_info("ROM file is less than 16 bytes, impossile!");
        exit(-1);
    }

    u8 *rom = new u8[romsize];
    fread(rom, romsize, 1, f);
    fclose(f);

    if (strncmp((const char *)rom, NES_MAGIC_HEADER, 4) != 0) {
        log_info("ROM file has wrong magic header for INES file");
        exit(-1);
    }

    int mapperNum = (rom[7] & 0xF0) | (rom[6] >> 4);

    // short-circuit for now
    mapperNum = 0;

    if (mapper != NULL) {
        delete mapper;
    }

    switch (mapperNum) {
        case 0:
            mapper = new Mapper0(rom);
            break; 
        default:
            break;
    }

}

u8 readMem(u16 addr)
{
    if (!mapper) {
        log_error("attempted to read from cartridge before loaded");
        exit(-1);
    }
    return mapper->readMem(addr);
}

} // namespace Cartridge