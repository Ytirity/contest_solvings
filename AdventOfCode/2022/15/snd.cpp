#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <climits>
#include <algorithm>

using namespace std;

struct Point{
	Point(int x, int y)
	: m_x(x)
	, m_y(y)
	{}

	int m_x;
	int m_y;
};

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	vector<pair<Point, Point>> data;
	std::regex data_regex("Sensor at x=([-]?[0-9]+), y=([-]?[0-9]+): closest beacon is at x=([-]?[0-9]+), y=([-]?[0-9]+)");

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex))
			data.push_back({Point(stoi(matches[1].str()), stoi(matches[2].str())),
							Point(stoi(matches[3].str()), stoi(matches[4].str()))});

	}

	const long long int MN_B = 0, MX_B = 4'000'000; //MX_B = 20;
	for (int row = MN_B; row <= MX_B; row++){

		vector<pair<int, int>> intervs;

		for (pair<Point, Point> p : data){
			int dist = abs(p.first.m_x - p.second.m_x) + abs(p.first.m_y - p.second.m_y);
		
			if (int diff = abs(p.first.m_y - row); diff <= dist)
				intervs.push_back({p.first.m_x - (dist - diff), p.first.m_x + (dist - diff)});
		}

		auto cmp = [](pair<int, int> p1, pair<int, int> p2){ return p1.first < p2.first; };
		sort(intervs.begin(), intervs.end(), cmp);

		int covered = 0;
		for (pair<int, int> p : intervs)
			if (p.first > covered){
				cout << row << ' ' << p.first - 1 << ' ' << (long long int)row + MX_B * (long long int)(p.first - 1) << '\n';
				break;
			} else
				covered = max(covered, p.second);

		if (covered < MX_B)
			cout << row << ' ' << covered + 1 << ' ' << (long long int)row + MX_B * (long long int)(covered + 1) << '\n';
	}

	return 0;
}