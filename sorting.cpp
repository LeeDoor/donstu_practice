#include "sorting.hpp"
#include <chrono>
#include <iostream>

static const std::string_view MERGE_STR= "Merge";
static const std::string_view QUICK_STR = "Quick";
static const std::string_view INSERTION_STR = "Insertion";

void merge_sort(std::vector<int>& source, std::vector<int>& dest, int l, int r) {
    if(l == r) return;
    int m = (l + r) / 2;
    merge_sort(source, dest, l, m);
    merge_sort(source, dest, m + 1, r);
    int li = l, ri = m + 1, i = l;
    while(li <= m && ri <= r) {
        if(source[li] < source[ri]) {
            dest[i] = source[li++];
        } else {
            dest[i] = source[ri++];
        }
        ++i;
    }
    while(li <= m) dest[i++] = source[li++];
    while(ri <= r) dest[i++] = source[ri++];
    for(int i = l; i <= r; ++i) {
        source[i] = dest[i];
    }
}
void merge_sort(std::vector<int>& numbers) {
    std::vector<int> buffer(numbers.size());
    merge_sort(numbers, buffer, 0, numbers.size() - 1);
}
int pin_pivot(std::vector<int>& numbers, int l, int r) {
    int pivot = numbers[r]; 
    int i = l - 1;
    for(int j = l; j < r; ++j) {
        if(numbers[j] < pivot) {
            ++i;
            std::swap(numbers[i], numbers[j]);
        }
    }
    std::swap(numbers[i + 1], numbers[r]);
    return i + 1;
}
void quick_sort(std::vector<int>& numbers, int l, int r) {
    if(l >= r) return;
    int pivot = pin_pivot(numbers, l, r);
    quick_sort(numbers, l, pivot - 1);
    quick_sort(numbers, pivot + 1, r);
}
void quick_sort(std::vector<int>& numbers) {
    quick_sort(numbers, 0, numbers.size() - 1);
}
void insertion_sort(std::vector<int>& numbers) {
    int n = numbers.size();
    for(int i = 1; i < n; ++i) {
        int k = numbers[i];
        int j = i - 1;
        while (j >= 0 && numbers[j] > k) {
            std::swap(numbers[j + 1], numbers[j]);
            --j;
        }
        numbers[j + 1] = k;
    }
}
std::string_view sort_type_str(SORT_TYPE type) {
    switch(type) {
        case SORT_TYPE::MERGE_SORT:
            return MERGE_STR;
        case SORT_TYPE::QUICK_SORT:
            return QUICK_STR;
        case SORT_TYPE::INSERTION_SORT:
            return INSERTION_STR;
    }
    throw std::logic_error("sort_type_str did not capture the type.");
}
