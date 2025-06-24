#pragma once

#include <climits> 
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <sstream>

enum WeightStatus {
    StrongUnderweight,
    SlightUnderweight,
    Normal,
    SlightOverweight,
    StrongOverweight
};

struct Stallion {
    std::string nickname;
    int age_months;
    int height_cm; 
    int weight_kg;
    WeightStatus weight_status;
};
using DataSet = std::vector<Stallion>;

bool save_data_set(const DataSet& data_set, const std::string& filename);
int knn_algorithm(const DataSet& data_set, Stallion& new_unit, int K, const std::string& filename_or_console);
void k_means_algorithm(const DataSet& data_set, int K, const std::string& filename_or_console);

std::string serialize_category(WeightStatus category);
std::string serialize_unit(const Stallion& unit, bool is_user_print);
std::string serialize_data_set(const DataSet& set, bool is_user_print);
bool write_output(const std::string& filename_or_console, const std::string& output);

int get_number(int from, int to);
std::string get_filename();
Stallion read_unit_console(bool ask_age);
DataSet read_set_console();
DataSet read_set_file(std::string filename, bool& succeed);

void k_means_algorithm(const DataSet& data_set, int K, const std::string& filename_or_console);
