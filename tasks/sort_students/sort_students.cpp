#include "sort_students.h"

bool EqualDates(Date a, Date b) {
    return (a.year == b.year && a.month == b.month && a.day == b.month);
}
bool CompareDates(Date a, Date b) {
    return (a.year < b.year) || (a.year == b.year && a.month < b.month) ||
           (a.year == b.year && a.month == b.month && a.day < b.day);
}
struct StudentDateComparator {
    bool operator()(Student a, Student b) {
        if (EqualDates(a.birth_date, b.birth_date)) {
            return a.last_name + a.name < b.last_name + b.name;
        }
        return CompareDates(a.birth_date, b.birth_date);
    }
};
struct StudentNameComparator {
    bool operator()(Student a, Student b) {
        if (a.last_name == b.last_name) {
            if (a.name == b.name) {
                return CompareDates(a.birth_date, b.birth_date);
            }
            return a.name < b.name;
        }
        return a.last_name < b.last_name;
    }
};
void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    StudentDateComparator sort_by_date;
    StudentNameComparator sort_by_name;
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), sort_by_date);
    } else {
        std::sort(students.begin(), students.end(), sort_by_name);
    }
}
