#include <iostream>

int euler9() {
    // --- Your code here
    for(int i = 1; i <= 998; i++){
        int l = i+1;
        int r = 1000;
        while(l < r){
            if(i+l+r > 1000) r--;
            if(i+l+r < 1000) l++;
            if(i+l+r == 1000){
                if(i*i + l*l == r*r){
                    //std::cout << i << ", " << l << ", " << r << std::endl;
                    return i*l*r;
                }
                else l++;
            }
        }
    }


    // ---
}

int main() {
    // This code is a lot cleaner if you write it as a function, because you can use `return` once you find the answer
    int const product = euler9();
    std::cout << product << std::endl;
    return 0;
}