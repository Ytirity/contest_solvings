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

	int answ = 1;
	for (int i = 1; i < grid.size() - 1; i++)
		for (int j = 1; j < grid[0].size() - 1; j++){
			int mult = 1;

			int l = i - 1;
			for (; l > 0; l--)
				if (grid[l][j] >= grid[i][j])
					break;
			mult *= (i - l);
			cout << (i - l) << ' ';

			int r = i + 1;
			for (; r < grid.size() - 1; r++)
				if (grid[r][j] >= grid[i][j])
					break;
			mult *= (r - i);
			cout << (r - i) << ' ';

			int t = j - 1;
			for (; t > 0; t--)
				if (grid[i][t] >= grid[i][j])
					break;
			mult *= (j - t);
			cout << (j - t) << ' ';

			int b = j + 1;
			for (; b < grid[0].size() - 1; b++)
				if (grid[i][b] >= grid[i][j])
					break;
			mult *= (b - j);
			cout << (b - j) << '\n';

			cout << grid[i][j] << ' ' << mult << '\n';
			answ = max (answ, mult);
		}

	
	cout << answ << '\n';

	return 0;
}