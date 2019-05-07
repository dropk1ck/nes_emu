#include "disasm.hh"
#include "log.hh"
#include "types.hh"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        log_error("Provide a ROM filename!");
        exit(-1);
    }

    int c;
    bool skipHdr = true;

    while ((c = getopt(argc, argv, "d")) != -1) {
        switch (c) {
            case 'd':
                skipHdr = false;
                break;
            default:
                break;
        }
    }
    char *fname = argv[optind];
    FILE* f = fopen(fname, "rb");
    if (f == NULL) {
        log_error("can't open ROM file %s: %s", fname, strerror(errno));
        exit(-1);
    }

    fseek(f, 0, SEEK_END);
    int romsize = ftell(f);
    if (skipHdr) {
        fseek(f, 16, SEEK_SET);
    }
    else {
        fseek(f, 0, SEEK_SET);
    }

    u8 *rom = new u8[romsize];
    fread(rom, romsize, 1, f);
    fclose(f);

    int idx = 0;
    while (idx < romsize) {
        insn *i = disasm(&rom[idx]);
        if (i != NULL) {
            printf("%s %s\n", i->opcode.c_str(), i->operands.c_str());
            idx += i->size;
            delete i;
        }
    }

    return 0;
}