#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <utility>

using namespace std;


pair<int, int> parsePoint(const string& str){
	int x = 0, y = 0;
	bool wasComma = false;
	for (int i = 0; i < str.size(); i++){
		if (str[i] == ','){
			wasComma = true;
			continue;
		}

		if (wasComma)
			y = y * 10 + (str[i] - '0');
		else
			x = x * 10 + (str[i] - '0');
	}

	return {x, y};
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");
	const int VERT = 200;
	const int HORZ = 600;
	const int SHIFT = 300;

	vector<vector<char>> layout(HORZ, vector<char>(VERT, '.'));

	int floor = 0;

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		string point, tmp;
		iss >> point;

		pair<int, int> curr = parsePoint(point);
		floor = max(floor, curr.second);
		while (iss >> tmp){
			iss >> point;

			pair<int, int> next = parsePoint(point);
			for (int i = min(curr.first, next.first); i <= max(curr.first, next.first); i++)
				for (int j = min(curr.second, next.second); j <= max(curr.second, next.second); j++) //одни из них равны
					layout[i - SHIFT][j] = '#';
				

			curr = next;
			floor = max(floor, curr.second);
		}
	}


	floor+=2;
	for (int i = 0; i < HORZ; i++)
		layout[i][floor] = '#';

	pair<int, int> sand_point = {500 - SHIFT, 0};
	layout[sand_point.first][sand_point.second] = '+';

	int answ = 0;
	while (layout[sand_point.first][sand_point.second] != 'o'){
		pair<int, int> curr_sand = sand_point;
		while (layout[curr_sand.first][curr_sand.second + 1] == '.' 
				|| layout[curr_sand.first - 1][curr_sand.second + 1] == '.' 
				|| layout[curr_sand.first + 1][curr_sand.second + 1] == '.'){

			if (layout[curr_sand.first][curr_sand.second + 1] == '.' )
				curr_sand.second++;
			else if (layout[curr_sand.first - 1][curr_sand.second + 1] == '.'){
				curr_sand.first--;
				curr_sand.second++;
			} else{
				curr_sand.first++;
				curr_sand.second++;
			}
		}

		layout[curr_sand.first][curr_sand.second] = 'o';
		answ++;
	}


	for (vector<char>& row : layout){
		for (char ch : row)
			cout << ch;
		cout << '\n';
	}

	cout << answ << '\n';

	return 0;
}