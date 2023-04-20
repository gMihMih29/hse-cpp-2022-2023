#include "palindrome.h"

#include <algorithm>

bool IsPalindrome(const std::string& str) {
    size_t l = 0;
    size_t r = str.length() - 1;
    while (l < r) {
        while (str[l] == ' ' && l != str.length() - 1) {
            ++l;
        }
        while (str[r] == ' ' && r != 0) {
            --r;
        }
        if (l >= r) {
            break;
        }
        if (str[l] != str[r]) {
            return false;
        }
        l = std::min(l + 1, str.length());
        r = std::max(r - 1, static_cast<size_t>(0));
    }
    return true;
}
