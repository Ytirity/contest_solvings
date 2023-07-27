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
	int new_reg = 1;
	int countdown = 0;

	vector<string> screen = vector<string>(6);
	for (string& str : screen)
		for (int i = 0; i < 40; i++)
			str += '.';

	for (int pos = 0; pos <= screen.size() * screen[0].size(); pos++){
		if (countdown == 0)
			reg = new_reg;

		if (std::string line; countdown == 0 && std::getline(in, line)){
			std::istringstream iss(line);
			string command;
			iss >> command;

			if (command == "noop")
				countdown++;
			else {
				int val;
				iss >> val;
				new_reg += val;
				countdown += 2;
			}
		}

		countdown--;

		if (reg - 1 <= pos % screen[0].size() && pos % screen[0].size() <= reg + 1)
			screen[pos / screen[0].size()][pos % screen[0].size()] = '#';
	}
	for (const string& str : screen)
		cout << str << '\n';

	return 0;
}