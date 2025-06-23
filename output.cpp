#include "header.hpp"

std::string serialize_unit(const DataUnit& unit) {
    std::stringstream ss;
    for(int i = 0; i < unit.size(); ++i) {
        ss << unit[i] << ' ';
    }
    return ss.str();
}

std::string serialize_data_set(const DataSet& set) {
    std::stringstream ss;
    ss << set[0].size() << ' ' << set.size() << std::endl; // при сохранении, первой строчкой выводим размер данных и размер сета
    // потом в set.size() строках пишем по юниту
    for(int i = 0; i < set.size(); ++i) {
        ss << serialize_unit(set[i]) << std::endl;
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
    return write_output(filename, serialize_data_set(data_set));
}
