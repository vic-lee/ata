/**
 * C++ Implementation of the valid parenthesis problem. 
 * src: https://leetcode.com/problems/valid-parentheses/
 * Runtime: 0 ms
 * Memory Usage: 8.7 MB
 */

#include <map>
#include <stack>

class Solution
{
public:
    bool isValid(std::string s)
    {
        std::map<char, char> close_open_map = {{')', '('},
                                               {'}', '{'},
                                               {']', '['}};
        std::stack<char> stk;
        for (char &c : s)
        {
            if (close_open_map.find(c) == close_open_map.end())
            {
                stk.push(c);
            }
            else
            {
                if ((!stk.empty()) && stk.top() == close_open_map[c])
                    stk.pop();
                else
                    return false;
            }
        }
        return stk.empty();
    }
};