#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> works_order;
    std::vector<std::string> queries_order;
    for (auto student_action = student_actions.begin(); student_action != student_actions.end(); ++student_action) {
        if ((*student_action).side == Side::Bottom) {
            works_order.push_back((*student_action).name);
        }
    }
    for (auto student_action : student_actions) {
        if (student_action.side == Side::Top) {
            works_order.push_back(student_action.name);
        }
    }
    for (size_t index : queries) {
        queries_order.push_back(works_order[works_order.size() - index]);
    }
    return queries_order;
}
