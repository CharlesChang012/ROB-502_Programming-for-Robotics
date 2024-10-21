#include "robots.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;


//define and implement a function here called compareBotsByName
//it should be of the proper form to be used as the comparison
//function in std::sort. You will use compareBotsByName and std::sort
//to sort a std::vector<Robot>
// --- Your code here
bool compareBotsByName(const Robot& bot1, const Robot& bot2){

	string bot1Name = bot1.getName();
	string bot2Name = bot2.getName();

	for(int i = 0; i < bot1Name.size() && i < bot1Name.size(); i++	){
		if(bot1Name[i] < bot2Name[i]) return true;
		else if(bot1Name[i] > bot2Name[i]) return false;
	}

	return bot1Name.size() < bot2Name.size();
}
// ---


int main() {
	ifstream botfile("bots.txt");
	ifstream jobfile("jobs.txt");
	ofstream outfile("output.txt");

	queue<Robot> bot_queue;

	//read the robots from botfile in to bot_queue
	//make sure you've looked at the definition 
	//of the Robot class in robots.h first
	// --- Your code here
	string botLine;
	while(getline(botfile, botLine)){
		istringstream iss(botLine);
		string botName, botType;
		if(iss >> botName >> botType){
			bot_queue.push(Robot(botName, botType));
		}
		
	}
	// ---

	//read in each job id and job in jobfile
	//and assign them to the robots as described in the problem
	// --- Your code here
	string jobLine;
	while(getline(jobfile, jobLine)){
		istringstream iss_(jobLine);
		int jobId;
		string jobJob;
		if(iss_ >> jobId >> jobJob){

			bool assigned = false;
			while(!assigned){

				Robot curBot = bot_queue.front();
				bot_queue.pop();
				string curBotType = curBot.getType();
				std::vector<std::string> curBotJob =  TYPES2JOBS.at(curBotType);

				if(find(curBotJob.begin(), curBotJob.end(), jobJob) != curBotJob.end()){
					curBot.assignJob(jobId);
					assigned = true;
				}

				bot_queue.push(curBot);
			}
		}
	}
	// ---


	vector<Robot> bots;

	//now that the jobs are assigned, get the robots from the queue
	//and put them in the bots vector
	//then sort that vector alphabetically using std::sort
	//you will need to use the compareBotsByName function above
	// --- Your code here
	while(!bot_queue.empty()){
		bots.push_back(bot_queue.front());
		bot_queue.pop();
	}

	sort(bots.begin(), bots.end(), compareBotsByName);
	// ---

	// print the bots to outfile and cout
	for (int i = 0; i < bots.size(); i++) {
		cout << bots[i].print(false);
		outfile << bots[i].print(false);
	}

	return 0;
}
