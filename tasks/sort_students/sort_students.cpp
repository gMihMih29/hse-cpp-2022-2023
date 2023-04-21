#include "sort_students.h"

#include <algorithm>

int Date::CompareTo(const Date& d) {
    if (year < d.year) {
        return 1;
    } else if (year > d.year) {
        return -1;
    }
    if (month < d.month) {
        return 1;
    } else if (month > d.month) {
        return -1;
    }
    if (day < d.day) {
        return 1;
    } else if (day > d.day) {
        return -1;
    }
    return 0;
}

bool CmpDate(Student s1, Student s2) {
    int cmp_result = s1.birth_date.CompareTo(s2.birth_date);
    if (cmp_result != 0) {
        return cmp_result > 0;
    }
    return s1.last_name + s1.name < s2.last_name + s2.name;
}

bool CmpName(Student s1, Student s2) {
    if (s1.last_name + s1.name != s2.last_name + s2.name) {
        return s1.last_name + s1.name < s2.last_name + s2.name;
    }
    int cmp_result = s1.birth_date.CompareTo(s2.birth_date);
    return cmp_result > 0;
}

void SortStudents(std::vector<Student>& students, SortKind sort_kind) {
    if (sort_kind == SortKind::Date) {
        std::sort(students.begin(), students.end(), CmpDate);
    } else {
        std::sort(students.begin(), students.end(), CmpName);
    }
}
