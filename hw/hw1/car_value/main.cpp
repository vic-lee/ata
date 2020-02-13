#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Keep track of the bank balance and the car value, as well as a month tracker.
 * The first time car value > bank balance (if there is), print and exit.
 */
int main() {
    int duration, depr_record_cnt;
    float down_pmt, loan_amt;

    vector<int> months;
    vector<float> depr_pcts;

    scanf("%d %f %f %d", &duration, &down_pmt, &loan_amt, &depr_record_cnt);
    for (int i = 0; i < depr_record_cnt; i++) {
        int month; float depr;
        scanf("%d %f", &month, &depr);
        months.push_back(month); depr_pcts.push_back(depr);
    }
    // cout << endl;

    // for (int i = 0; i < months.size(); i++) {
    //     cout << months[i] << " " << depr_pcts[i] << endl;
    // }

    int mo, next_mo = -1; float dp;

    if (months.size() > 0) {
        mo = months.front();
        dp = depr_pcts.front();
        months.erase(months.begin());
        depr_pcts.erase(depr_pcts.begin());
        if (months.size() > 0) next_mo = months.front();
    }

    // cout << "\n" << mo << " " << dp << " " << next_mo << endl;

    
    float car_val = loan_amt + down_pmt, loan_val = loan_amt;
    const float loan_pmt = loan_amt / duration;

    if (loan_val == 0 || duration == 0) {
        cout << "0 months" << endl;
        return 0;
    }

    for (int i = 0; i < duration; i++) {
        car_val = car_val * (1 - dp);
        loan_val = loan_val - loan_pmt;
        // printf("month: %d\tcar value: %f\tloan amount: %f\n", (i+1), car_val, loan_val);

        if (car_val > loan_val) {
            int m = i + 1;
            // cout << car_val << ' ' << loan_val << endl;
            if (m == 1) {
                cout << m << " month" << endl;
            } else {
                cout << m << " months" << endl;
            }
            return 0;
        }

        if (next_mo != -1 && next_mo == i + 1) {
            mo = months.front();
            dp = depr_pcts.front();
            months.erase(months.begin());
            depr_pcts.erase(depr_pcts.begin());
            if (months.size() > 0) next_mo = months.front();
        }
    }
}