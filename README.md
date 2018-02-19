# elf-parser
Lightweight header-only elf binary parser with no external dependencies - Sections, Symbols, Relocations, Segments 

# Required libraries
No dependencies

# Usage

## Sections (readelf -S executable)
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
elf_parser::Elf_parser elf_parser(executable_path);
std::vector<elf_parser::section_t> secs = elf_parser.get_sections();
```
see [example](examples/sections.cc)

## Segments (readelf -l executable)
parse program header table from elf binary and return vector of segment_t below

```
typedef struct {
    std::string segment_type, segment_flags;
    long segment_offset, segment_virtaddr, segment_physaddr, segment_filesize, segment_memsize;
    int segment_align;
} segment_t;
```

get elf segments using elf-parser

```
#include <elf-parser.h>
elf_parser::Elf_parser elf_parser(executable_path);
std::vector<elf_parser::segment_t> segs = elf_parser.get_segments();
```
see [example](examples/segments.cc)

## Symbols (readelf -s executable)
parse symbols table from elf binary and return vector of symbol_t below

```
typedef struct {
    std::string symbol_index;
    std::intptr_t symbol_value;
    int symbol_num = 0, symbol_size = 0;
    std::string symbol_type, symbol_bind, symbol_visibility, symbol_name, symbol_section;      
} symbol_t;
```

get elf symbols using elf-parser

```
#include <elf-parser.h>
elf_parser::Elf_parser elf_parser(executable_path);
std::vector<elf_parser::symbol_t> syms = elf_parser.get_symbols();
```
see [example](examples/symbols.cc)

## Relocations (readelf -r executable)
parse relocations with plt address from elf binary and return vector of relocation_t below

```
typedef struct {
    std::intptr_t relocation_offset, relocation_info, relocation_symbol_value;
    std::string   relocation_type, relocation_symbol_name, relocation_section_name;
    std::intptr_t relocation_plt_address;
} relocation_t;
```

get elf relocations using elf-parser

```
#include <elf-parser.h>
elf_parser::Elf_parser elf_parser(executable_path);
std::vector<elf_parser::relocation_t> relocs = elf_parser.get_relocations();
```
see [example](examples/relocations.cc)


# Supported Architecture
amd64

# Projects using elf-parser
[finixbit/ltrace - Library call tracer](http://github.com/finixbit/ltrace)

[finixbit/ftrace - Function call tracer](http://github.com/finixbit/ftrace)

