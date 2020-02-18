#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <tuple>

#define PRIORITY_UNDEF 0

using namespace std;
struct PrintJob {
    unsigned short id;
    unsigned short priority;
};
using PriorityQueue = deque<PrintJob>;
using PriorityCountMap = map<unsigned short, unsigned short, greater<int>>;

struct Input {
    unsigned short target;
    PriorityQueue queue;
    PriorityCountMap priority_cnts;
};

Input read_in() {
    Input in;
    unsigned short jobs_cnt, p;
    cin >> jobs_cnt >> in.target;

    for (unsigned short i = 0; i < jobs_cnt; i++) {
        cin >> p;
        PrintJob job = {i, p};
        in.queue.push_back(job);
        in.priority_cnts[p]++;
    }

    return in;
}

unsigned short calc_wait_time(unsigned short target,
                              PriorityQueue& queue,
                              PriorityCountMap priority_cnts) {
    unsigned short time = 0;
    while (queue.size() > 0) {
        PrintJob f = queue.front();
        if (f.priority != priority_cnts.begin()->first) {
            queue.push_back(f);
            queue.pop_front();
        } else {
            time++;
            if (f.id == target)
                break;
            queue.pop_front();
            auto front = priority_cnts.begin();
            front->second--;
            if (front->second == 0)
                priority_cnts.erase(front);
        }
    }
    return time;
}

int main() {
    auto in = read_in();
    cout << calc_wait_time(in.target, in.queue, in.priority_cnts) << endl;
}
