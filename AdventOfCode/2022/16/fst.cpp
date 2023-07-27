#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <unordered_map>
#include <queue>
#include <array>

using namespace std;


int stateToFlow(int state, vector<int>& flowrate){
	int answ = 0;
	for (int i = 0; i < flowrate.size(); i++)
		if (state & (1 << i))
			answ += flowrate[i];
	return answ;
}

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	std::regex data_regex("Valve ([A-Z]{2}) has flow rate=([0-9]+); tunnels? leads? to valves? ([A-Z, ]+)");

	unordered_map<string, int> strToNum;
	vector<vector<int>> graph;

	unordered_map<int, int> numToPlace; // in flowrate
	vector<int> flowrate;

	int amount = 0;
	int amountActive = 0;

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex)){

			string curr = matches[1].str();
			if (strToNum.count(curr) == 0){
				strToNum[curr] = amount++;
				graph.push_back(vector<int>());
			}

			int fl_r = stoi(matches[2].str());
			if (fl_r != 0){
				numToPlace[strToNum[curr]] = amountActive++;
				flowrate.push_back(fl_r);
			}

			string connections = matches[3].str();
			for (int i = 0; i < connections.size(); i+= 4){
				string nxt(connections.begin() + i, connections.begin() + i + 2 );

				if (strToNum.count(nxt) == 0){
					strToNum[nxt] = amount++;
					graph.push_back(vector<int>());
				}

				graph[strToNum[curr]].push_back(strToNum[nxt]);
			}
		}

	}

	vector<vector<int>> states(1 << flowrate.size(), vector<int>(amount, -1)); // [state][pos] = max_amount
	const int TIMER = 30;

	queue<array<int, 3>> toConsider;
	toConsider.push({0, strToNum["AA"], 0}); // state, curr_pos

	for (int t = 0; t < TIMER; t++){
		int lvl = toConsider.size();
		for (int i = 0; i < lvl; i++){
			array<int, 3> curr = toConsider.front();
			toConsider.pop();

			if (curr.at(2) > states[curr.at(0)][curr.at(1)]){
				int state = curr.at(0), place = curr.at(1), neu_amount = curr.at(2);
				states[state][place] = neu_amount;

				for (int next : graph[place])
					toConsider.push({state, next, neu_amount + stateToFlow(state, flowrate)});

				if (numToPlace.count(place) != 0){
					state = state | (1 << numToPlace[place]);
					toConsider.push({state, place, neu_amount + stateToFlow(state, flowrate)});
				}

			}
			
		}
	}

	int answ = 0;
	for (vector<int>& p : states)
		for (int val : p)
			answ = max(answ, val);

	cout << answ << '\n';

	return 0;
}