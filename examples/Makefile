

all: sections symbols segments relocations test1

sections: sections.cc 
	g++ -o sections sections.cc -std=gnu++11 

symbols: symbols.cc 
	g++ -o symbols symbols.cc -std=gnu++11 

segments: segments.cc 
	g++ -o segments segments.cc -std=gnu++11 

relocations: relocations.cc 
	g++ -o relocations relocations.cc -std=gnu++11 

test1: tests/test1.cc 
	g++ -o tests/test1 tests/test1.cc -std=gnu++11 -g

clean:
	rm -f sections symbols segments relocations tests/test1