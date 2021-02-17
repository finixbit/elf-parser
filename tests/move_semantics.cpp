#include "catch.hpp"
#include "../elf_parser.hpp"
#include <elfio/elfio.hpp>

/*
 * Test move construction/assignment
 */

TEST_CASE("Move construction")
{
	elf_parser::Elf_parser parser_a("../examples/sections");
	elf_parser::Elf_parser parser_b(std::move(parser_a));

	REQUIRE(parser_a.get_memory_map() == nullptr);
	REQUIRE(parser_b.get_memory_map() != nullptr);
	REQUIRE(parser_b.get_entry_point() > 0);

	// Move back via assignment
	parser_a = std::move(parser_b);

	REQUIRE(parser_a.get_memory_map() != nullptr);
	REQUIRE(parser_b.get_memory_map() == nullptr);
	REQUIRE(parser_a.get_entry_point() > 0);

	// Test moving to a vector
	std::vector<decltype(parser_a)> vec;
	vec.emplace_back(std::move(parser_a));
	REQUIRE(parser_a.get_memory_map() == nullptr);
	REQUIRE(parser_b.get_memory_map() == nullptr);
	REQUIRE(vec.back().get_memory_map() != nullptr);
}

