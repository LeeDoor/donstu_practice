#pragma once

#include <climits> 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <unordered_map>
#include <sstream>

using DataUnit = std::vector<int>;
using DataSet = std::vector<DataUnit>;

bool save_data_set(const DataSet& data_set, const std::string& filename);
int knn_algorithm(const DataSet& data_set, DataUnit& new_unit, int K, const std::string& filename_or_console);
void k_means_algorithm(const DataSet& data_set, int K, const std::string& filename_or_console);

std::string serialize_unit(const DataUnit& unit);
bool write_output(const std::string& filename_or_console, const std::string& output);

int get_number(int from, int to);
std::string get_filename();
DataUnit read_unit_console(int unit_size);
DataSet read_set_console();

void k_means_algorithm(const DataSet& data_set, int K, const std::string& filename_or_console);
