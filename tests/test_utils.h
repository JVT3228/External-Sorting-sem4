#pragma once
#include <vector>
#include <string>

std::vector<int> read_test_file(const std::string& filename);
void write_test_file(const std::string& filename, const std::vector<int>& data);