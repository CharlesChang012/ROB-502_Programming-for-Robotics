#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>


int main() {
    // HINT: consider using std::to_string and std::reverse
    unsigned long largest_palandrome{0};
    // --- Your code here

    for(int i = 100; i < 1000; i++){
        for(int j = i; j < 1000; j++){
            long int product = i * j;
            std::string product_str = std::to_string(product);

            int l = 0;
            int r = product_str.size()-1;

            bool is_palindrome = true;

            while(l < r){
                if(product_str[l] != product_str[r]){
                    is_palindrome = false;
                    break;
                }
                l++;
                r--;
            }

            if(is_palindrome && product > largest_palandrome) largest_palandrome = product;
        }
    }

    // ---
    std::cout << largest_palandrome << std::endl;
    return 0;
}
