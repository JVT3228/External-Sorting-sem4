#include <catch.hpp>
#include "one_phase_merge_sort.cpp"
#include <fstream>
#include <vector>
#include "test_utils.h"

TEST_CASE("One-phase merge sort") {
    const std::string input_file = "test_input.bin";
    const std::string output_file = "test_output.bin";

    SECTION("Sorts random data") {
        std::vector<int> data = { 10, 5, 7, 3, 2 };
        write_test_file(input_file, data);
        one_phase_merge_sort<int>(input_file, output_file, 3);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == std::vector<int>{2, 3, 5, 7, 10});
    }

    SECTION("Handles single element data") {
        std::vector<int> data = { 42 };
        write_test_file(input_file, data);
        one_phase_merge_sort<int>(input_file, output_file, 2);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == data);
    }
}