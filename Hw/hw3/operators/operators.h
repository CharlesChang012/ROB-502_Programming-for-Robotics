#include <iostream>
#include <vector>

#define ERROR_MESSAGE std::invalid_argument("Error: vectors must be the same size")

// --- Your code here
using namespace std;

template <typename T1, typename T2>
vector<double> operator+(const vector<T1>& v1, const vector<T2>& v2){
    
    if(v1.size() != v2.size()) throw ERROR_MESSAGE;
    
    vector<double> res(v1.size(), 0);

    for(int i = 0; i < v1.size(); i++){
        res[i] = double(v1[i]) + double(v2[i]);
    }

    return res;
}

template <typename T1, typename T2>
vector<double> operator-(const vector<T1>& v1, const vector<T2>& v2){
    
    if(v1.size() != v2.size()) throw ERROR_MESSAGE;
    
    vector<double> res(v1.size(), 0);

    for(int i = 0; i < v1.size(); i++){
        res[i] = double(v1[i]) - double(v2[i]);
    }

    return res;
}

template <typename T1, typename T2>
vector<double> operator*(const vector<T1>& v1, const vector<T2>& v2){
    
    if(v1.size() != v2.size()) throw ERROR_MESSAGE;
    
    vector<double> res(v1.size(), 0);

    for(int i = 0; i < v1.size(); i++){
        res[i] = double(v1[i]) * double(v2[i]);
    }

    return res;
}

template <typename T1, typename T2>
vector<double> operator*(const T1& a, const vector<T2>& v2){
    
    vector<double> res(v2.size(), 0);

    for(int i = 0; i < v2.size(); i++){
        res[i] = double(a) * double(v2[i]);
    }

    return res;
}

template <typename T1, typename T2>
vector<double> operator/(const vector<T1>& v1, const T2& a){
    
    vector<double> res(v1.size(), 0);

    for(int i = 0; i < v1.size(); i++){
        res[i] = double(v1[i]) / double(a);
    }

    return res;
}

template <typename T1, typename T2>
vector<double> operator,(const vector<T1>& v1, const vector<T2>& v2){
    
    vector<double> res;

    for (const auto& n : v1) {
        res.push_back(static_cast<double>(n));
    }

    for (const auto& n : v2) {
        res.push_back(static_cast<double>(n));
    }

    return res;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const vector<T>& v){

    for(int i = 0; i < v.size(); i++){
        if(i == 0) out << "[" << v[i];
        else out << ", " << v[i];
    }

    out << "]";

    return out;
}

// ---
