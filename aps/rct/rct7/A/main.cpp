#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using UIN = unsigned int;

struct EvenSubset {
    bool exists;
    vector<UIN> locs;
};

vector<vector<unsigned int>> read_in() {
    unsigned int case_cnt, num_cnt, num;
    cin >> case_cnt;
    vector<vector<unsigned int>> nums(case_cnt, vector<unsigned int>());

    for (unsigned int i = 0; i < case_cnt; i++) {
        cin >> num_cnt;
        nums[i] = vector<unsigned int>(num_cnt, 0);
        for (unsigned int j = 0; j < num_cnt; j++) {
            cin >> num;
            nums[i][j] = num;
        }
    }

    return nums;
}

EvenSubset find_even_subset(vector<UIN> nums) {
    EvenSubset es;
    es.exists = false;

    for (size_t i = 0; i < nums.size(); i++) {
        if (nums[i] % 2 == 0) {
            es.exists = true;
            es.locs.push_back(i + 1);
            return es;
        }
    }

    if (nums.size() >= 2) {
        es.exists = true;
        es.locs.push_back(1);
        es.locs.push_back(2);
    }

    return es;
}

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    auto nums = read_in();
    ostringstream oss;
    for (auto const& arr : nums) {
        auto res = find_even_subset(arr);
    }
}
