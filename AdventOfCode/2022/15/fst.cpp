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

	const int ROW = 2000000;
	
	vector<pair<int, int>> intervs;

	for (pair<Point, Point> p : data){
		int dist = abs(p.first.m_x - p.second.m_x) + abs(p.first.m_y - p.second.m_y);
		
		

		if (int diff = abs(p.first.m_y - ROW); diff <= dist){
			intervs.push_back({p.first.m_x - (dist - diff), p.first.m_x + (dist - diff)});
			//cout << p.first.m_x << "I" << p.first.m_y << ' ' << dist - diff << ' ' << p.first.m_x - (dist - diff) << '|' << p.first.m_x + (dist - diff)<< '\n';
		}
	}



	auto cmp = [](pair<int, int> p1, pair<int, int> p2){ return p1.first < p2.first; };

	sort(intervs.begin(), intervs.end(), cmp);

	for (pair<int, int> p : intervs)
		cout << p.first << '|' << p.second << ' ';
	cout << '\n';

	int answ = 0;
	int covered = INT_MIN;
	for (pair<int, int> p : intervs){
		if (p.first > covered)
			answ += (p.second - p.first);
		else 
			answ += max(p.second - covered, 0);
		covered = max(covered, p.second);
	}

	cout << answ << '\n';

	return 0;
}

// 5068327 too high