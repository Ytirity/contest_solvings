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
		std::string str;
		iss >> str;
		std::cout << str << '\n';

		bool l_half[52] = {false};

		for (int i = 0; i < str.size() / 2; i++){
			int l_val = (str[i] > 'Z' ? str[i] - 'a' : str[i] - 'A' + 26);

			l_half[l_val] = true;
		
		}

		for (int i = str.size() / 2; i < str.size(); i++){
			int r_val = (str[i] > 'Z' ? str[i] - 'a' : str[i] - 'A' + 26);

			if (l_half[r_val]){
				answ += (r_val + 1);
				break;
			}
		}

		std::cout << answ << '\n';
	}

	std::cout << answ << '\n';

	return 0;
}