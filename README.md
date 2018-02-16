# elf-parser
Lightweight header-only elf binary parser with no external dependencies - Sections, Symbols, Relocations, Segments 

# Required libraries
No dependencies

# Usage

## Sections (readelf -S <executable>)
parse sections header table from elf binary and return vector of section_t below

```
typedef struct {
    int section_index = 0; 
    std::intptr_t section_offset, section_addr;
    std::string section_name;
    std::string section_type; 
    int section_size, section_ent_size, section_addr_align;
} section_t;
```

get elf sections using elf-parser

```
#include <elf-parser.h>
Elf_parser::Elf_parser elf_parser(executable_path);
std::vector<Elf_parser::section_t> secs = elf_parser.get_sections();
```
see [example](examples/sections.cc)


# Supported Architecture
amd64

# Project using elf-parser
[ltrace](http://github.com/finixbit/ltrace)
[ftrace](http://github.com/finixbit/ftrace)

