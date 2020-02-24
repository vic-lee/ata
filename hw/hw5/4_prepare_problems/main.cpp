#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Input {
    unsigned int initial_supply;
    vector<unsigned int> supply;
    vector<unsigned int> demand;
};

Input read_in() {
    Input in;
    in.supply = vector<unsigned int>(12, 0);
    in.demand = vector<unsigned int>(12, 0);
    cin >> in.initial_supply;
    unsigned int x;
    for (int i = 0; i < 12; i++) {
        cin >> x;
        in.supply[i] = x;
    }
    for (int i = 0; i < 12; i++) {
        cin >> x;
        in.demand[i] = x;
    }
    return in;
}

ostringstream prepare_problems(unsigned int initial_supply,
                               vector<unsigned int> supply,
                               vector<unsigned int> demand) {
    ostringstream oss;
    vector<unsigned int> avail = vector<unsigned int>(12, 0);

    avail[0] = initial_supply;
    if (avail[0] < demand[0]) {
        oss << "No homework.\n";
    } else {
        avail[0] -= demand[0];
        oss << "A lot of grading.\n";
    }

    for (int i = 1; i < 12; i++) {
        auto curr_availability = avail[i - 1] + supply[i - 1];
        if (curr_availability < demand[i]) {
            oss << "No homework.\n";
            avail[i] = curr_availability;
        } else {
            oss << "A lot of grading.\n";
            avail[i] = curr_availability - demand[i];
        }
    }

    return oss;
}

int main() {
    auto in = read_in();
    auto oss = prepare_problems(in.initial_supply, in.supply, in.demand);
    cout << oss.str();
}
