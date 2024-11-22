#include <catch.hpp>
#include "natural_merge_sort.cpp"
#include "test_utils.h"

TEST_CASE("Natural merge sort") {
    const std::string input_file = "test_input.bin";
    const std::string output_file = "test_output.bin";

    SECTION("Sorts random data") {
        std::vector<int> data = { 41, 89, 37, 10, 87, 70, 15, 16, 26, 13, 52, 45, 91, 25, 47, 75, 81, 65, 71, 65 };
        write_test_file(input_file, data);
        natural_merge_sort<int>(input_file, output_file, 5);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == std::vector<int>{10, 13, 15, 16, 25, 26, 37, 41, 45, 47, 52, 65, 65, 70, 71, 75, 81, 87, 89, 91});
    }

    SECTION("Handles already sorted data") {
        std::vector<int> data = { 1, 2, 3, 4, 5 };
        write_test_file(input_file, data);
        natural_merge_sort<int>(input_file, output_file, 3);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == data);
    }

    SECTION("Handles reverse sorted data") {
        std::vector<int> data = { 5, 4, 3, 2, 1 };
        write_test_file(input_file, data);
        natural_merge_sort<int>(input_file, output_file, 3);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == std::vector<int>{1, 2, 3, 4, 5});
    }

    SECTION("Handles empty data") {
        std::vector<int> data = {};
        write_test_file(input_file, data);
        natural_merge_sort<int>(input_file, output_file, 3);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result.empty());
    }

    SECTION("Handles single element") {
        std::vector<int> data = { 42 };
        write_test_file(input_file, data);
        natural_merge_sort<int>(input_file, output_file, 3);
        std::vector<int> result = read_test_file(output_file);
        REQUIRE(result == data);
    }
}