#include <iostream>

int main() {
    // --- Your code here
    int difference = 0;
    int squareSum = 0;
    int sumSquare = 0;

    for(int i = 1; i <= 100; i++){
        squareSum += (i * i);
    }

    sumSquare = ((1+100) * (100/2)) * ((1+100) * (100/2));

    difference = sumSquare - squareSum;

    // ---
    std::cout << difference << std::endl;
    return 0;
}