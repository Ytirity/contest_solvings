#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

int main(){
	std::ifstream in("input.txt");

	int answ = 0;
	int curr = 0;
	std::vector<int> counts;

	
	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);

		if (line.size() == 0){
			std::cout << 'b' << curr << '\n';
			answ = std::max(answ, curr);
			curr = 0;
		} else {
			int tmp;
			iss >> tmp;
			std::cout << 'a' << tmp << '\n';
			curr += tmp;
		}
	}
	std::cout << '\n' << std::max(answ, curr) << '\n';
	return 0;
}