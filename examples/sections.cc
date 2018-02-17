#include <iostream>
#include <inttypes.h> // PRIx64 
#include "../elf_parser.h"

void print_sections(std::vector<elf_parser::section_t> &sections);

int main(int argc, char* argv[]) {
    char usage_banner[] = "usage: ./sections [<executable>]\n";
    if(argc < 2) {
        std::cerr << usage_banner;
        return -1;
    }

    std::string program((std::string)argv[1]);
    elf_parser::Elf_parser elf_parser(program);

    std::vector<elf_parser::section_t> secs = elf_parser.get_sections();
    print_sections(secs);
    return 0;
}

void print_sections(std::vector<elf_parser::section_t> &sections) {
    printf("  [Nr] %-16s %-16s %-16s %s\n", "Name", "Type", "Address", "Offset");
    printf("       %-16s %-16s %5s\n",
                    "Size", "EntSize", "Align");
    
    for (auto &section : sections) {
        printf("  [%2d] %-16s %-16s %016" PRIx64 " %08" PRIx64 "\n", 
            section.section_index,
            section.section_name.c_str(),
            section.section_type.c_str(),
            section.section_addr, 
            section.section_offset);

        printf("       %016zx %016" PRIx64 " %5" PRIu64 "\n",
            section.section_size, 
            section.section_ent_size,
            section.section_addr_align);
    }
}