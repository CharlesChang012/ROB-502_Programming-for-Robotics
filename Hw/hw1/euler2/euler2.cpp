#include <iostream>
#include <string>

int main() {
    // you'll need to store the answer in a variable named 'sum'
    // --- Your code here
    int first = 1;
    int second = 1;
    int cur = first + second;
    int sum = 0;

    while(cur <= 4*10e5){
        
        if(cur % 2 == 0) sum += cur;
        first = second;
        second = cur;
        cur = first + second;
    }

    // ---tcpp 
    std::cout << sum << std::endl;
    return 0;
}