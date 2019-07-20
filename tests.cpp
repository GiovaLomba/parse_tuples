#define CATCH_CONFIG_MAIN

#include "parse_tuples.hpp"
#include "tests_catch.hpp"

#include <string>
#include <iostream>
#include <vector>

namespace TestData{
	IndexedTuples<std::basic_string, char> tuples;
	const std::string l_sep ="\n"; // NOLINT(cert-err58-cpp)
	const std::string f_sep = ","; // NOLINT(cert-err58-cpp)
};

using namespace TestData;

TEST_CASE("Splitting text by space achieved by giving random not-empty field separator and space as line separator", ""){
	std::stringstream ss;
	std::string fields("###"), lines(" ");
	std::string content("give me all those words");
	parse_tuples(content, lines, fields, tuples);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second << "|";
		}
	}
	CHECK(ss.str() == "give|me|all|those|words|");
}

TEST_CASE("Splitting text by space achieved by giving random not-empty line separator and space as field separator", ""){
	std::stringstream ss;
	std::string fields(" "), lines("###");
	std::string content("give me all those words");
	parse_tuples(content, lines, fields, tuples);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second << "|";
		}
	}
	CHECK(ss.str() == "give|me|all|those|words|");
}

TEST_CASE("CSV parsing", ""){

	std::stringstream ss;
	std::string fields(","), lines("\n");
	std::string content("1,2,3\n4,5,6\n7,8,9\n1,3,5\n2,4,6\n3,5,7\n");
	parse_tuples(content, lines, fields, tuples);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second;
		}
	}
	CHECK(ss.str() == "123456789135246357");
}

TEST_CASE("CSV parsing with lines skip", ""){

	std::stringstream ss;
	std::string fields(","), lines("\n");
	std::string content("1,2,3\n4,5,6\n7,8,9\n1,3,5\n2,4,6\n3,5,7\n");
	parse_tuples(content, lines, fields, tuples, 3);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second;
		}
	}
	CHECK(ss.str() == "135246357");
}

TEST_CASE("CSV parsing with size limits", ""){

	std::stringstream ss;
	std::string fields(","), lines("\n");
	std::string content("1,2,3\n4,5,6\n7,8,9\n1,3,5\n2,4,6\n3,5,7\n");
	parse_tuples(content, lines, fields, tuples, 0, 1);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second;
		}
	}
	CHECK(ss.str() == "123");
}

TEST_CASE("CSV random line access", ""){

	std::stringstream ss;
	std::string fields(","), lines("\n");
	std::string content("1,2,3\n4,5,6\n7,8,9\n1,3,5\n2,4,6\n3,5,7\n");
	parse_tuples(content, lines, fields, tuples, 5, 1);
	for (const auto& row : tuples) {
		for (const auto& field : row.second) {
			ss << field.second;
		}
	}
	CHECK(ss.str() == "357");
}

TEST_CASE("When the line separator is not in content fields are parsed.", ""){
    std::string content("1,2,3");
    tuples = parse_tuples(content, l_sep, f_sep, tuples);
    CHECK(tuples.size() == 1);
    CHECK(tuples.at(0).at(0)=="1");
    CHECK(tuples.at(0).at(1)=="2");
    CHECK(tuples.at(0).at(2)=="3");
}

TEST_CASE("When the line separator and the field separator are not in content only one tuple of one field is returned.", ""){
    std::string content("an arbitrary long token not separated by commas");
    tuples = parse_tuples(content, l_sep, f_sep, tuples);
    CHECK(tuples.size() == 1);
    CHECK(tuples.at(0).at(0)==content);
}

TEST_CASE("When the field separator is empty and no line separator is in content only one tuple of one field is returned.", ""){
	std::string content("A descriptive string");
	const std::string empty;
	tuples = parse_tuples(content, l_sep, empty, tuples);
	CHECK(tuples.size() == 1);
	CHECK(tuples.at(0).at(0)==content);
}

TEST_CASE("When field separator is longer than content one tuple with one field is returned.", ""){
	std::string content("A string");
	const std::string field_sep("SOME_SEPARATOR");
	tuples = parse_tuples(content, l_sep, field_sep, tuples);
	CHECK(tuples.size() == 1);
	CHECK(tuples.at(0).at(0)==content);
}