#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

int main(){
	std::ifstream in("input.txt");

	int answ = 0;

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		
		int a1, a2, b1, b2;
		char tmp;
		iss >> a1 >> tmp >> a2 >> tmp >> b1 >> tmp >> b2;
		
		if (a1 == b1 || a2 == b2 || ((a1 < b1) == (a2 > b2)))
			answ++;
	}

	std::cout << answ << '\n';

	return 0;
}