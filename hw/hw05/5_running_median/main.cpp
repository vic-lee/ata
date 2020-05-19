#include <deque>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using ULL = unsigned long long;
using MaxHeap = priority_queue<unsigned int>;
using MinHeap =
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>>;

deque<unsigned int> read_in() {
    deque<unsigned int> nums;
    string line;
    unsigned int x;
    while (getline(cin, line)) {
        if (line.find_first_not_of(' ') == string::npos)
            break;
        istringstream iss(line);
        nums.push_back(*istream_iterator<unsigned int>{iss});
    }
    return nums;
}

/**
 * Balance heap sizes (so that they differ by at most 1) by moving the top
 * element from source to destination. Args must be `MinHeap | MaxHeap`.
 */
template <typename T, typename K>
void balance_heap(T& src_heap, K& dst_heap) {
    auto top = src_heap.top();
    src_heap.pop();
    dst_heap.push(top);
}

deque<ULL> find_running_medians(deque<unsigned int>& input) {
    deque<ULL> medians(1, 0);
    MaxHeap lowerhalf;
    MinHeap upperhalf;

    while (input.size()) {
        auto next = input.front();
        input.pop_front();
        if (lowerhalf.size() > upperhalf.size()) {
            if (next < medians.back()) {
                balance_heap(lowerhalf, upperhalf);
                lowerhalf.push(next);
            } else {
                upperhalf.push(next);
            }
            ULL med = ((ULL)upperhalf.top() + (ULL)lowerhalf.top()) / 2;
            medians.push_back(med);
        } else if (lowerhalf.size() < upperhalf.size()) {
            if (next > medians.back()) {
                balance_heap(upperhalf, lowerhalf);
                upperhalf.push(next);
            } else {
                lowerhalf.push(next);
            }
            ULL med = ((ULL)upperhalf.top() + (ULL)lowerhalf.top()) / 2;
            medians.push_back(med);
        } else {
            if (next < medians.back()) {
                lowerhalf.push(next);
                medians.push_back(lowerhalf.top());
            } else {
                upperhalf.push(next);
                medians.push_back(upperhalf.top());
            }
        }
    }

    medians.pop_front();
    return medians;
}

void fmtout(deque<ULL> medians) {
    for (auto& m : medians)
        cout << m << endl;
}

int main() {
    auto in = read_in();
    auto medians = find_running_medians(in);
    fmtout(medians);
}
