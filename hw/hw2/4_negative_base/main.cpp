#include <iostream>
#include <sstream>
#include <string>

using namespace std; 
  
string toBaseTwo(int n) { 
    if (n == 0) return "0"; 

    string ans = ""; 
    while (n != 0) { 
        int next = n % -2; 
        n /= -2;
  
        if (next < 0) { 
            next += 2; 
            n += 1; 
        }
        ans = to_string(next) + ans; 
    } 
    return ans; 
} 

int main() { 
    int n; cin >> n;
    cout << toBaseTwo(n); 
}