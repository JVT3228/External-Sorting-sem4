#include "natural_merge_sort.h"
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>

template <typename T>
void natural_merge_sort(const std::string& input_file, const std::string& output_file, size_t buffer_size) {
    std::ifstream fin(input_file, std::ios::binary);
    if (!fin) {
        throw std::runtime_error("Failed to open input file.");
    }

    std::vector<std::string> temp_files{ "temp1.bin", "temp2.bin" };
    std::ofstream fout1(temp_files[0], std::ios::binary);
    std::ofstream fout2(temp_files[1], std::ios::binary);

    T prev_value, current_value;
    bool write_to_first = true;

    if (fin.read(reinterpret_cast<char*>(&prev_value), sizeof(T))) {
        (write_to_first ? fout1 : fout2).write(reinterpret_cast<char*>(&prev_value), sizeof(T));
    }

    while (fin.read(reinterpret_cast<char*>(&current_value), sizeof(T))) {
        if (current_value < prev_value) {
            write_to_first = !write_to_first;
        }
        (write_to_first ? fout1 : fout2).write(reinterpret_cast<char*>(&current_value), sizeof(T));
        prev_value = current_value;
    }

    fin.close();
    fout1.close();
    fout2.close();

    bool sorted = false;
    while (!sorted) {
        std::ifstream f1(temp_files[0], std::ios::binary);
        std::ifstream f2(temp_files[1], std::ios::binary);
        std::ofstream fout(output_file, std::ios::binary);

        T val1, val2;
        bool has_f1 = static_cast<bool>(f1.read(reinterpret_cast<char*>(&val1), sizeof(T)));
        bool has_f2 = static_cast<bool>(f2.read(reinterpret_cast<char*>(&val2), sizeof(T)));
        sorted = true;

        while (has_f1 || has_f2) {
            if (has_f1 && (!has_f2 || val1 <= val2)) {
                fout.write(reinterpret_cast<char*>(&val1), sizeof(T));
                has_f1 = static_cast<bool>(f1.read(reinterpret_cast<char*>(&val1), sizeof(T)));
            }
            else {
                fout.write(reinterpret_cast<char*>(&val2), sizeof(T));
                has_f2 = static_cast<bool>(f2.read(reinterpret_cast<char*>(&val2), sizeof(T)));
                sorted = false;
            }
        }

        f1.close();
        f2.close();
        fout.close();

        if (!sorted) {
            std::ifstream fin(output_file, std::ios::binary);
            std::ofstream fout1(temp_files[0], std::ios::binary);
            std::ofstream fout2(temp_files[1], std::ios::binary);

            write_to_first = true;
            if (fin.read(reinterpret_cast<char*>(&prev_value), sizeof(T))) {
                (write_to_first ? fout1 : fout2).write(reinterpret_cast<char*>(&prev_value), sizeof(T));
            }

            while (fin.read(reinterpret_cast<char*>(&current_value), sizeof(T))) {
                if (current_value < prev_value) {
                    write_to_first = !write_to_first;
                }
                (write_to_first ? fout1 : fout2).write(reinterpret_cast<char*>(&current_value), sizeof(T));
                prev_value = current_value;
            }

            fin.close();
            fout1.close();
            fout2.close();
        }
    }

    for (const auto& temp_file : temp_files) {
        std::remove(temp_file.c_str());
    }
}

template void natural_merge_sort<int>(const std::string&, const std::string&, size_t);
template void natural_merge_sort<double>(const std::string&, const std::string&, size_t);