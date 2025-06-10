#include <climits>
#include <iostream>
#include <vector>
#include <fstream>
#include "sorting.hpp"

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
std::vector<int> request_numbers(size_t size = 100) {
    std::vector<int> result(size);
    for(size_t i = 0; i < size; ++i) result[i] = size - i;
    return result;
}
void print_array(const std::vector<int>& array) {
    for(int i : array) {
        std::cout << i << ' ';
    }   std::cout << std::endl;
}

std::ostream* ask_ostream() {
    std::cout << 
        "Where do you want to put sorting results?\n"
        "0) avoid them\n"
        "1) standard output\n"
        "2) file #TODO\n";
    int print_result = get_input(0, 2);
    switch(print_result) {
        case 0:
            return nullptr;
        case 1:
            return &std::cout;
        case 2:
            return new std::ofstream("output.txt");
    }
    return nullptr;
}
void remove_ostream(std::ostream* output) {
    if(output == nullptr || output == &std::cout) return;
    delete output;
}

bool main_menu() {
    std::cout << 
        "Select an item from the menu:\n"
        "0) Exit\n"
        "1) Sort using Merge sort\n"
        "2) Sort using Quick sort\n"
        "3) Sort using Insertion sort\n";
    int input = get_input(0, 3);
    if(input == 0) return false;
    std::ostream* output = ask_ostream();
    std::vector<int> numbers = request_numbers(100000);
    switch(input) {
        case 1: {
            print(output, "initial array: ");
            print_array(numbers);
            std::cout << std::endl;
            merge_sort(numbers);
            std::cout << "sorted array: ";
            print_array(numbers);
            std::cout << std::endl;
            break;
        }
        case 2:
            quick_sort(request_numbers());
            break;
        case 3:
            insertion_sort(request_numbers());
            break;
    }
    remove_ostream(output);
    return true;
}

int main() {
    int choice = -1;
    std::cout << "Welcome to sorting comparer!\n";
    while(main_menu());
}
