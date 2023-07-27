#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

int main(){
	std::ifstream in("input.txt");

	//r: A X
	//p: B Y
	//s: C Z

	int answ = 0;
	int scores[3] = {3, 0, 6};
	int values[3] = {1, 2, 3};

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		char a, x;
		iss >> a >> x;
		std::cout << a << ' ' << x << '\n';

		answ += values[x - 'X'];
		answ += scores[((a - 'A' - (x - 'X')) + 3) % 3];

		std::cout << answ << '\n';
	}

	std::cout << answ << '\n';

	return 0;
}