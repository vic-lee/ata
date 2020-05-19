#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

enum ArrivalLocation {
    Left,
    Right,
};

struct CarArrival {
    CarArrival() : time(0), loc(Left){};
    CarArrival(unsigned int id, unsigned int t, ArrivalLocation l)
        : id(id), time(t), loc(l){};
    unsigned int id;
    unsigned int time;
    ArrivalLocation loc;
};

struct Ferry {
    unsigned int max_carload;
    unsigned int transit_time;
};

struct Input {
    Ferry ferry;
    deque<CarArrival> car_stream;
};

Input read_in() {
    Input in;
    unsigned int car_arrival_cnt, next_time;
    string direction;
    cin >> in.ferry.max_carload >> in.ferry.transit_time >> car_arrival_cnt;
    in.car_stream = deque<CarArrival>(car_arrival_cnt, CarArrival());

    for (unsigned int i = 0; i < car_arrival_cnt; ++i) {
        cin >> next_time >> direction;
        in.car_stream[i] = (direction == "left")
                               ? CarArrival(i, next_time, Left)
                               : CarArrival(i, next_time, Right);
    }

    return in;
}

bool load_ferry(const Ferry& ferry,
                deque<CarArrival>& queue,
                unsigned int& curr_time,
                vector<unsigned int>& out) {
    if (queue.size() == 0)
        return false;

    unsigned int loaded_car_cnt = 0;

    while (queue.size() > 0 && loaded_car_cnt < ferry.max_carload &&
           queue.front().time <= curr_time) {
        out[queue.front().id] = curr_time + ferry.transit_time;
        queue.pop_front();
        loaded_car_cnt++;
    }

    return loaded_car_cnt > 0;
}

vector<unsigned int> calc_arrival_times(const Ferry ferry,
                                        deque<CarArrival>& car_stream) {
    auto out = vector<unsigned int>(car_stream.size(), 0);
    bool on_left = true;
    bool in_transit = false;
    unsigned int time = 0;
    unsigned int arrival_time = 0;
    deque<CarArrival> lqueue, rqueue;

    if (car_stream.size() == 0)
        return out;

    while (car_stream.size() || lqueue.size() || rqueue.size()) {
        while (car_stream.size() && car_stream.front().time <= time) {
            if (car_stream.front().loc == Left)
                lqueue.push_back(car_stream.front());
            else
                rqueue.push_back(car_stream.front());
            car_stream.pop_front();
        }

        if (in_transit && time == arrival_time) {
            in_transit = false;
            on_left = !on_left;
        }

        if (!in_transit) {
            if (lqueue.size() && rqueue.size()) {
                if (on_left) {
                    in_transit = load_ferry(ferry, lqueue, time, out);
                } else {
                    in_transit = load_ferry(ferry, rqueue, time, out);
                }
            } else if (lqueue.size()) {
                if (on_left) {
                    in_transit = load_ferry(ferry, lqueue, time, out);
                } else {
                    in_transit = true;
                }
            } else if (rqueue.size()) {
                if (!on_left) {
                    in_transit = load_ferry(ferry, rqueue, time, out);
                } else {
                    in_transit = true;
                }
            }
            if (in_transit)
                arrival_time = time + ferry.transit_time;
        }

        time++;
    }

    return out;
}

void print_arrival_times(vector<unsigned int> out) {
    ostringstream oss;
    for (auto const& o : out)
        oss << o << '\n';
    cout << oss.str();
}

int main() {
    auto in = read_in();
    auto arrival_times = calc_arrival_times(in.ferry, in.car_stream);
    print_arrival_times(arrival_times);
}
