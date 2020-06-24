#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;
using ReminderMap = map<int, int>;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

tuple<ReminderMap, int> read_in() {
    string word;
    int id, interval, num_alerts;
    ReminderMap reminders;
    while (true) {
        cin >> word;
        if (word == "#") {
            break;
        }
        cin >> id >> interval;
        reminders[id] = interval;
    }
    cin >> num_alerts;
    return {reminders, num_alerts};
}

ostringstream calc(int num_alerts, ReminderMap& reminders) {
    ostringstream oss;
    int time = 1;
    while (num_alerts > 0) {
        for (auto it = reminders.begin(); it != reminders.end(); it++) {
            auto id = it->first, interval = it->second;
            if (time % interval == 0) {
                oss << id << '\n';
                num_alerts--;
                if (num_alerts == 0)
                    break;
            }
        }
        time++;
    }
    return oss;
}

void fmtout() {}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto [reminders, num_alerts] = read_in();
    cout << calc(num_alerts, reminders).str();
}
