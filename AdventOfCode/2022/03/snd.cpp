#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

int main(){
	std::ifstream in("input.txt");

	int answ = 0;
	int count = 0;

	bool bags[52][2] = {false};

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		std::string str;
		iss >> str;
		std::cout << str << '\n';

		
		if (count = (count + 1) % 3)
			for (char ch : str){
				int val = (ch > 'Z' ? ch - 'a' : ch - 'A' + 26);
				bags[val][count - 1] = true;
			} 
		else 
			for (char ch : str){
				int val = (ch > 'Z' ? ch - 'a' : ch - 'A' + 26);

				if (bags[val][0] && bags[val][1]){
					answ += (val + 1);

					for (int i = 0; i < 52; i++)
						bags[i][0] = bags[i][1] = false;
					break;
				}
			}


		std::cout << answ << '\n';
	}

	std::cout << answ << '\n';

	return 0;
}