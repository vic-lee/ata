#include <iostream>

int main() {
    int problem_count;
    std::cin >> problem_count;
    int solved_count =;
    int a = 0, b = 0, c = 0;

    while (problem_count > 0) {
        std::cin >> a >> b >> c;
        if (a + b + c >= 2) solved_count++;
        a = 0; b = 0; c = 0;
        problem_count--;
    }

    std::cout << solved_count << std::endl;
}