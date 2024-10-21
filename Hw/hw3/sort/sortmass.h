#include <iostream>
#include <vector>

using ObjMassPair = std::pair<std::string, double>; //this defines the type ObjMassPair to be std::pair<std::string, double>

//define the operator << here
//define a function that compares ObjMassPair objects here (for use by std::sort)
// --- Your code here
std::ostream& operator<< (std::ostream& out, const std::vector<ObjMassPair>& obj_mass){

    for(const auto& obj : obj_mass){
        out << obj.first << " " << obj.second << std::endl;
    }

    return out;
}

bool compare(const ObjMassPair& obj1, const ObjMassPair& obj2){
    return obj1.second < obj2.second;  // if true, has higher priority, goes to end of vector
}
// ---
