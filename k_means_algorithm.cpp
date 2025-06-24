#include "header.hpp"

struct Centroid {
    double age = 0;
    double height = 0;
    double weight = 0;
    double w_status = 0;
};
using Centroids = std::vector<Centroid>;
// генерирует центроиды. каждый параметр какой-то краевой, чтобы лучше было видно разделение на группы
Centroid generate_centroid() {
    Centroid centroid;
    centroid.age = (rand() % 2) ? 6 : 34;
    centroid.height = (rand() % 2) ? 80 : 180;
    centroid.weight = (rand() % 2) ? 200 : 900;
    centroid.w_status = rand() % 5;
    return centroid;
}
// получает расстояние от пони до центроида
double get_distance_to_centroid(const Stallion& stallion, const Centroid& centroid) {
    double distance;
    distance += std::pow(stallion.age_months - centroid.age, 2);
    distance += std::pow((stallion.height_cm - centroid.height) / 10.0, 2); // делим на 10 чтобы данные весили +- одинаково
    distance += std::pow((stallion.weight_kg - centroid.weight) / 10.0, 2);
    return std::sqrt(distance); 
}
// генерирует центроиды
Centroids generate_centroids(int K) {
    Centroids centroids(K);
    for(int i = 0; i < K; ++i) {
        centroids[i] = generate_centroid();
    }
    return centroids;
}
// формирует новый центроид на основе средних значений пони в кластере и старого центроида
Centroids get_new_centroids(const Centroids& centroids, const std::vector<std::vector<Stallion*>>& clusters) {
    int K = centroids.size();
    Centroids new_centroids(K, Centroid{});
    for(int i = 0; i < K; ++i) {
        new_centroids[i].age = centroids[i].age;
        new_centroids[i].height = centroids[i].height;
        new_centroids[i].weight = centroids[i].weight;
        new_centroids[i].w_status = centroids[i].w_status;
        for(int j = 0; j < clusters[i].size(); ++j) {
            new_centroids[i].age += clusters[i][j]->age_months;
            new_centroids[i].height += clusters[i][j]->height_cm;
            new_centroids[i].weight += clusters[i][j]->weight_kg;
            new_centroids[i].w_status += static_cast<double>(clusters[i][j]->weight_status);
        }
        new_centroids[i].age /= clusters[i].size() + 1; // +1 initial centroid
        new_centroids[i].height /= clusters[i].size() + 1;
        new_centroids[i].weight /= clusters[i].size() + 1;
        new_centroids[i].w_status /= clusters[i].size() + 1;
    }
    return new_centroids;
}
// сравнивает два центроида по эпсилону
bool almost_similar(const Centroids& first, const Centroids& second) {
    double epsilon = 1e-6;
    bool similar = true;
    int K = first.size();
    for(int i = 0; i < K; ++i) {
        if(fabs(first[i].age - second[i].age) >= epsilon) return false;
        if(fabs(first[i].height - second[i].height) >= epsilon) return false;
        if(fabs(first[i].weight - second[i].weight) >= epsilon) return false;
        if(fabs(first[i].w_status - second[i].w_status) >= epsilon) return false;
    }
    return true;
}
// преобразует кластер поней в строку
std::string serialize_cluster(const std::vector<Stallion*>& cluster) {
    std::stringstream ss;
    for(const auto& point : cluster) {
        ss << serialize_unit(*point, true) << std::endl;
    }
    return ss.str();
}
// формирует вывод в строку
std::string serialize_kmeans_output(const std::vector<std::vector<Stallion*>>& clusters) {
    std::stringstream ss;
    int K = clusters.size();
    ss << "Separating data set to " << K << " groups\n" << serialize_header();
    for(int i = 0; i < K; ++i) {
        ss << "Group " << i + 1 << ":\n";
        ss << serialize_cluster(clusters[i]);
    }
    return ss.str();
}

// разделяет датасет на группы и выводит результат
void k_means_algorithm(DataSet& data_set, int K, const std::string& filename_or_console) {
    Centroids centroids = generate_centroids(K);
    std::vector<std::vector<Stallion*>> clusters;
    clusters.resize(K);
    bool running = true;
    while (running) {
        for(auto& cluster : clusters)
        cluster.clear();
        for(Stallion& stall : data_set) {
            double min_distance = std::numeric_limits<double>::max();
            int distance_id = -1;
            for(int i = 0; i < K; ++i) {
                double distance_to_center_ith = get_distance_to_centroid(stall, centroids[i]);
                if(distance_to_center_ith < min_distance) {
                    min_distance = distance_to_center_ith;
                    distance_id = i;
                }
            }
            Stallion* s = &stall; 
            clusters[distance_id].push_back(s);
        }
        Centroids new_centroids = get_new_centroids(centroids, clusters);
        if(almost_similar(centroids, new_centroids)) running = false;
        centroids = new_centroids;
    }
    write_output(filename_or_console, serialize_kmeans_output(clusters));
}
