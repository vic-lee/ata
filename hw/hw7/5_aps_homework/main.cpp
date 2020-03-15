#include <iostream>
#include <queue>

using namespace std;
using UIN = unsigned int;

struct HWProblem {
    UIN solve_time;
    UIN grade_time;
    HWProblem(UIN solve, UIN grade) : solve_time(solve), grade_time(grade){};
};

ostream& operator<<(ostream& os, const HWProblem& hw) {
    os << "<" << hw.solve_time << ", " << hw.grade_time << ">";
    return os;
}

bool operator<(const HWProblem& hw1, const HWProblem& hw2) {
    return hw1.grade_time < hw2.grade_time;
}

priority_queue<HWProblem> read_in() {
    UIN hw_cnt, solve_time, grade_time;
    cin >> hw_cnt;
    priority_queue<HWProblem> hws;
    for (UIN i = 0; i < hw_cnt; i++) {
        cin >> solve_time >> grade_time;
        hws.emplace(solve_time, grade_time);
    }
    return hws;
}

UIN do_hw(priority_queue<HWProblem>& hws) {
    UIN time = 0, max_finish_grade_time = 0;

    while (hws.size()) {
        auto top = hws.top();
        max_finish_grade_time =
            max(time + top.solve_time + top.grade_time, max_finish_grade_time);
        time += top.solve_time;
        hws.pop();
    }

    return max_finish_grade_time;
}

int main() {
    auto hws = read_in();
    cout << do_hw(hws) << endl;
}
