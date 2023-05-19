#include "word2vec.h"

#include <cmath>
#include <vector>

const double EPS = 1e-9;

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    size_t dimensions = vectors[0].size();
    double current_result = 0;
    std::vector<double> self_scalar_prods;
    std::vector<double> first_scalar_prods;
    self_scalar_prods.reserve(vectors.size());
    first_scalar_prods.reserve(vectors.size());
    for (size_t i = 1; i < vectors.size(); ++i) {
        current_result = 0;
        for (size_t j = 0; j < dimensions; ++j) {
            current_result += vectors[i][j] * vectors[i][j];
        }
        self_scalar_prods.push_back(current_result);
    }
    for (size_t i = 1; i < vectors.size(); ++i) {
        current_result = 0;
        for (size_t j = 0; j < dimensions; ++j) {
            current_result += vectors[i][j] * vectors[0][j];
        }
        first_scalar_prods.push_back(current_result);
    }
    double max = -2;
    int count_max = 0;
    bool is_first = true;
    for (size_t i = 1; i < vectors.size(); ++i) {
        current_result = first_scalar_prods[i] / (std::sqrt(self_scalar_prods[i]) * std::sqrt(self_scalar_prods[0]));
        if (std::abs(max - current_result) < EPS) {
            ++count_max;
        } else if (max < current_result || is_first) {
            max = current_result;
            count_max = 1;
            is_first = false;
        }
    }
    std::vector<std::string> answer;
    answer.reserve(count_max);
    for (size_t i = 0; i < vectors.size(); ++i) {
        current_result = first_scalar_prods[i] / (std::sqrt(self_scalar_prods[i]) * std::sqrt(self_scalar_prods[0]));
        if (std::abs(max - current_result) < EPS) {
            answer.push_back(words[i]);
        }
    }
    return answer;
}
