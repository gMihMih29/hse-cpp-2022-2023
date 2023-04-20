#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (8 > password.length() || password.length() > 14) {
        return false;
    }
    for (const char& i : password) {
        if (i < 32 || 126 < i) {
            return false;
        }
    }
    bool has_digits = false;
    bool has_upper = false;
    bool has_lower = false;
    bool has_other_symbols = false;
    for (const char& i : password) {
        if (isdigit(i)) {
            has_digits = true;
        } else if (isupper(i)) {
            has_upper = true;
        } else if (islower(i)) {
            has_lower = true;
        } else {
            has_other_symbols = true;
        }
    }
    return has_digits + has_upper + has_lower + has_other_symbols >= 3;
}
