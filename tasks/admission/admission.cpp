#include "admission.h"

#include <algorithm>
#include <map>

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::map<std::string, std::vector<const Student*>> univers_with_students;
    std::vector<const Applicant*> sorted_applicants;
    sorted_applicants.reserve(applicants.size());
    for (const auto& i : applicants) {
        sorted_applicants.push_back(&i);
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), [](const Applicant* a1, const Applicant* a2) {
        if (a1->points != a2->points) {
            return a1->points > a2->points;
        }
        if (a1->student.birth_date.year != a2->student.birth_date.year) {
            return a1->student.birth_date.year < a2->student.birth_date.year;
        }
        if (a1->student.birth_date.month != a2->student.birth_date.month) {
            return a1->student.birth_date.month < a2->student.birth_date.month;
        }
        if (a1->student.birth_date.day != a2->student.birth_date.day) {
            return a1->student.birth_date.day < a2->student.birth_date.day;
        }
        return a1->student.name < a2->student.name;
    });
    for (const auto& u : universities) {
        univers_with_students[u.name] = std::vector<const Student*>();
        univers_with_students[u.name].reserve(u.max_students);
    }
    for (const auto& i : sorted_applicants) {
        for (const auto& u : i->wish_list) {
            if (univers_with_students[u].capacity() != univers_with_students[u].size()) {
                univers_with_students[u].push_back(&i->student);
                break;
            }
        }
    }
    for (auto& i : univers_with_students) {
        std::sort(i.second.begin(), i.second.end(), [](const Student* s1, const Student* s2) {
            if (s1->name != s2->name) {
                return s1->name < s2->name;
            }
            if (s1->birth_date.year != s2->birth_date.year) {
                return s1->birth_date.year < s2->birth_date.year;
            }
            if (s1->birth_date.month != s2->birth_date.month) {
                return s1->birth_date.month < s2->birth_date.month;
            }
            return s1->birth_date.day < s2->birth_date.day;
        });
    }
    AdmissionTable answer;
    for (const auto& i : univers_with_students) {
        answer[i.first] = i.second;
    }
    return answer;
}
