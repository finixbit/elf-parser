#ifndef H_ELF_PARSER
#define H_ELF_PARSER

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>    /* O_RDONLY */
#include <sys/stat.h> /* For the size of the file. , fstat */
#include <sys/mman.h> /* mmap, MAP_PRIVATE */
#include <vector>
#include <elf.h> // Elf64_Shdr
#include <inttypes.h> // PRIx64 
#include <fcntl.h>

namespace Elf_parser {

class Elf_loader {
  public:
    Elf_loader (std::string &program_path): m_program_path{program_path} {   
      load_memory_map();
    }
    void load_memory_map();
    std::string m_program_path; 
    uint8_t *m_mmap_program;
};

void Elf_loader::load_memory_map() {
    int fd, i;
    struct stat st;

    if ((fd = open(m_program_path.c_str(), O_RDONLY)) < 0) {
        printf("Err: open\n");
        exit(-1);
    }
    if (fstat(fd, &st) < 0) {
        printf("Err: fstat\n");
        exit(-1);
    }
    m_mmap_program = static_cast<uint8_t*>(mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0));
    if (m_mmap_program == MAP_FAILED) {
        printf("Err: mmap\n");
        exit(-1);
    }
}


typedef struct {
  int section_index = 0;
  std::string section_name;
  std::string section_type;
  long section_addr;
  std::intptr_t section_offset;
  int section_size;
  int section_ent_size;
  int section_addr_align;
} section_t;


class Elf_section {
  public:
    Elf_section () {}
    static std::vector<section_t> get_sections(Elf_loader &elf_loader);
    static void print_sections(std::vector<section_t> &sections);
    static std::string get_section_type(int tt);
};

std::vector<section_t> Elf_section::get_sections(Elf_loader &elf_loader) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr*)elf_loader.m_mmap_program;
    Elf64_Shdr *shdr = (Elf64_Shdr*)(elf_loader.m_mmap_program + ehdr->e_shoff);
    int shnum = ehdr->e_shnum;

    Elf64_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
    const char *const sh_strtab_p = (char*)elf_loader.m_mmap_program + sh_strtab->sh_offset;

    std::vector<section_t> sections;
    for (int i = 0; i < shnum; ++i) {
        section_t section;
        section.section_index= i;
        section.section_name = std::string(sh_strtab_p + shdr[i].sh_name);
        section.section_type = Elf_section::get_section_type(shdr[i].sh_type);
        section.section_addr = shdr[i].sh_addr;
        section.section_offset = shdr[i].sh_offset;
        section.section_size = shdr[i].sh_size;
        section.section_ent_size = shdr[i].sh_entsize;
        section.section_addr_align = shdr[i].sh_addralign; 
        
        sections.push_back(section);
    }
    return sections;
}

void Elf_section::print_sections(std::vector<section_t> &sections) {
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

std::string Elf_section::get_section_type(int tt) {
    if(tt < 0)
        return "UNKNOWN";

    switch(tt) {
        case 0: return "SHT_NULL";      /* Section header table entry unused */
        case 1: return "SHT_PROGBITS";  /* Program data */
        case 2: return "SHT_SYMTAB";    /* Symbol table */
        case 3: return "SHT_STRTAB";    /* String table */
        case 4: return "SHT_RELA";      /* Relocation entries with addends */
        case 5: return "SHT_HASH";      /* Symbol hash table */
        case 6: return "SHT_DYNAMIC";   /* Dynamic linking information */
        case 7: return "SHT_NOTE";      /* Notes */
        case 8: return "SHT_NOBITS";    /* Program space with no data (bss) */
        case 9: return "SHT_REL";       /* Relocation entries, no addends */
        case 11: return "SHT_DYNSYM";   /* Dynamic linker symbol table */
        default: return "UNKNOWN";
    }
    return "UNKNOWN";
}


}
#endif