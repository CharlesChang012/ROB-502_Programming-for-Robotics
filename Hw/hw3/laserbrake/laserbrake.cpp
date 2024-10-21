#include <fstream>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include <stdint.h>

double DEG2RAD = M_PI / 180; //this definition will be useful

using namespace std;

int main() {
    ifstream scanfile("input.txt");
    ofstream outfile("output.txt");
    cout << setprecision(4); //this sets how many decimal places to print
    outfile << setprecision(4);


    double robot_width;
    double threshold;

    string input;
    for(int i=0; i < 2; i++)
    {
    scanfile >> input;
    if (input == "width:")
        scanfile >> robot_width;
    else if (input == "threshold:")
        scanfile >> threshold;
    }
    cout << "Width: " << robot_width << ", Threshold: " << threshold << endl;
    double temp;
    vector<double> scan_returns;
    while (scanfile >> temp) {
    scan_returns.push_back(temp);
    cout << scan_returns[scan_returns.size()-1] << " ";
    }
    cout << endl;

    double resolution =
        180.0 / (scan_returns.size() - 1); // assume last scan is at 180
    cout << "Resolution: " << resolution << " degrees" << endl;


    // convert each scan return to x,y coordinates, and write to output.txt
    // --- Your code here
    vector<pair<double, double>> data;
    for(int i = 0; i < scan_returns.size(); i++){

        double x = scan_returns[i] * cos(resolution*i*DEG2RAD);
        double y = scan_returns[i] * sin(resolution*i*DEG2RAD);
        data.push_back(make_pair(x, y));

        outfile << x << " " << y << endl;
    }
    // ---

    //check if each point is 1) in front of the robot and 
    //2) closer than the threshold (in y)
    // --- Your code here
    bool stop = false;
    for(int i = 0; i < data.size(); i++){
        if(abs(data[i].first) <= robot_width/2 && scan_returns[i] <= threshold){
            stop = true;
            outfile << "Stop! " << i << endl;
            break;
        }
    }

    if(!stop) outfile << "OK" << endl;

    // ---
    return 0;
}
