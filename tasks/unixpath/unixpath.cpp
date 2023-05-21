#include "unixpath.h"

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    size_t left_path_index = 0;
    size_t right_path_index = 0;
    std::string answer = static_cast<std::string>(current_working_dir);
    while (right_path_index < path.length()) {
        while (right_path_index < path.length() && path[right_path_index] != '/') {
            ++right_path_index;
        }
        if (path.substr(left_path_index, right_path_index - left_path_index) == "..") {
            answer = answer.substr(0, answer.find_last_of('/'));
        } else if (path.substr(left_path_index, right_path_index - left_path_index) != ".") {
            answer += "/";
            answer += path.substr(left_path_index, right_path_index - left_path_index);
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
