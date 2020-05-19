#include <algorithm>
#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define MAX_SOLDERS_CNT 100000

struct LossReport {
    unsigned int left;
    unsigned int right;
};

struct Input {
    unsigned int soldiers_cnt;
    vector<LossReport> reports;
};

Input read_in() {
    unsigned int soldiers_cnt, loss_report_cnt, l, r;
    cin >> soldiers_cnt >> loss_report_cnt;
    vector<LossReport> reports;
    for (int i = 0; i < loss_report_cnt; ++i) {
        cin >> l >> r;
        reports.push_back({l, r});
    }
    return {soldiers_cnt, reports};
}

ostringstream gen_pals(vector<LossReport> reports,
                       unsigned const int soldiers_cnt) {
    ostringstream oss;
    auto bs = bitset<MAX_SOLDERS_CNT>();
    bs.set();

    for (auto& report : reports) {
        for (int i = report.left - 1; i < report.right; ++i) {
            bs.reset(i);
        }

        int left = -1, right = soldiers_cnt + 1;
        for (int i = report.left - 2; i >= 0; --i) {
            if (bs.test(i)) {
                left = i + 1;
                break;
            }
        }
        if (left < 0)
            oss << "* ";
        else
            oss << left << " ";

        for (int i = report.right; i < soldiers_cnt; ++i) {
            if (bs.test(i)) {
                right = i + 1;
                break;
            }
        }
        if (right > soldiers_cnt)
            oss << "*";
        else
            oss << right;

        oss << '\n';
    }

    return oss;
}

int main() {
    auto in = read_in();
    cout << gen_pals(in.reports, in.soldiers_cnt).str();
}
