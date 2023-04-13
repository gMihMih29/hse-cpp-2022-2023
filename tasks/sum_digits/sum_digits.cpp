#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    int64_t sum = 0;
    while (number) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}