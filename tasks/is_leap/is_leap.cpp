#include "is_leap.h"

bool IsLeap(int year) {
    const int FOUR = 4;
    const int HUNDRED = 100;
    const int FOUR_HUNDRED = 400;
    if (year % FOUR_HUNDRED == 0) {
        return true;
    }
    if (year % FOUR == 0 && year % HUNDRED != 0) {
        return true;
    }
    return false;
}
