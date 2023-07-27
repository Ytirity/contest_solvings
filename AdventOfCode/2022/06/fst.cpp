#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;
int main(){
	std::ifstream in("input.txt");
	//std::ifstream in("test.txt");

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		
		string str;
		
		iss >> str;

		int place = -1;

		for (int i = 0; i < str.size() - 14; i++){
			for (int j = i + 1; j < i + 14; j++)
				for (int k = i; k < j; k++)
					if (str[j] == str[k]){
						cout << j << ' ' << str[j] << ' ' << k << ' ' << str[k] << '\n';
						goto next;
					}
					
			place = i;
			break;
			next:;
		}

		

		cout << place + 14 << '\n';
	}

	

	return 0;
}