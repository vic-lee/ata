#include <iostream>

int maximum(int a, int b, int c) {
    if (a > b) {
        return std::max(a, c);
    } else {
        return std::max(b, c);
    }
}

int main() {
    int input_count;
    std::cin >> input_count;

    int chest_count = 0, bicep_count = 0, back_count = 0;

    for (int i = 0; i < input_count; i++) {
        int incr;
        std::cin >> incr;
        if (i % 3 == 0) {
            chest_count += incr;
        } else if (i % 3 == 1) {
            bicep_count += incr;
        } else {
            back_count += incr;
        }
    }

    int sol = maximum(chest_count, bicep_count, back_count);
    if (sol == chest_count) {
        std::cout << "chest" << std::endl;
    } else if (sol == bicep_count) {
        std::cout << "biceps" << std::endl;
    } else {
        std::cout << "back" << std::endl;
    }
}