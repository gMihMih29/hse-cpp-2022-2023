#pragma once

#include <memory>
#include <vector>
#include <string>

using std::string;

template <class T>
std::vector<std::unique_ptr<T>> Duplicate(const std::vector<std::shared_ptr<T>>& items) {
    std::vector<std::unique_ptr<T>> result(items.size());
    for (size_t i = 0; i < items.size(); ++i) {
        std::unique_ptr<T> new_ptr(new T(*items[i]));
        result[i] = std::move(new_ptr);
    }
    return result;
}

template <class T>
std::vector<std::shared_ptr<T>> DeDuplicate(const std::vector<std::unique_ptr<T>>& items) {
    std::vector<std::shared_ptr<T>> result;
    for (size_t i = 0; i < items.size(); ++i) {
        bool flag = false;
        for (size_t j = 0; j < result.size(); ++j) {
            if (*items[i] == *result[j]) {
                result.push_back(result[j]);
                flag = true;
                break;
            }
        }
        if (!flag) {
            std::shared_ptr<T> new_ptr(new T(*items[i]));
            result.push_back(new_ptr);
        }
    }
    return result;
}
