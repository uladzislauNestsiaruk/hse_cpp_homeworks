#include "admission.h"
bool EqualDates(Date a, Date b) {
    return (a.year == b.year && a.month == b.month && a.day == b.month);
}
bool CompareDates(Date a, Date b) {
    return (a.year < b.year) || (a.year == b.year && a.month < b.month) ||
           (a.year == b.year && a.month == b.month && a.day < b.day);
}
struct ApplicantComparator {
    bool operator()(const Applicant* a, const Applicant* b) {
        if (a->points == b->points) {
            if (EqualDates(a->student.birth_date, b->student.birth_date)) {
                return a->student.name < b->student.name;
            }
            return CompareDates(a->student.birth_date, b->student.birth_date);
        }
        return a->points > b->points;
    }
};
struct StudentComparator {
    bool operator()(const Student* a, const Student* b) {
        if (a->name == b->name) {
            return CompareDates(a->birth_date, b->birth_date);
        }
        return a->name < b->name;
    }
};
AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    ApplicantComparator applicant_comparator;
    StudentComparator student_comparator;
    std::vector<const Applicant*> sorted_applicants;
    for (const Applicant& applicant : applicants) {
        sorted_applicants.push_back(&applicant);
    }
    AdmissionTable admission_table;
    std::unordered_map<std::string, size_t> places_left;
    for (const University& university : universities) {
        places_left[university.name] = university.max_students;
    }
    std::sort(sorted_applicants.begin(), sorted_applicants.end(), applicant_comparator);
    for (const Applicant* applicant : sorted_applicants) {
        for (const std::string& university_name : applicant->wish_list) {
            if (places_left[university_name] > admission_table[university_name].size()) {
                admission_table[university_name].push_back(&applicant->student);
                break;
            }
        }
    }
    for (const University& university : universities) {
        std::sort(admission_table[university.name].begin(), admission_table[university.name].end(), student_comparator);
    }
    return admission_table;
}
