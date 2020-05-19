#include <iostream>
#include <stdio.h>
#include <inttypes.h>

using namespace std;

int main() {
    int32_t input;
    cin >> input;

    int32_t b0,b1,b2,b3;
    int32_t output;

    b0 = (input & 0x000000ff) << 24u;
    b1 = (input & 0x0000ff00) <<  8u;
    b2 = (input & 0x00ff0000) >>  8u;
    b3 = (input & 0xff000000) >> 24u;

    output = b0 | b1 | b2 | b3;

    printf("%d converts to %d", input, output);
}