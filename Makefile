CC		  = clang
CXX       = clang++
CLFAGS    = 
CXXFLAGS  = -std=c++11 -Wall -Iinclude
LDFLAGS   = -lncurses
BINS      = nesemu nesdisasm
OBJS      = cpu.o main.o cartridge.o mapper.o disasm.o nesdisasm.o

all: $(BINS)
debug: CXXFLAGS += -DDEBUG_BUILD -g
debug: CFLAGS += -g
debug: nesemu 

nesemu: cpu.cc main.cc cartridge.cc mapper.cc disasm.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

nesdisasm: nesdisasm.cc disasm.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(BINS)

