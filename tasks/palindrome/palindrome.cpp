#include "palindrome.h"

#include <algorithm>

bool IsPalindrome(const std::string& str) {
    size_t l = 0;
    size_t r = str.length() - 1;
    while (l < r) {
        while (str[l] == ' ' && l != str.length() - 1) {
            ++l;
        }
        while (str[r] == ' ' && r != 1) {
            --r;
        }
        if (l >= r || l >= str.length() / 2 || r < str.length() / 2) {
            break;
        }
        if (str[l] != str[r]) {
            return false;
        }
        ++l;
        --r;
    }
    return true;
}
