#include "header.hpp"

// функция получает из консоли число от from до to
// если не получилось спрашивает еще раз
int get_number(int from, int to) {
    int input;
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

// получает из консоли имя файла
std::string get_filename() {
    std::cout << "enter file name: ";
    std::string filename;
    std::cin >> filename;
    return filename;
}

// считывает один элемент датасета с консоли
Stallion read_unit_console(bool ask_weight_status) {
    Stallion horse;
    std::cout << "Enter stallion nickname: ";
    std::cin >> horse.nickname;
    std::cout << "Enter horse age (6 - 40 months): ";
    horse.age_months = get_number(6, 40);
    std::cout << "Enter horse height in cm (80 - 180): ";
    horse.height_cm = get_number(80, 200);
    std::cout << "enter horse weight (200-900 kg): ";
    horse.weight_kg = get_number(200, 900);
    if(ask_weight_status) {
        std::cout << "enter weight status:\n"
            "1) Strong underweight\n"
            "2) Slight underweight\n"
            "3) Normal\n"
            "4) Slight overweight\n"
            "5) Strong overweight\n";
        int status = get_number(1, 5);
        horse.weight_status = static_cast<WeightStatus>(status - 1);
    }
    return horse;
}
// считывает дата сет с консоли
DataSet read_set_console() {
    std::cout << "Enter the number of units in set: ";
    int data_size = get_number(1, INT_MAX);
    DataSet data_set(data_size);
    for(int i = 0; i < data_size; ++i) {
        data_set[i] = read_unit_console(true);
        std::cout << "Stallion added\n";
    }
    return data_set;
}
Stallion read_unit_file(std::ifstream& ifs) {
    Stallion stallion;
    int status_int;
    ifs >> stallion.nickname
        >> stallion.age_months
        >> stallion.height_cm
        >> stallion.weight_kg
        >> status_int;
    stallion.weight_status = static_cast<WeightStatus>(status_int);
    return stallion;
}

DataSet read_set_file(std::string filename, bool& succeed) {
    std::ifstream ifs(filename);
    if(!ifs.is_open()) {
        std::cout << "unable to open file\n";
        succeed = false;
        return {};
    }
    int N;
    ifs >> N;
    DataSet data_set;
    for(int i = 0; i < N; ++i) {
        data_set.push_back(read_unit_file(ifs));
    }
    succeed = true;//ifs.good();
    return data_set;
}
