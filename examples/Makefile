

all: sections symbols segments relocations

sections: sections.cc 
	g++ -o sections sections.cc ../elf_parser.cpp -std=gnu++11 

symbols: symbols.cc 
	g++ -o symbols symbols.cc ../elf_parser.cpp -std=gnu++11 

segments: segments.cc 
	g++ -o segments segments.cc ../elf_parser.cpp -std=gnu++11 

relocations: relocations.cc 
	g++ -o relocations relocations.cc ../elf_parser.cpp -std=gnu++11 

clean:
	rm -f sections symbols segments relocations