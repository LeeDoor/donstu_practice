#include "number_generator.hpp"
#include <cstdlib>
#include <stdexcept>

static const std::string_view ASCENDING_STR = "Ascending";
static const std::string_view DESCENDING_STR = "Descending";
static const std::string_view RANDOM_STR = "Random";

std::vector<int> generate_ascending(size_t size = 100) {
    std::vector<int> result(size);
    for(size_t i = 0; i < size; ++i) result[i] = i;
    return result;
}
std::vector<int> generate_descending(size_t size = 100) {
    std::vector<int> result(size);
    for(size_t i = 0; i < size; ++i) result[i] = size - i;
    return result;
}
std::vector<int> generate_random(size_t size = 100) {
    std::vector<int> result(size);
    for(size_t i = 0; i < size; ++i) result[i] = rand() % size;
    return result;
}
std::string_view gen_type_str(GENERATION_TYPE type) {
    switch(type) {
        case GENERATION_TYPE::ASCENDING:
            return ASCENDING_STR;
        case GENERATION_TYPE::DESCENDING:
            return DESCENDING_STR;
        case GENERATION_TYPE::RANDOM:
            return RANDOM_STR;
    }
    throw std::logic_error("gen_type_str mapping is broken");
}
std::vector<int> generate_numbers(size_t size, GENERATION_TYPE type) {
    switch(type) {
        case GENERATION_TYPE::ASCENDING:
            return generate_ascending(size);
        case GENERATION_TYPE::DESCENDING:
            return generate_descending(size);
        case GENERATION_TYPE::RANDOM:
            return generate_random(size);
    }
    throw std::logic_error("generate_numbers mapping is broken");
}
