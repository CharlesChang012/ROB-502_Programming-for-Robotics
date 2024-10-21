#include <fstream>
#include <iostream>

// --- Your code here
#include <sstream>
#include <vector>

using namespace std;
// ---

int main()
{
    ifstream infile("input.txt");
    ofstream outfile("output.txt");

    //Read in each line from the input file,
    //perform the specified operation on the numbers,
    //and write the results to the ouputfile.
    //Remember to check if the specified operation is possible!
    // --- Your code here
    while(infile.peek() != std::ifstream::traits_type::eof()){
        vector<string> func;
        std::string str;
        std::string line;
        std::getline(infile, line);
        std::stringstream ss(line);
        while(ss >> str){
            func.push_back(str);
        }
        
        bool error = false;

        if(func.size() == 1 || (func.back() != "+" && func.back() != "*" && func.back() != "/") || (func.back() == "/" && func.size() != 3)){
            outfile << "ERROR" << endl;
            continue;
        }

        double res = stod(func[0]);

        for(int i = 1; i < func.size()-1; i++){

            if(func.back() == "+") res += stod(func[i]);
            else if(func.back() == "*") res *= stod(func[i]);
            else{

                if(stod(func[i]) == 0){
                    error = true;
                    break;
                }
                else res /= stod(func[i]);
            }
        }

        if(error) outfile << "ERROR" << endl;
        else outfile << res << endl;
    }

    // ---
    return 0;
}
