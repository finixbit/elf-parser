#include <iostream>
#include <inttypes.h> // PRIx64 
#include "../elf_parser.h"

void print_segments(std::vector<Elf_parser::segment_t> &segments);

int main(int argc, char* argv[]) {
    char usage_banner[] = "usage: ./sections [<executable>]\n";
    if(argc < 2) {
        std::cerr << usage_banner;
        return -1;
    }

    std::string program((std::string)argv[1]);
    Elf_parser::Elf_parser elf_parser(program);

    std::vector<Elf_parser::segment_t> segs = elf_parser.get_segments();
    print_segments(segs);
    return 0;
}

void print_segments(std::vector<Elf_parser::segment_t> &segments) {
    printf("  %-16s  %-16s   %-16s   %s\n", "Type", "Offset", "VirtAddr", "PhysAddr");
    printf("  %-16s  %-16s   %-16s  %6s %5s\n", " ", "FileSiz", "MemSiz", "Flags", "Align");

    for (auto &segment : segments) {
        printf("   %-16s 0x%016" PRIx64 " 0x%016" PRIx64 " 0x%016" PRIx64 "\n",
                segment.segment_type.c_str(), 
                segment.segment_offset,
                segment.segment_virtaddr, 
                segment.segment_physaddr);
        
        printf("   %-16s 0x%016" PRIx64 " 0x%016" PRIx64 " %-5s %-5" PRIx64 "\n", "",
                segment.segment_filesize, 
                segment.segment_memsize,
                segment.segment_flags.c_str(), 
                segment.segment_align);
    }
}