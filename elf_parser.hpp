// MIT License

// Copyright (c) 2018 finixbit

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef H_ELF_PARSER
#define H_ELF_PARSER

#include <string>
#include <vector>

namespace elf_parser {

typedef struct {
    int section_index = 0; 
    std::intptr_t section_offset, section_addr;
    std::string section_name;
    std::string section_type; 
    int section_size, section_ent_size, section_addr_align;
} section_t;

typedef struct {
    std::string segment_type, segment_flags;
    long segment_offset, segment_virtaddr, segment_physaddr, segment_filesize, segment_memsize;
    int segment_align;
} segment_t;

typedef struct {
    std::string symbol_index;
    std::intptr_t symbol_value;
    int symbol_num = 0, symbol_size = 0;
    std::string symbol_type, symbol_bind, symbol_visibility, symbol_name, symbol_section;      
} symbol_t;

typedef struct {
    std::intptr_t relocation_offset, relocation_info, relocation_symbol_value;
    std::string   relocation_type, relocation_symbol_name, relocation_section_name;
    std::intptr_t relocation_plt_address;
} relocation_t;


class Elf_parser {
    public:
        Elf_parser (const std::string &program_path): m_program_path{program_path} {   
            load_memory_map();
        }
        Elf_parser (std::string&& program_path): m_program_path{std::move(program_path)} {   
            load_memory_map();
        }
		~Elf_parser();

		// Enable moving
		Elf_parser(Elf_parser&& rhs);
		Elf_parser& operator=(Elf_parser&& rhs);

		// Disable copying
		Elf_parser(const Elf_parser&) = delete;
		Elf_parser& operator=(const Elf_parser&) = delete;

		// Get ELF entry point address
		uintptr_t get_entry_point() const;

        std::vector<section_t> get_sections() const ;
        std::vector<segment_t> get_segments() const;
        std::vector<symbol_t> get_symbols() const;
        std::vector<relocation_t> get_relocations()const;
        uint8_t* get_memory_map();
        const uint8_t* get_memory_map() const;
        
    private:
        void load_memory_map();

        std::string get_section_type(int tt) const;

        std::string get_segment_type(uint32_t seg_type) const;
        std::string get_segment_flags(uint32_t seg_flags) const;

        std::string get_symbol_type(uint8_t sym_type) const;
        std::string get_symbol_bind(uint8_t sym_bind)const;
        std::string get_symbol_visibility(uint8_t sym_vis)const;
        std::string get_symbol_index(uint16_t sym_idx)const;

        std::string get_relocation_type(uint64_t rela_type) const;
        std::intptr_t get_rel_symbol_value(uint64_t sym_idx, const std::vector<symbol_t> &syms) const;
        std::string get_rel_symbol_name(
            uint64_t sym_idx, const std::vector<symbol_t> &syms) const;

        std::string m_program_path; 
        uint8_t *m_mmap_program = nullptr;
		size_t m_elf_size = 0;
};

}
#endif
