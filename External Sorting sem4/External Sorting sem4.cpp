#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include "two_phase_merge_sort.cpp"
#include "one_phase_merge_sort.cpp"
#include "natural_merge_sort.cpp"

void generate_random_file(const std::string& filename, size_t count, int min_value, int max_value) {
    std::ofstream fout(filename, std::ios::binary);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min_value, max_value);

    for (size_t i = 0; i < count; ++i) {
        int value = dist(gen);
        fout.write(reinterpret_cast<const char*>(&value), sizeof(int));
    }
}

std::vector<int> read_file(const std::string& filename) {
    std::ifstream fin(filename, std::ios::binary);
    fin.seekg(0, std::ios::end);
    size_t size = fin.tellg() / sizeof(int);
    fin.seekg(0, std::ios::beg);

    std::vector<int> data(size);
    fin.read(reinterpret_cast<char*>(data.data()), size * sizeof(int));
    return data;
}

void print_vector(const std::vector<int>& data) {
    for (int value : data) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

int main() {
    const std::string input_file = "input_data.bin";
    const std::string output_file_two_phase = "output_two_phase.bin";
    const std::string output_file_one_phase = "output_one_phase.bin";
    const std::string output_file_natural = "output_natural.bin";

    size_t data_size = 20;
    int min_value = 1, max_value = 100;

    generate_random_file(input_file, data_size, min_value, max_value);
    std::cout << "Generated random data: ";
    print_vector(read_file(input_file));

    std::cout << "\n=== Two-Phase Merge Sort ===\n";
    two_phase_merge_sort<int>(input_file, output_file_two_phase, 5);
    std::vector<int> sorted_two_phase = read_file(output_file_two_phase);
    std::cout << "Sorted data: ";
    print_vector(sorted_two_phase);

    std::cout << "\n=== One-Phase Merge Sort ===\n";
    one_phase_merge_sort<int>(input_file, output_file_one_phase, 5);
    std::vector<int> sorted_one_phase = read_file(output_file_one_phase);
    std::cout << "Sorted data: ";
    print_vector(sorted_one_phase);

    std::cout << "\n=== Natural Merge Sort ===\n";
    natural_merge_sort<int>(input_file, output_file_natural, 5);
    std::vector<int> sorted_natural = read_file(output_file_natural);
    std::cout << "Sorted data: ";
    print_vector(sorted_natural);

    return 0;
}