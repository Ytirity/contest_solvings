#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;



int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	vector<string> grid;
	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);

		string row;
		iss >> row;

		grid.push_back(row);
	}

	vector<vector<bool>> visible = vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size(), false));

	
	for (int i = 0; i < grid.size(); i++){
		int l_cover = -1, r_cover = -1;
		for (int j = 0; j < grid[0].size(); j++){
			if (grid[i][j] > l_cover){
				visible[i][j] = true;
				l_cover = grid[i][j];
			}
			if (grid[i][grid[0].size() - j - 1] > r_cover){
				visible[i][grid[0].size() - j - 1] = true;
				r_cover = grid[i][grid[0].size() - j - 1];
			}
		}
	}

	for (int j = 0; j < grid[0].size(); j++){
		int t_cover = -1, b_cover = -1;
		for (int i = 0; i < grid.size(); i++){
			if (grid[i][j] > t_cover){
				visible[i][j] = true;
				t_cover = grid[i][j];
			}
			if (grid[grid.size() - i - 1][j] > b_cover){
				visible[grid.size() - i - 1][j] = true;
				b_cover = grid[grid.size() - i - 1][j];
			}
		}
	}

	int answ = 0;
	for (vector<bool>& row : visible)
		for (bool bl : row)
			if (bl)
				answ++;

	cout << answ;

	return 0;
}