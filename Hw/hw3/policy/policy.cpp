#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
using namespace std;


using State = vector<int>; //this defines the type State to be a vector of ints
using Action = vector<int>; //this defines the type Action to be a vector of ints


//this function should print out a state to the given stream
//the ostream could be something like cout, or cerr
//or it could be a filestream
void printState(const State& state, ostream & stream){
    // --- Your code here
    
    stream << state[0] << " " << state[1];

    // ---
}


State dynamics(const State& state, const Action& action)
{
    State next_state(state.size());
    for (int j = 0; j < state.size();j++)
    {
        next_state[j] = state[j] + action[j];
    }
    return next_state;
}


int main () {
    
    ifstream policyfile("policy.txt");
    ofstream outputfile("output.txt");

    const int StateSize = 2;
    const int ActionSize = 2;    

    State key(StateSize);
    Action value(ActionSize);
    map<State,Action> policy;

    //read the policy file information into std::pair objects,
    //insert each std::pair into the map
    // --- Your code here
    string line;
    while(getline(policyfile, line)){
        istringstream iss(line);
        int key_x, key_y, val_x, val_y;
        if(iss >> key_x >> key_y >> val_x >> val_y){
            key[0] = key_x;
            key[1] = key_y;
            value[0] = val_x;
            value[1] = val_y;
            policy[key] = value;
        }
    }

    policyfile.close();
    // ---

    //optional (but recommended) print out the policy to cout
    //to make sure that it was read in correctly
    // --- Your code here
    std::cout << "Policy read from file:" << endl;
    for(const auto& pair : policy){
        std::cout << "State: ";
        printState(pair.first, std::cout);
        std::cout << " -> Action: ";
        printState(pair.second, std::cout);
        std::cout << endl;
    }

    // ---

    //read in rollout
    ifstream rolloutfile ("rollout.txt");
    State startState(StateSize); //this stores the start stae
    int numSteps; //this is the number of steps in the rollout
    rolloutfile>>startState[0];
    rolloutfile>>startState[1];
    rolloutfile>>numSteps;
    rolloutfile.close();

    //Now use the the policy map to do the rollout
    // --- Your code here
    int stepCnt = 0;
    outputfile << startState[0] << " " << startState[1] << endl;

    State curState(StateSize);
    curState[0] = startState[0];
    curState[1] = startState[1];

    while(stepCnt < numSteps){ 
        
        if(policy.find(curState) == policy.end()){
            cerr << "State " << curState[0] << " " << curState[1] << " is not in policy, terminating.";
            return 1;
        }

        curState = dynamics(curState, policy[curState]);

        outputfile << curState[0] << " " << curState[1] << endl;
        stepCnt++;
    }
    // ---

    outputfile.close();
    return 0;
}
