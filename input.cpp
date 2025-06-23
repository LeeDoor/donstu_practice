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
DataUnit read_unit_console(int unit_size) {
    DataUnit unit(unit_size);
    std::cout << "enter " << unit_size << " numbers for a new unit: ";
    for(int i = 0; i < unit_size; ++i) {
        unit[i] = get_number(INT_MIN, INT_MAX);
    }
    return unit;
}
// считывает дата сет с консоли
DataSet read_set_console() {
    std::cout << "Enter the amount of numbers in data unit: ";
    int unit_size = get_number(1, INT_MAX);
    std::cout << "Etner the number of units in set: ";
    int data_size = get_number(1, INT_MAX);
    DataSet data_set(data_size);
    for(int i = 0; i < data_size; ++i) {
        data_set[i] = read_unit_console(unit_size);
        std::cout << "Unit added\n";
    }
    return data_set;
}
