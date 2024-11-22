#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "two_phase_merge_sort.cpp"
#include <fstream>
#include <vector>
#include "test_utils.h"

TEST_CASE("Two-phase merge sort") {
    const std::string input_file = "test_input.bin";
    const std::string output_file = "test_output.bin";

    SECTION("Sorts random data") {
        std::vector<int> data = { 5, 3, 8, 6, 2 };
        write_test_file(input_file, data);
        two_phase_merge_sort<int>(input_file, output_file, 2);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == std::vector<int>{2, 3, 5, 6, 8});
    }

    SECTION("Handles already sorted data") {
        std::vector<int> data = { 1, 2, 3, 4, 5 };
        write_test_file(input_file, data);
        two_phase_merge_sort<int>(input_file, output_file, 2);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == data);
    }

    SECTION("Handles reverse sorted data") {
        std::vector<int> data = { 5, 4, 3, 2, 1 };
        write_test_file(input_file, data);
        two_phase_merge_sort<int>(input_file, output_file, 2);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == std::vector<int>{1, 2, 3, 4, 5});
    }

    SECTION("Handles empty data") {
        std::vector<int> data = {};
        write_test_file(input_file, data);
        two_phase_merge_sort<int>(input_file, output_file, 2);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result.empty());
    }
}