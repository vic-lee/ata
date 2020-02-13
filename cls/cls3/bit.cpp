#include <iostream>

using namespace std;

int main() {
    int x;
    for (int i = 0; i < 16; i++) x = x | x << i;
    
}