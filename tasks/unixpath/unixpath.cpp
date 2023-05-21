#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    if (path.empty()) {
        return static_cast<std::string>(current_working_dir);
    }
    size_t left_path_index = 0;
    size_t right_path_index = 0;
    std::string answer;
    if (path[0] != '/') {
        answer = static_cast<std::string>(current_working_dir);
    } else {
        return static_cast<std::string>(path);
    }
    while (right_path_index < path.length()) {
        while (right_path_index < path.length() && path[right_path_index] != '/') {
            ++right_path_index;
        }
        if (left_path_index != right_path_index) {
            if (path.substr(left_path_index, right_path_index - left_path_index) == "..") {
                answer = answer.substr(0, answer.find_last_of('/'));
            } else if (path.substr(left_path_index, right_path_index - left_path_index) != ".") {
                answer += "/";
                answer += path.substr(left_path_index, right_path_index - left_path_index);
            }
        }
        while (right_path_index < path.length() && path[right_path_index] == '/') {
            ++right_path_index;
        }
        left_path_index = right_path_index;
    }
    if (answer.empty()) {
        answer = "/";
    }
    return answer;
}
