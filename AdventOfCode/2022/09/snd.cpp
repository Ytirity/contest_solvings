#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <unordered_set>
#include <utility>
#include <climits>

using namespace std;

long long int toKey(pair<int, int> p){
	return ((long long int)p.first << 31) + (long long int)p.second;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

pair<int, int> changePos(pair<int, int> t, pair<int, int> h){

	if (abs(t.first - h.first) < 2 && abs(t.second - h.second) < 2)
		return t;
	else
		return {t.first + sgn(h.first - t.first), t.second + sgn(h.second - t.second)};
}

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	unordered_set<long long int> visited;

	vector<pair<int, int>> rope(10, {0, 0});
	visited.insert(toKey(rope[9]));

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);

		char move;
		int amount;
		iss >> move >> amount;

		while (amount--){
			switch (move){
			case 'R':
				rope[0].first++;
				break;
			case 'L':
				rope[0].first--;
				break;
			case 'U':
				rope[0].second++;
				break;
			case 'D':
				rope[0].second--;
				break;
			}
			
			for (int i = 1; i <= 9; i++)
				rope[i] = changePos(rope[i], rope[i - 1]);
			visited.insert(toKey(rope[9]));
		}

	}

	cout << visited.size();

	return 0;
}