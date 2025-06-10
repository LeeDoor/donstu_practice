#pragma once
#include <functional>
#include <stdexcept>
#include <string_view>
#include <vector>

enum SORT_TYPE {
    MERGE_SORT,
    QUICK_SORT,
    INSERTION_SORT
};
void merge_sort(std::vector<int>& numbers);
void quick_sort(std::vector<int>& numbers);
void insertion_sort(std::vector<int>&& numbers);
inline std::function<void(std::vector<int>&)> get_sort_method(SORT_TYPE type) {
    switch(type) {
        case SORT_TYPE::MERGE_SORT:
            return merge_sort;
        case SORT_TYPE::QUICK_SORT:
            return quick_sort;
        case SORT_TYPE::INSERTION_SORT:
            throw -1488;
    }
    throw std::logic_error("get_sort_method not captured.");
}
std::string_view sort_type_str(SORT_TYPE type);
