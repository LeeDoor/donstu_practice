#include "header.hpp"

using KNeighbors = std::vector<std::pair<double, int>>;

std::string serialize_knn_output(const DataSet& data_set, const Stallion& new_stallion, const KNeighbors& nearest_K) {
    std::stringstream ss;
    ss << "Working with element:\n" << serialize_unit(new_stallion, true) << std::endl;
    ss << "Nearest " << nearest_K.size() << " categories:\n";
    for(const auto& unit : nearest_K) {
        ss << serialize_unit(data_set[unit.second], true) << std::endl;
    }
    ss << "Selected category: " << serialize_category(new_stallion.weight_status) << std::endl;
    return ss.str();
}


double get_distance(const Stallion& first, const Stallion& second) {
    double distance; // height age weight
    distance += std::pow((first.height_cm - second.height_cm) / 10.0, 2); // делим на 10 чтобы данные весили +- одинаково
    distance += std::pow(first.age_months - second.age_months, 2);
    distance += std::pow((first.weight_kg - second.weight_kg) / 10.0, 2);
    return std::sqrt(distance); 
}

KNeighbors get_nearest_K(const DataSet& data_set, Stallion& new_stallion, int K) {
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
        double distance = get_distance(data_set[i], new_stallion);
        nearest_K.push_back({ distance, i }); // добавляем новый элемент
        std::sort(nearest_K.begin(), nearest_K.end()); // сортируем по расстоянию до нашей точки
        nearest_K.pop_back(); // последним оказывается самый дальний элемент. убираем его, чтобы осталось только К элементов
    }
    return nearest_K;
}
WeightStatus get_preferred_category(const DataSet& data_set, const KNeighbors& nearest_K) {
    // Подсчитаем самую частую категорию среди них
    std::array<int, 5> repeatings; // repeatings[WeightStatus] = количество повторений этой категории
    repeatings.fill(0);
    WeightStatus result_cat = Normal;
    for(auto pair : nearest_K) {
        WeightStatus current_category = data_set[pair.second].weight_status;
        repeatings[current_category] = 1;
        if(repeatings[current_category] > repeatings[result_cat]) {
            result_cat = current_category;
        }
    }
    return result_cat;
}


int knn_algorithm(const DataSet& data_set, Stallion& new_unit, int K, const std::string& filename_or_console) {
    KNeighbors nearest_K = get_nearest_K(data_set, new_unit, K);
    WeightStatus preferred_category = get_preferred_category(data_set, nearest_K);
    new_unit.weight_status = preferred_category;
    std::string output = serialize_knn_output(data_set, new_unit, nearest_K);
    write_output(filename_or_console, output);
    return preferred_category;
}
