#include "../elf_parser.h"
using namespace Elf_parser;

int main() {
  std::string program("/bin/ps");
  Elf_loader elf_loader(program);

  // readelf -S <executable>
  std::vector<section_t> secs = Elf_section::get_sections(elf_loader);
  Elf_section::print_sections(secs);
  return 0;
}
