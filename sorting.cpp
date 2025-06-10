#include "sorting.hpp"
#include <chrono>
#include <iostream>
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
    std::chrono::time_point begin = std::chrono::steady_clock::now();
    merge_sort(numbers, buffer, 0, numbers.size() - 1);
    std::chrono::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
}
void quick_sort(std::vector<int>&& numbers) {

}
void insertion_sort(std::vector<int>&& numbers) {

}
