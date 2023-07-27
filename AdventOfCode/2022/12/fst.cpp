#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <utility>
#include <climits>
#include <queue>


using namespace std;

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	vector<string> map;
	vector<vector<bool>> visited;

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);
		string row;
		iss >> row;

		map.push_back(row);
		visited.push_back(vector<bool>(row.size(), false));
	}

	queue<pair<int, int>> que;

	pair<int, int> endpoint;
	for (int i = 0; i < map.size(); i++)
		for (int j = 0; j < map[0].size(); j++){
			if (map[i][j] == 'S'){
				map[i][j] = 'a';
				que.push({i, j});
			}
			if (map[i][j] == 'E'){
				map[i][j] = 'z';
				endpoint = {i, j};
			}
		}

	const vector<pair<int, int>> moves = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

	int steps = 0;
	while (!que.empty()){
		int level_amount = que.size();

		for (int i = 0; i < level_amount; i++){
			pair<int, int> curr = que.front();
			//cout << curr.first << ' ' << curr.second << '\n';
			que.pop();

			if (curr == endpoint){
				cout << steps << '\n';
				return 0;
			}
			if (visited[curr.first][curr.second])
				continue;

			visited[curr.first][curr.second] = true;

			for (const pair<int, int>& move : moves)
				if (pair<int, int> next = {curr.first + move.first, curr.second + move.second}
					; next.first >= 0 && next.first < map.size() && next.second >= 0 && next.second < map[0].size()
					&& !visited[next.first][next.second] 
					&& map[curr.first][curr.second] + 1 >= map[next.first][next.second])
				que.push(next);

		}
		steps++;
	}

	cout << "hmmm\n";

	return 0;
}