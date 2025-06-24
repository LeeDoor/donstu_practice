#include "header.hpp"
#include <iomanip>

std::string serialize_category(WeightStatus category) {
    switch(category) {
        case StrongUnderweight:
            return "Strong underweight";
        case SlightUnderweight:
            return "Slight underweight";
        case Normal:
            return "Normal";
        case SlightOverweight:
            return "Slight overweight";
        case StrongOverweight:
            return "Strong overweight";
    }
    throw std::runtime_error("serialize_category didn't match any");
}

std::string serialize_unit(const Stallion& stallion, bool is_user_print) {
    std::stringstream ss;
    ss  << std::setw(15) <<  stallion.nickname << ' ' 
        << std::setw(8) << stallion.age_months << ' ' 
        << std::setw(6) << stallion.height_cm << ' ' 
        << std::setw(13) << stallion.weight_kg << ' ';
    if(is_user_print)
        ss << std::setw(21) << serialize_category(stallion.weight_status);
    else
        ss << std::setw(3) << stallion.weight_status;
    return ss.str();
}

std::string serialize_header() {
    std::stringstream ss;
    ss  << std::setw(15) << "Nickname" << ' ' 
        << std::setw(8) << "Age, m" << ' ' 
        << std::setw(6) << "H, cm" << ' ' 
        << std::setw(13) << "Weight, kg" << ' ' 
        << std::setw(21) << "Weight category" << std::endl; 
    return ss.str();
}
std::string serialize_data_set(const DataSet& set, bool is_user_print) {
    std::stringstream ss;
    ss << set.size() << std::endl; // при сохранении, первой строчкой выводим размер данных и размер сета
    if(is_user_print) {
        ss << serialize_header();
    }
    // потом в set.size() строках пишем по юниту
    for(int i = 0; i < set.size(); ++i) {
        ss << serialize_unit(set[i], is_user_print) << std::endl;
    }
    return ss.str();
}

bool write_output(const std::string& filename_or_console, const std::string& output) {
    if(filename_or_console.empty()) {
        std::cout << output << std::endl;
        return true;
    }
    std::ofstream ofs(filename_or_console);
    if(!ofs.is_open()) {
        std::cout << "failed to open file\n";
        return false;
    }
    ofs << output;
    ofs.close();
    return true;
}

bool save_data_set(const DataSet& data_set, const std::string& filename) {
    return write_output(filename, serialize_data_set(data_set, false));
}
