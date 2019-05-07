CC		  = clang
CXX       = clang++
CLFAGS    = 
CXXFLAGS  = -std=c++11 -Wall -I../include
LDFLAGS   = -lgtest -lgtest_main
BINS      = test_disasm 
OBJS      = test_disasm.o 

all: $(BINS)

test_disasm: test_disasm.cc
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJS) $(BINS)

