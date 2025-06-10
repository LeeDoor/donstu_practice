#pragma once
#include <list>
#include <string_view>
#include <vector>
enum GENERATION_TYPE {
    ASCENDING,
    DESCENDING,
    RANDOM
};
static const std::list<GENERATION_TYPE> generation_types = {
    GENERATION_TYPE::ASCENDING,
    GENERATION_TYPE::DESCENDING,
    GENERATION_TYPE::RANDOM
};
std::string_view gen_type_str(GENERATION_TYPE type); 
std::vector<int> generate_numbers(size_t size = 100, GENERATION_TYPE type = GENERATION_TYPE::RANDOM);
