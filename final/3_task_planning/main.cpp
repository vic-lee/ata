#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ULL = unsigned long long;

//               1,000,000
#define TIME_MAX 1000000

#define FOR_N(n) for (int i = 0; i < n; i++)

template <typename T>
void print_iterable(const T& items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct TimeEntry {
    UIN start;
    UIN end;
    UIN repetition_interval;

    TimeEntry() {}

    TimeEntry(UIN start, UIN end)
        : start(start), end(end), repetition_interval(0){};

    TimeEntry(UIN start, UIN end, UIN interval)
        : start(start), end(end), repetition_interval(interval){};
};

struct Input {
    std::vector<TimeEntry> repeated_tasks;
    std::vector<TimeEntry> onetime_tasks;

    Input(size_t onetime_task_count, size_t repeated_task_count) {
        onetime_tasks = std::vector<TimeEntry>(onetime_task_count, TimeEntry());
        repeated_tasks =
            std::vector<TimeEntry>(repeated_task_count, TimeEntry());
    }
};

Input read_in() {
    size_t num_onetime_tasks, num_repeated_tasks;
    std::cin >> num_onetime_tasks >> num_repeated_tasks;
    Input in(num_onetime_tasks, num_repeated_tasks);
    UIN   start, end, repeat_interval;

    FOR_N(num_onetime_tasks) {
        cin >> start >> end;
        in.onetime_tasks[i] = TimeEntry(start, end);
    }

    FOR_N(num_repeated_tasks) {
        cin >> start >> end >> repeat_interval;
        in.repeated_tasks[i] = TimeEntry(start, end, repeat_interval);
    }

    return in;
}

bool has_time_conflicts(Input& in) {
    auto bs = bitset<TIME_MAX + 1>();

    // mark all repeated task intervals
    for (auto const& repeated_task : in.repeated_tasks) {
        auto begin = repeated_task.start, end = repeated_task.end;

        while (begin <= TIME_MAX) {
            for (size_t i = begin; i <= TIME_MAX && i < end; i++) {
                if (bs.test(i)) return true;  // overlap found
                bs.set(i);
            }

            begin += repeated_task.repetition_interval;
            end += repeated_task.repetition_interval;
        }
    }

    // mark all one-time tasks
    for (auto const& task : in.onetime_tasks) {
        auto begin = task.start, end = task.end;
        for (size_t i = begin; i <= TIME_MAX && i < end; i++) {
            if (bs.test(i)) return true;  // overlap found
            bs.set(i);
        }
    }

    return false;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();

    if (has_time_conflicts(in)) {
        cout << "CONFLICT" << endl;
    } else {
        cout << "NO CONFLICT" << endl;
    }
}
