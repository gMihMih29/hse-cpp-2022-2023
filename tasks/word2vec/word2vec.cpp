#include "word2vec.h"

#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    int dimensions = vectors[0].size();
    int max = 0;
    int count_max = 0;
    int current_result = 0;
    bool is_first = true;
    for (const auto& v : vectors) {
        current_result = 0;
        for (size_t i = 0; i < dimensions; ++i) {
            current_result += v[i] * vectors[0][i];
        }
        if (max < current_result || is_first) {
            max = current_result;
            count_max = 1;
            is_first = false;
        } else if (max == current_result) {
            ++count_max;
        }
    }
    std::vector<std::string> answer;
    answer.reserve(count_max);
    for (size_t i = 0; i < vectors.size(); ++i) {
        current_result = 0;
        for (size_t j = 0; j < dimensions; ++j) {
            current_result += vectors[i][j] * vectors[0][j];
        }
        if (max == current_result) {
            answer.push_back(words[i]);
        }
    }
    return answer;
}
