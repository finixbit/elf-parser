CXXFLAGS = -std=gnu++11 -Wall -Wextra -fmax-errors=5
PROGRAMS = sections symbols segments relocations

all: $(PROGRAMS)

%: %.cc elf_parser.o
	$(CXX) -o $@ $@.cc elf_parser.o $(CXX_FLAGS)

elf_parser.o: ../elf_parser.hpp ../elf_parser.cpp
	$(CXX) -c -o $@ ../elf_parser.cpp $(CXX_FLAGS)

clean:
	rm -f $(PROGRAMS)
	rm -f elf_parser.o
