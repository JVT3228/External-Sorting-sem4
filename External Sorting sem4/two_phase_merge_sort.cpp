#include "two_phase_merge_sort.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <cstdio>

template <typename T>
void split_to_temp_files(const std::string& input_file, std::vector<std::string>& temp_files, size_t buffer_size) {
    std::ifstream fin(input_file, std::ios::binary);
    std::vector<T> buffer(buffer_size);

    size_t file_count = 0;
    while (fin.read(reinterpret_cast<char*>(buffer.data()), buffer_size * sizeof(T)) || fin.gcount()) {
        size_t read_count = fin.gcount() / sizeof(T);
        buffer.resize(read_count);
        std::sort(buffer.begin(), buffer.end());

        std::string temp_file = "temp_" + std::to_string(file_count++) + ".bin";
        temp_files.push_back(temp_file);

        std::ofstream fout(temp_file, std::ios::binary);
        fout.write(reinterpret_cast<char*>(buffer.data()), read_count * sizeof(T));
    }
}

template <typename T>
void merge_temp_files(const std::vector<std::string>& temp_files, const std::string& output_file, size_t buffer_size) {
    auto cmp = [](std::pair<T, std::ifstream*> left, std::pair<T, std::ifstream*> right) {
        return left.first > right.first;
        };
    std::priority_queue<std::pair<T, std::ifstream*>, std::vector<std::pair<T, std::ifstream*>>, decltype(cmp)> min_heap(cmp);

    std::vector<std::ifstream> file_streams(temp_files.size());
    for (size_t i = 0; i < temp_files.size(); ++i) {
        file_streams[i].open(temp_files[i], std::ios::binary);
        T value;
        if (file_streams[i].read(reinterpret_cast<char*>(&value), sizeof(T))) {
            min_heap.emplace(value, &file_streams[i]);
        }
    }

    std::ofstream fout(output_file, std::ios::binary);
    std::vector<T> output_buffer;
    output_buffer.reserve(buffer_size);

    while (!min_heap.empty()) {
        auto [value, file] = min_heap.top();
        min_heap.pop();
        output_buffer.push_back(value);

        if (output_buffer.size() == buffer_size) {
            fout.write(reinterpret_cast<char*>(output_buffer.data()), output_buffer.size() * sizeof(T));
            output_buffer.clear();
        }

        if (file->read(reinterpret_cast<char*>(&value), sizeof(T))) {
            min_heap.emplace(value, file);
        }
    }

    if (!output_buffer.empty()) {
        fout.write(reinterpret_cast<char*>(output_buffer.data()), output_buffer.size() * sizeof(T));
    }

    for (const auto& temp_file : temp_files) {
        std::remove(temp_file.c_str());
    }
}

template <typename T>
void two_phase_merge_sort(const std::string& input_file, const std::string& output_file, size_t buffer_size) {
    std::vector<std::string> temp_files;
    split_to_temp_files<T>(input_file, temp_files, buffer_size);
    merge_temp_files<T>(temp_files, output_file, buffer_size);
}

template void two_phase_merge_sort<int>(const std::string&, const std::string&, size_t);
template void two_phase_merge_sort<double>(const std::string&, const std::string&, size_t);