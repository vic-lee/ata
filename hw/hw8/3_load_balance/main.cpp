#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

template <typename T>
void print_iterable(T items) {
    ostringstream oss;
    for (auto const& item : items) {
        oss << item << '\n';
    }
    cout << oss.str();
}

struct Input {
    vector<UIN> tasks;
    UIN num_nodes;
    UIN num_tasks;
};

Input read_in() {
    Input in;
    cin >> in.num_nodes >> in.num_tasks;
    in.tasks = vector<UIN>(2 * in.num_nodes, 0);
    for (size_t i = 0; i < in.num_tasks; i++)
        cin >> in.tasks[i];
    return in;
}

double balance_load(vector<UIN>& tasks, UIN num_nodes) {
    int sum = accumulate(tasks.begin(), tasks.end(), 0);
    double avg = (double)sum / num_nodes;
    double imbalance = 0.0;

    sort(tasks.begin(), tasks.end());
    for (size_t i = 0; i < tasks.size() / 2; i++) {
        double load = tasks[i] + tasks[tasks.size() - i - 1];
        imbalance += abs(avg - load);
    }

    return imbalance;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);

    auto in = read_in();
    double imbalance = balance_load(in.tasks, in.num_nodes);
    cout << "IMBALANCE = " << fixed << setprecision(5) << imbalance << endl;
}
