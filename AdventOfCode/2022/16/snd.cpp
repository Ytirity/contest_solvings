#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <unordered_map>
#include <bitset>

using namespace std;

typedef unsigned long ulong;
constexpr int TOTAL = 15;

int getFlowsTick(bitset<TOTAL>& flow, vector<int>& flowrate){
	int answ = 0;
	for (int i = 0; i < flowrate.size(); i++)
		if (flow.test(i))
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

	int statesAmount = 1 << flowrate.size();
	cout << "total " << flowrate.size() << " statesAmount " << statesAmount << '\n';

	vector<vector<vector<int>>> states(statesAmount, vector<vector<int>>(amount, vector<int>(amount, -1))); // [state][posMe][posEl] = max_amount
	states[0][strToNum["AA"]][strToNum["AA"]] = 0;
	vector<vector<vector<int>>> statesNext(statesAmount, vector<vector<int>>(amount, vector<int>(amount, -1)));
	const int TIMER = 26;
	
	for (int t = 0; t < TIMER; t++){
		cout << "timer: " << t << '\n';

		for (ulong st = 0; st < statesAmount; st++){
			bitset<TOTAL> flow(st);
			for (int posMe = 0; posMe < amount; posMe++)
				for (int posEl = 0; posEl < amount; posEl++)
					if (states[st][posMe][posEl] != -1){
						int flowAddoned = states[st][posMe][posEl] + getFlowsTick(flow, flowrate);
						
						// both open
						if (numToPlace.count(posMe) && numToPlace.count(posEl)){
							bitset<TOTAL> nFlow(flow);
							nFlow.set(numToPlace[posMe]);
							nFlow.set(numToPlace[posEl]);
							statesNext[nFlow.to_ulong()][posMe][posEl] = max(statesNext[nFlow.to_ulong()][posMe][posEl], flowAddoned);
						}

						// Me open
						if (numToPlace.count(posMe)){
							bitset<TOTAL> nFlow(flow);
							nFlow.set(numToPlace[posMe]);
							for (int nextPos : graph[posEl])
								statesNext[nFlow.to_ulong()][posMe][nextPos] = max(statesNext[nFlow.to_ulong()][posMe][nextPos], flowAddoned);
							
						}

						// El open
						if (numToPlace.count(posEl)){
							bitset<TOTAL> nFlow(flow);
							nFlow.set(numToPlace[posEl]);
							for (int nextPos : graph[posMe])
								statesNext[nFlow.to_ulong()][nextPos][posEl] = max(statesNext[nFlow.to_ulong()][nextPos][posEl], flowAddoned);
						}

						// moving
						for (int nextMePos : graph[posMe])
							for (int nextElPos : graph[posEl])
								statesNext[st][nextMePos][nextElPos] = max(statesNext[st][nextMePos][nextElPos], flowAddoned);
					}
		}
		swap(states, statesNext);
	}

	int answ = 0;
	for (vector<vector<int>>& v : states)
		for (vector<int>& p : v)
			for (int val : p)
				answ = max(answ, val);

	cout << answ << '\n';

	return 0;
}


// можно быстрее -  посчитать для каждой вершины travelTime до других (https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)

// тот же массив [state][posM][posE], только теперь ходим по сокращенному графу (64 -> 16), но ещё добавляется таймер(26)

// пересчёт: для state - пытаемся придти во все !=0 вершины(timer += travelTime) и смотрим как будет максимальней
// придти == придти и включить (а то в чём смысл)

// 2^state * 16*16 * 16*16 * 26