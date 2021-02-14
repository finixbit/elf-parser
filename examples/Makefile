CXXFLAGS = -std=gnu++11 -Wall -Wextra
PROGRAMS = sections symbols segments relocations

all: $(PROGRAMS)

%: %.cc
	$(CXX) -o $@ $@.cc ../elf_parser.cpp $(CXX_FLAGS)

clean:
	rm -f $(PROGRAMS)
