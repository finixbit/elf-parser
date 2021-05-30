#include "catch.hpp"
#include "../elf_parser.hpp"
#include <elfio/elfio.hpp>

/*
 * Compare results of this library to 
 * the results of Elfio */

TEST_CASE("Elfio Compare")
{
	const auto path = GENERATE(
		"../examples/sections",
		"../examples/segments",
		"../examples/relocations",
		"../examples/symbols",
		"/usr/bin/bash"
	);

	ELFIO::elfio elfio;
	elfio.load(path);
	const elf_parser::Elf_parser elf_parser(path);

	SECTION("Elf Header"){
		REQUIRE(elf_parser.get_entry_point() == elfio.get_entry());
	}

	SECTION("Sections"){
		const auto ep_sections =  elf_parser.get_sections();
		const auto elfio_sections =  elfio.sections;

		REQUIRE(elfio_sections.size() == ep_sections.size());

		const size_t size = elfio_sections.size();

		for(unsigned i=0; i<size;i++)
		{
			const auto ep_section = ep_sections[i];
			const auto elfio_section = (elfio_sections[i]);
			REQUIRE(ep_section.section_addr == (long)elfio_section->get_address());
			REQUIRE(ep_section.section_size == (long)elfio_section->get_size());
		}
	}

	SECTION("Segments"){
		const auto ep_segments =  elf_parser.get_segments();
		const auto elfio_segments =  elfio.segments;

		REQUIRE(elfio_segments.size() == ep_segments.size());

		const size_t size = elfio_segments.size();

		for(unsigned i=0; i<size;i++)
		{
			const auto ep_segment = ep_segments[i];
			const auto elfio_segment = (elfio_segments[i]);
			REQUIRE(ep_segment.segment_virtaddr == (long)elfio_segment->get_virtual_address());
			REQUIRE(ep_segment.segment_physaddr == (long)elfio_segment->get_physical_address());
			REQUIRE(ep_segment.segment_filesize == (long)elfio_segment->get_file_size());
			REQUIRE(ep_segment.segment_memsize == (long)elfio_segment->get_memory_size());
			REQUIRE(ep_segment.segment_align == (long)elfio_segment->get_align());
		}
	}
}
