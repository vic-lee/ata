#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // sort the people array in-place to avoid additional memory allocation,
        // as did the previous implementation.
        sort(people.begin(), people.end(),
             [](const vector<int>& one, const vector<int>& other) {
                 // for each person (<height, # ppl shorter than them>)
                 // sort them by descending height.
                 // For 2 people with the same height, sort them by the second
                 // parameter, in ascending order.
                 return one[0] > other[0] ||
                        (one[0] == other[0] && one[1] < other[1]);
             });

        vector<vector<int>> res;
        res.reserve(people.size());

        for (auto const& ppl : people) {
            res.insert(res.begin() + ppl[1], ppl);
        }

        return res;
    }
};

int main() { auto s = Solution(); }