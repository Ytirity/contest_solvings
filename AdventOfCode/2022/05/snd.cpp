#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;
int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	vector<string> crates{"SLW", "JTNQ", "SCHFJ", "TRMWNGB", "TRLSDHQB",
						 "MJBVFHRL", "DWRNJM", "BZTFHNDJ", "HLQNBFT"};

	//vector<string> crates{"ZN", "MCD", "P"};

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		
		int count, from, to;
		string tmp;
		iss >> tmp >> count >> tmp >> from >> tmp >> to;

		//reverse(crates[from - 1].end() - count, crates[from - 1].end());
		crates[to - 1].append(crates[from - 1].end() - count, crates[from - 1].end());
		crates[from - 1].erase(crates[from - 1].end() - count, crates[from - 1].end());

		cout << count << ' ' << from << ' ' << to << '\n';

		for (string& crate : crates){
			cout << crate << '\n';
		}
		cout << '\n';
	}

	

	return 0;
}