#include <iostream>
#include <fstream>
// below are some includes that are hints for what could make things easier
#include <string>
#include <vector>
#include <algorithm>

void processLine(std::string& line, int lineNumber, int* counter) {
    // line is passed in by reference, so you can modify it directly
    // do not return anything from this function
    // --- Your code here
    for(auto& c : line){
        if(c == 'e'){
            c = '3';
            *counter += 3 * lineNumber;
        }
        else if(c == 'l'){
            c = '1';
            *counter += 1 * lineNumber;
        }
        else if(c == 't'){
            c = '7'; 
            *counter += 7 * lineNumber;
        }  
    }
    // ---
}

int* createCounter() {
    // this is a contrived function to get you more familiar with heap allocation
    // if you return a pointer to a local variable (on the stack), that value will be invalid after the return
    // and accessing it will be unexpected behavior (probably a segfault)
    // remember to initialize it to 0
    // --- Your code here
    int* cnter = new int(0);
    return cnter;
    // ---
}

int main() {

    // you will need to read the API of std::ofstream and std::ifstream
    std::ifstream input{"input.txt"};
    std::vector<std::string> lines;
    std::string line;

    // create a reference to the pointed value
    // references can be used more conveniently than pointers
    // note that the processLine function takes counter as a pointer, so you have to address it with &
    // contrived example to get you more familiar with going between references and pointers
    // usually there will not be so many unnecessary conversions
    int& counter = *createCounter();

    // --- Your code here
    // Read in each line from the file.
    while(getline(input, line)){
        lines.push_back(line);
    }
    reverse(lines.begin(), lines.end());
    input.close();

    // process each line
    for(int i = 0; i < lines.size(); i++){
        processLine(lines[i], lines.size()-1-i, &counter);
        //std::cout << counter << std::endl;
    }
    // ---

    // output
    // --- Your code here
    std::ofstream output("./output.txt");
    for(int i = 0; i < lines.size(); i++){
        output << lines[i] << std::endl;
    }
    output << counter;
    output.close();
    // ---

    delete &counter;
}