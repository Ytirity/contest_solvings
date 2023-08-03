#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>

using namespace std;

int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	std::regex data_regex("([0-9]+),([0-9]+),([0-9]+)"); // all data is positive

	vector<array<int,3>> data;
	int Xmax = 0, Ymax = 0, Zmax = 0;

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex)){
			data.push_back({stoi(matches[1].str()) + 1, stoi(matches[2].str()) + 1, stoi(matches[3].str()) + 1});

			Xmax = max(Xmax, data.back()[0]);
			Ymax = max(Ymax, data.back()[1]);
			Zmax = max(Zmax, data.back()[2]);
		}
	}

	vector<vector<vector<bool>>> grid(Xmax + 2, vector<vector<bool>>(Ymax + 2, vector<bool>(Zmax + 2, false)));
	for (array<int, 3> pos : data)
		grid[pos[0]][pos[1]][pos[2]] = true;

	const vector<array<int, 3>> moves = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};

	int answ = 0;

	for (int x = 0; x < grid.size(); x++)
		for (int y = 0; y < grid[0].size(); y++)
			for (int z = 0; z < grid[0][0].size(); z++)
				if (!grid[x][y][z])
					for (const array<int, 3>& move : moves)
						if (x + move[0] >= 0 && x + move[0] < grid.size() 
							&& y + move[1] >= 0 && y + move[1] < grid[0].size()
							&& z + move[2] >= 0 && z + move[2] < grid[0][0].size()
							&& grid[x + move[0]][y + move[1]][z + move[2]])
							answ++;
	

	cout << answ;

	return 0;
}