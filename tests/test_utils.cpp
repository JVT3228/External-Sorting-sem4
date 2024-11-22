#include "test_utils.h"
#include <fstream>

std::vector<int> read_test_file(const std::string& filename) {
    std::vector<int> data;
    std::ifstream file(filename, std::ios::binary);
    int value;
    while (file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        data.push_back(value);
    }
    return data;
}

void write_test_file(const std::string& filename, const std::vector<int>& data) {
    std::ofstream file(filename, std::ios::binary);
    for (int value : data) {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }
}