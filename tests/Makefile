CXXFLAGS = -Wall -Wextra -fmax-errors=1 -O0 -g -I.. -std=c++11 -I../elf-parser
OBJECTS = elf_parser.o main.o compare.o move_semantics.o

all: unit
	$(MAKE) -C ../examples
	./unit
unit: $(OBJECTS) 
	$(CXX) -o unit $(OBJECTS) $(CXXFLAGS)
elf_parser.o: ../elf_parser.hpp ../elf_parser.cpp
	$(CXX) -c -o $@ ../elf_parser.cpp $(CXX_FLAGS)
clean:
	rm -f $(OBJECTS)
