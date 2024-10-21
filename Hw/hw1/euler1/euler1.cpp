#include <iostream>
#include <string>

int main() {
    unsigned long answer = 0;
    // --- Your code here

    int num3 = 999/3;
    int max3 = num3 * 3;
    int num5 = 999/5;
    int max5 = num5 * 5;
    int num15 = 999/15;
    int max15 = num15 * 15;

    answer = ((3+max3)*num3 + (5+max5)*num5 - (15+max15)*num15)/2;

    // ---
    std::cout << answer << std::endl;
    return 0;
}