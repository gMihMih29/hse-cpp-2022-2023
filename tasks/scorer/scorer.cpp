#include "scorer.h"

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable answer;
    Events sorted_events = events;
    std::sort(sorted_events.begin(), sorted_events.end(),
              [](const Event& e1, const Event& e2) { return e1.time < e2.time; });
    for (const auto& e : events) {
        if (e.time > score_time) {
            break;
        }
        if (e.event_type == EventType::CheckSuccess) {
            answer[e.student_name].insert(e.task_name);
            continue;
        }
        if (e.event_type == EventType::MergeRequestClosed) {
            answer[e.student_name].insert(e.task_name);
            continue;
        }
        answer[e.student_name].erase(e.task_name);
    }
    return answer;
}
