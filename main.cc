#include "cartridge.hh"
#include "cpu.hh"
#include "disasm.hh"
#include "log.hh"
#include "types.hh"

#include <cstdio>
#include <ncurses.h>

WINDOW* regsWindow;
WINDOW* stackWindow;
WINDOW* codeWindow;
WINDOW* memWindow;
WINDOW* cmdWindow;

void initwindows()
{
    int max_y, max_x;

    initscr();
    cbreak();
    refresh();
    getmaxyx(stdscr, max_y, max_x);

    regsWindow = newwin(20, 25, 0, 0);
    box(regsWindow, 0, 0);
    mvwprintw(regsWindow, 0, 5, "  REGS  ");
    wrefresh(regsWindow);

    stackWindow = newwin(25, 25, 20, 0);
    box(stackWindow, 0, 0);
    mvwprintw(stackWindow, 0, 5, "  STACK  ");
    wrefresh(stackWindow);

    codeWindow = newwin(20, max_x-25, 0, 25);
    box(codeWindow, 0, 0);
    mvwprintw(codeWindow, 0, 5, "  CODE  ");
    wrefresh(codeWindow);

    memWindow = newwin(25, max_x-25, 20, 25);
    box(memWindow, 0, 0);
    mvwprintw(memWindow, 0, 5, "  MEMORY  ");
    wrefresh(memWindow);

    cmdWindow = newwin(max_y-45, max_x, 45, 0);
    box(cmdWindow, 0, 0);
    mvwprintw(cmdWindow, 0, 5, "  SHELL  ");
    wrefresh(cmdWindow);

    return;
}

void updateregs()
{
    mvwprintw(regsWindow, 2, 3, "A:  0x%x", CPU::getA());
    mvwprintw(regsWindow, 3, 3, "X:  0x%x", CPU::getX());
    mvwprintw(regsWindow, 4, 3, "Y:  0x%x", CPU::getY());
    mvwprintw(regsWindow, 5, 3, "S:  0x%04x", STACK_PAGE + CPU::getS());
    mvwprintw(regsWindow, 6, 3, "PC: 0x%04x", CPU::getPC());
    mvwprintw(regsWindow, 7, 3, "P:  0x%x", CPU::getP());

    wrefresh(regsWindow);
}

void updatestack()
{
    // TODO: tune to height of stack window
    u8 stackPtr = CPU::getS();

    // increment stack pointer to begin w/first element of stack
    stackPtr++;
    for (int i=0, pos=0; i < 20; i++, pos++) {
        if (((stackPtr+i)&0xff) == 0) {
            // just break for now
            break;
        }
        u16 addr = STACK_PAGE + stackPtr + i;
        mvwprintw(stackWindow, 2+pos, 3, "0x%04x: 0x%x", addr, CPU::readMem(addr));
    }
    wrefresh(stackWindow);
}

void updatecode()
{
    u16 codePtr = CPU::getPC();
    u8 code[3];

    for (int j = 0; j < 12; j++) {
        code[0] = CPU::readMem(codePtr);
        code[1] = CPU::readMem(codePtr+1);
        code[2] = CPU::readMem(codePtr+2);
        insn *i = disasm(code);
        mvwprintw(codeWindow, 2+j, 3, "0x%04X:  %s %s", codePtr, i->opcode.c_str(), 
            i->operands.c_str());
        codePtr += i->size;
        delete i;
    }
    wrefresh(codeWindow);
}

int main(int argc, char *argv[])
{
    initwindows();

    Cartridge::load("super.nes");
    CPU::power();
    updateregs();
    updatestack();
    updatecode();
    
    getch();
    endwin();

    return 0;
}