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

	pair<int, int> head = {0, 0};
	pair<int, int> tail = {0, 0};
	visited.insert(toKey(tail));

	for (std::string line; std::getline(in, line); ){

		std::istringstream iss(line);

		char move;
		int amount;
		iss >> move >> amount;

		while (amount--){
			switch (move){
			case 'R':
				head.first++;
				break;
			case 'L':
				head.first--;
				break;
			case 'U':
				head.second++;
				break;
			case 'D':
				head.second--;
				break;
			}
			tail = changePos(tail, head);
			visited.insert(toKey(tail));
		}

	}

	cout << visited.size();

	return 0;
}