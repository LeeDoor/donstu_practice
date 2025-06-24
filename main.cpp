#include "header.hpp"

// вежливо просит ввести значение для К.
int get_valid_k(int mx) {
    std::cout << 
        "Enter K value for your calculations.\n"
        "Use K less than the data set size for effectiveness\n";
    return static_cast<int>(get_number(1, mx));
}

// спрашивает, куда положить результаты вычислений.
// если пользователь захочет в консоль, возвращает пустую строку.
// если в файл, возвращает имя файла.
std::string get_filename_or_console() {
    std::cout << 
        "Where to put the results?\n"
        "1) in console\n"
        "2) in file\n";
    return get_number(1, 2) == 2 ? get_filename() : "";
}

// меню, в котором мы выбираем, откуда брать данные
// появляется в начале и когда просим загрузить новые данные
bool initial_menu(DataSet& data_set) {
    std::cout << 
        "How to load the data?\n"
        "1) enter manually\n"
        "2) read from file\n"
        "3) generate\n"
        "0) exit\n";
    int choice = get_number(0, 3);
    switch(choice) {
        case 0: {
            return false;
        }
        case 1: {
            data_set = read_set_console();
            break;
        }
        case 2: {
            std::string filename = get_filename();
            bool succeed;
            data_set = read_set_file(filename, succeed);
            if(!succeed) 
                return false;
            break;
        }
        case 3: {
            std::cout << "Enter data set size: ";
            int size = get_number(1, INT_MAX);
            data_set = generate_set(size);
            break;
        }
    }
    return true;
}

// главное меню, появляется после загрузки данных. повторяется пока
// не выберем пункт exit
bool main_menu(DataSet& data_set) {
    std::cout <<
        "What do you want to do:\n"
        "1) load new data set\n"
        "2) save current data set to file\n"
        "3) apply KNN algorithm\n"
        "4) apply K-means algorithm NOT IMPLEMENTED\n"
        "5) add element to data set\n"
        "6) print data set\n"
        "0) exit\n";
    int choice = get_number(0, 6);
    switch(choice) {
        case 0:
            return false;
        case 1: {
            std::cout << "Current data set will be lost since last save; proceed?(0 - yes, 1 - no):";
            choice = get_number(0, 1);
            if(choice == 0) {
                if(!initial_menu(data_set)) {
                    std::cout << "Data hasn't changed\n";
                } else {
                    std::cout << "New data set loaded\n";
                }
            } std::cout << "Cancelled\n";
            break;
        }
        case 2: {
            std::string filename = get_filename();
            if(save_data_set(data_set, filename)) {
                std::cout << "Data saved successfully\n";
            } 
            break;
        }
        case 3: {
            int K = get_valid_k(data_set.size());
            std::string filename_or_console = get_filename_or_console();
            Stallion new_unit = read_unit_console(false);
            knn_algorithm(data_set, new_unit, K, filename_or_console);
            break;
        }
        case 4: {
            int K = get_valid_k(data_set.size());
            std::string filename_or_console = get_filename_or_console();
            k_means_algorithm(data_set, K, filename_or_console);
            break;
        }
        case 5: {
            data_set.push_back(read_unit_console(true));
            break;
        }
        case 6: {
            std::cout << serialize_data_set(data_set, true) << std::endl;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));

    DataSet data_set;
    if(!initial_menu(data_set)) 
        return 0;
    while(main_menu(data_set));
}
