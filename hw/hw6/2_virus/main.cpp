#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;
using PID = unsigned int;
using Time = unsigned int;
using OfficeID = unsigned int;
using MinHeap = priority_queue<PID, vector<PID>, greater<PID>>;

struct Arrival {
    PID pid;
    Time arrival_time;
    Arrival(PID pid, unsigned int arrival_time)
        : pid(pid), arrival_time(arrival_time){};
};

auto comp_arrivals = [](const Arrival& a1, const Arrival& a2) {
    return a2.arrival_time <= a1.arrival_time;
};

using ArrivalQueue =
    priority_queue<Arrival, vector<Arrival>, decltype(comp_arrivals)>;
using VisitMap = map<PID, deque<unsigned int>>;

tuple<ArrivalQueue, VisitMap> read_in() {
    unsigned int patient_cnt, office_cnt, arrival_time, visit_cnt, x;
    cin >> patient_cnt >> office_cnt;

    ArrivalQueue arrivals(comp_arrivals);
    VisitMap visits;

    for (size_t pid = 1; pid <= patient_cnt; pid++) {
        cin >> arrival_time >> visit_cnt;
        arrivals.emplace(pid, arrival_time);
        for (size_t j = 0; j < visit_cnt; j++) {
            cin >> x;
            visits[pid].push_back(x);
        }
    }

    return {arrivals, visits};
}

/* Util function to enqueue patient from their prev office to their next. */
inline void enqueue_next(PID pid,
                         VisitMap& visits,
                         map<OfficeID, MinHeap>& buffer) {
    buffer[visits[pid].front()].push(pid);
    visits[pid].pop_front();
}

inline void flush_queue_buffer(map<OfficeID, MinHeap>& buffer,
                               map<OfficeID, queue<PID>>& queues) {
    for (auto& bf : buffer) {
        while (bf.second.size()) {
            queues[bf.first].push(bf.second.top());
            bf.second.pop();
        }
    }
    buffer.clear();
}

/**
 * Given the patients' order of arrival and each patient's oder of their
 * office visits, return the time when the last patient leaves the hospital.
 */
Time simulate_visits(ArrivalQueue& arrivals, VisitMap& visits) {
    map<OfficeID, queue<PID>> office_queues;
    map<OfficeID, MinHeap> office_enqueue_buffers;

    Time current_time = 0;
    const unsigned int patient_cnt = visits.size();
    unsigned int finished_patient_cnt = 0;

    while (finished_patient_cnt < patient_cnt) {
        // enqueue new arrivals
        while (arrivals.size() && arrivals.top().arrival_time <= current_time) {
            auto top = arrivals.top();
            enqueue_next(top.pid, visits, office_enqueue_buffers);
            arrivals.pop();
        }

        // enqueue queue heads to their next destination
        for (auto it = office_queues.begin(); it != office_queues.end();) {
            PID top_pid = it->second.front();
            it->second.pop();

            if (visits[top_pid].empty()) {  // finish this patient
                finished_patient_cnt++;
            } else {  // enqueue to next destination
                enqueue_next(top_pid, visits, office_enqueue_buffers);
            }

            if (it->second.empty()) {
                it = office_queues.erase(it);
            } else {
                it++;
            }
        }

        flush_queue_buffer(office_enqueue_buffers, office_queues);
        current_time++;
    }

    return current_time - 1;
}

int main() {
    auto [arrivals, visits] = read_in();
    cout << simulate_visits(arrivals, visits) << endl;
}
