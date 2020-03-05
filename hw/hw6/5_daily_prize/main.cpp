#include <cmath>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;
using ULL = unsigned long long;
using Receipts = vector<vector<unsigned int>>;
using MaxHeap = priority_queue<unsigned int>;
using MinHeap =
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>>;

Receipts read_in() {
    unsigned int days_cnt, daily_receipt_cnt, x;
    cin >> days_cnt;
    Receipts receipts(days_cnt);
    for (unsigned int day = 0; day < days_cnt; day++) {
        cin >> daily_receipt_cnt;
        for (unsigned int i = 0; i < daily_receipt_cnt; i++) {
            cin >> x;
            receipts[day].push_back(x);
        }
    }
    return receipts;
}

ULL calc_prizes(Receipts& receipts) {
    MinHeap minheap;
    MaxHeap maxheap;
    ostringstream oss;
    ULL total = 0;

    for (auto const& daily : receipts) {
        for (auto const& rct : daily) {
            minheap.push(rct);
            maxheap.push(rct);
        }
        unsigned int min_rct = minheap.top();
        unsigned int max_rct = maxheap.top();
        minheap.pop();
        maxheap.pop();
        total += min(max_rct - min_rct, (unsigned int)1000000);
    }

    return total;
}

int main() {
    auto receipts = read_in();
    cout << calc_prizes(receipts) << endl;
}
