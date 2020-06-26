#include <stack>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> dailyTemperatures(vector<int>& T) {
        // if we cannot write to a certain location in the returned array,
        // that means there is no future temperature that is higher than the
        // current temperature at that point. For that we return 0.
        vector<int> res(T.size(), 0);

        // Invarant: this stack keeps track of all the temperatures that are
        // higher than the current temperature, in strictly increasing order.
        stack<size_t> stk;

        for (size_t curr = 0; curr < T.size(); curr++) {
            // unwind the stack until it's either empty or there is
            // no prior temperature that is lower than the current temperature
            // (for these lower temperatures we can now conveniently
            // calculate the diffs in indices).
            while (!stk.empty() && T[curr] > T[stk.top()]) {
                auto closestLowerTemp = stk.top();
                stk.pop();
                res[closestLowerTemp] = curr - closestLowerTemp;
            }

            // Add the current temperature for future consideration.
            stk.push(curr);
        }

        return res;
    }
};

int main() { auto s = Solution(); }