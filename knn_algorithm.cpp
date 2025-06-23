#include "header.hpp"

using KNeighbors = std::vector<std::pair<double, int>>;

std::string serialize_knn_output(const DataSet& data_set, const DataUnit& new_unit, const KNeighbors& nearest_K, int selected_cat) {
    std::stringstream ss;
    ss << "Working with element: " << serialize_unit(new_unit) << std::endl;
    ss << "Nearest " << nearest_K.size() << " categories:\n";
    for(const auto& unit : nearest_K) {
        ss << serialize_unit(data_set[unit.second]) << std::endl;
    }
    ss << "Selected category: " << selected_cat << std::endl;
    return ss.str();
}


double get_distance(const DataUnit& first, const DataUnit& second) {
    double distance;
    for(int i = 1; i < first.size(); ++i) { // начинаем с 1, тк нулевой элемент это категория, неизвестная для нашего элемента
        distance += std::pow(first[i] - second[i], 2);
    }
    return std::sqrt(distance); 
}

KNeighbors get_nearest_K(const DataSet& data_set, const DataUnit& new_unit, int K) {
    // создаем массив пар дробного и целого чисел, например: [ (1.2, 1), (6.3, 1), (8.1, 6) ]
    // дробное число это расстояние от новой точки до какого-то элемента, а целое число - айди этого элемента.
    // мы храним айди и расстояние до ближайших К соседей и затем по ним выбираем категорию
    // нашего элемента. 
    KNeighbors nearest_K;
    nearest_K.resize(K); // в массиве будет К элементов
    for(auto& pair : nearest_K) {
        pair = { std::numeric_limits<int>::max(), std::numeric_limits<double>::max() };
    }
    for(int i = 0; i < data_set.size(); ++i) {
        double distance = get_distance(data_set[i], new_unit);
        nearest_K.push_back({ distance, i }); // добавляем новый элемент
        std::sort(nearest_K.begin(), nearest_K.end()); // сортируем по расстоянию до нашей точки
        nearest_K.pop_back(); // последним оказывается самый дальний элемент. убираем его, чтобы осталось только К элементов
    }
    return nearest_K;
}
int get_preferred_category(const DataSet& data_set, const KNeighbors& nearest_K) {
    // Подсчитаем самую частую категорию среди них
    std::unordered_map<int, int> dictionary; // создаем словарь, где ключ - категория, а значение - количество повторений
    int preferred_category = data_set[nearest_K[0].second][0]; // здесь будем хранить нужную категорию. 
    for(auto pair : nearest_K) {
        int current_category = data_set[pair.second][0];
        if(dictionary.contains(current_category)) {
            ++dictionary[current_category];
        } else {
            dictionary[current_category] = 1;
        }
        if(dictionary[preferred_category] < dictionary[current_category]) {
            // Если вдруг какая то категория станет встречаться чаще чем нужная, поменяем
            preferred_category = current_category;
        }
    }
    return preferred_category;
}


int knn_algorithm(const DataSet& data_set, DataUnit& new_unit, int K, const std::string& filename_or_console) {
    KNeighbors nearest_K = get_nearest_K(data_set, new_unit, K);
    int preferred_category = get_preferred_category(data_set, nearest_K);
    new_unit[0] = preferred_category;
    std::string output = serialize_knn_output(data_set, new_unit, nearest_K, preferred_category);
    write_output(filename_or_console, output);
    return preferred_category;
}
