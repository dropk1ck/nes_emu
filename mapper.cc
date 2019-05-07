#include "mapper.hh"
#include "types.hh"

Mapper::Mapper(u8 *rom)
{
    this->rom = rom;
    this->prg = rom + 16;
    this->prgSize = rom[4] * 0x4000;
    this->chrSize = rom[5] * 0x2000;
}

Mapper::~Mapper()
{
    delete rom;
}