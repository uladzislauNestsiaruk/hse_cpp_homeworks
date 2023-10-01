#include "scorer.h"
struct EventTimeComparator {
    bool operator()(const Event& a, const Event& b) {
        return a.time < b.time;
    }
};
ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable score_table;
    EventTimeComparator event_time_comparator;
    Events sorted_events = events;
    std::map<std::pair<StudentName, TaskName>, bool> is_merge_request_open;
    std::map<std::pair<StudentName, TaskName>, bool> is_last_cl_failed;
    std::sort(sorted_events.begin(), sorted_events.end(), event_time_comparator);
    for (const Event& event : sorted_events) {
        if (event.time > score_time) {
            break;
        }
        if (event.event_type == EventType::CheckFailed || event.event_type == EventType::CheckSuccess) {
            is_last_cl_failed[std::make_pair(event.student_name, event.task_name)] =
                event.event_type == EventType::CheckFailed;
        } else {
            is_merge_request_open[std::make_pair(event.student_name, event.task_name)] =
                event.event_type == EventType::MergeRequestOpen;
        }
    }
    for (const auto& student_and_task : is_last_cl_failed) {
        if (!student_and_task.second && !is_merge_request_open[student_and_task.first]) {
            score_table[student_and_task.first.first].insert(student_and_task.first.second);
        }
    }
    return score_table;
}
