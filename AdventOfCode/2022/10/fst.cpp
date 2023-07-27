#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <unordered_set>
#include <utility>
#include <climits>

using namespace std;

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");
	int reg = 1;
	int timer = 1;

	vector<int> checks = {20, 60, 100, 140, 180, 220};
	int curr_check = 0;

	int answ = 0;

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		string command;
		iss >> command;

		if (command == "noop"){
			timer++;
		} else{
			int val;
			iss >> val;
			reg += val;
			timer += 2;
			//cout << reg << '\n';
		}

		if (curr_check < checks.size() && checks[curr_check] <= timer + 1){
			answ += (reg * checks[curr_check]);
			cout << reg << ' ' << (reg * checks[curr_check]) << '\n';
			curr_check++;
		}

	}

	cout << answ;

	return 0;
}