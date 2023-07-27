#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

int main(){
	std::ifstream in("input.txt");

	int curr = 0;
	std::vector<int> counts;

	
	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);

		if (line.size() == 0){
			counts.push_back(curr);
			curr = 0;
		} else {
			int tmp;
			iss >> tmp;
			curr += tmp;
		}
	}

	counts.push_back(curr);

	std::sort(counts.begin(), counts.end(), std::greater<int>());

	std::cout << counts[0] << ' ' << counts[1] << ' ' << counts[2] << '\n';
	std::cout << counts[0] + counts[1] + counts[2] << '\n';
	return 0;
}