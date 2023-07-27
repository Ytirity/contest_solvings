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
	int scores[3] = {0, 3, 6};
	int values[3] = {1, 2, 3};

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		char a, x;
		iss >> a >> x;
		std::cout << a << ' ' << x << '\n';

		answ += scores[x - 'X'];
		answ += values[((a - 'A' + (x - 'X')) + 2) % 3];

		std::cout << answ << '\n';
	}

	std::cout << answ << '\n';

	return 0;
}


/*
AY 1  0 1
BX 1  1 0
CZ 1  2 2

AX 0 0   3
AY 0 1   1
AZ 0 2   2

BX 1 0   1
BY 1 1   2
BZ 1 2   3

CX 2 0   2
CY 2 1   3
CZ 2 2   1
*/