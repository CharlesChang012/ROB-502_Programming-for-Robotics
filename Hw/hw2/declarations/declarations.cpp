// --- Your code here
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

std::string repeatString(std::string str, int cnt){
    std::string out;
    for(int i = 0; i < cnt; i++){
        out.append(str);
    }

    return out;
}

long double multiply(double n1, double n2){
    return n1*n2;
}
// ---

// include the standard library files that defines the std:: functions
int main() {
    // --- Your code here



    // ---
    
	// declare the variables used below
	double some_number = 5.5;
    // std::endl and '\n' are equivalent
	std::cout << some_number << ' ' << std::round(some_number + M_PI) << '\n';

    // this one may be a bit tricky since you can't assign a string literal to char* in C++ 
	std::string some_string = "my string";
	std::cout << some_string << '\n';

    // implement this function
    // should print empty string
    std::cout << repeatString(some_string, 0) << std::endl;
    // should print it 5 times, with nothing separating them
    std::cout << repeatString(some_string, 5) << std::endl;
	
	// there are many numerical types, each with different signedness and size
	// declare the appropriate types for them such that none of them overflow
    // note that 2^32 ~= 4 billion
    long large_number = 1000000;
    large_number *= 3;
    std::cout << large_number << std::endl;

    long long even_larger_number = large_number * large_number;
    std::cout << even_larger_number << std::endl;

    // implement this multiply function
    std::cout << std::fixed << std::setprecision(1) << multiply(large_number, even_larger_number) << std::endl;
    // beware of numeric types' signedness
    signed int negative_number = -250;
    std::cout << negative_number << std::endl;
}