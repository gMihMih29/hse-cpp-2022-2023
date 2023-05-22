#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t answer = 0;
    std::multiset<int> s;
    for (const int& p : provinces) {
        s.insert(p);
    }
    int val1 = 0;
    int val2 = 0;
    while (s.size() != 1) {
        val1 = *s.begin();
        s.erase(val1);
        val2 = *s.begin();
        s.erase(val2);
        answer += val1 + val2;
        s.insert(val1 + val2);
    }
    return answer;
}
