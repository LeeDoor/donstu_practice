#include <climits>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>
#include <fstream>
#include "sorting.hpp"
#include "number_generator.hpp"

static const std::string_view DELIMETER = "============";

int get_input(int from, int to) {
    int input = -1;
    std::cout << "Enter the item number: ";
    while (true) {
        std::cin >> input;
        if(std::cin.good() && from <= input && input <= to)
            return input;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "please try again: ";
    }
    return input;
}
void print_array(std::ostream* os, const std::vector<int>& numbers) {
        for(int i : numbers) {
            (*os) << i << ' ';
    }   (*os) << std::endl;
}

std::ostream* ask_ostream() {
    std::cout << 
        "Where do you want to put sorting results?\n"
        "1) standard output\n"
        "2) file\n";
    int print_result = get_input(1, 2);
    switch(print_result) {
        case 1:
            return &std::cout;
        case 2:
            std::string filename;
            std::cout << "Enter file name: ";
            std::cin >> filename;
            return new std::ofstream(filename);
    }
    throw std::logic_error("print_result is not captured.");
}
void remove_ostream(std::ostream* output) {
    if(output == nullptr || output == &std::cout) return;
    delete output;
}

std::chrono::milliseconds measure_time(std::function<void(std::vector<int>&)> method, std::vector<int>& numbers) {
    auto begin_time = std::chrono::steady_clock::now();
    method(numbers);
    auto end_time = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - begin_time);
}
std::vector<int> get_user_numbers() {
    std::cout << 
        "Which numbers do you want to sort?\n"
        "1) Enter manually\n"
        "2) Read from file\n"
        "3) Generate randomly\n";
    int select = get_input(1, 3);
    switch(select) {
        case 1: {
            return get_input_array();
        }
        case 2: {
            std::string filename;
            std::cout << "Enter file name: ";
            std::cin >> filename;
            return read_numbers_from_file(filename);
        }
        case 3: {
            return generate_numbers(99, RANDOM);
        }
    }       
    throw std::logic_error("get_input in get_user_numbers gave wrong input.");
}
void run_sorting(std::ostream* os, SORT_TYPE sort_type) {
    std::vector<int> numbers = get_user_numbers();
    (*os) << DELIMETER << std::endl;
    (*os) << "Initial array: ";
    print_array(os, numbers);

    auto elapsed = measure_time(get_sort_method(sort_type), numbers);

    (*os) << "Sorted array: ";
    print_array(os, numbers);
    (*os) << "Elapsed time: " << elapsed.count() << "ms\n";
}

void run_benchmarking(std::ostream* os, std::list<SORT_TYPE> methods) {
    std::cout << "Enter array size to generate:\n";
    int array_size = get_input(0, INT_MAX);
    (*os) << "Benchmarking array of size " << array_size << std::endl;
    (*os) << std::left;
    (*os) << std::setw(15) << "Sort Type"; 
    for(GENERATION_TYPE type : generation_types) {
        (*os) << std::setw(15) << gen_type_str(type);
    }   (*os) << std::endl;
    for(SORT_TYPE sort_type : methods) {
        (*os) << std::setw(15) << sort_type_str(sort_type);
        for(GENERATION_TYPE gen_type : generation_types) {
            auto numbers = generate_numbers(array_size, gen_type);
            auto elapsed = measure_time(get_sort_method(sort_type), numbers);
            (*os) << std::setw(15) << std::to_string(elapsed.count()) + "ms";
        }   (*os) << std::endl;
    }
}

bool main_menu() {
    std::cout << 
        "Select an item from the menu:\n"
        "0) Exit\n"
        "1) Sort using Merge sort\n"
        "2) Sort using Quick sort\n"
        "3) Sort using Insertion sort\n"
        "4) Benchmark algorithms\n";
    int input = get_input(0, 4);
    if(input == 0) return false;
    std::ostream* output = ask_ostream();
    switch(input) {
        case 1: 
            run_sorting(output, SORT_TYPE::MERGE_SORT);
            break;
        case 2:
            run_sorting(output, SORT_TYPE::QUICK_SORT);
            break;
        case 3:
            run_sorting(output, SORT_TYPE::INSERTION_SORT);
            break;
        case 4:
            run_benchmarking(output, {MERGE_SORT, QUICK_SORT, INSERTION_SORT});
            break;
    }
    remove_ostream(output);
    return true;
}

int main() {
    srand(time(NULL));
    std::cout << "Welcome to sorting comparer!\n";
    while(main_menu());
}
