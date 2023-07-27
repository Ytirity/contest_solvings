#include <string>
#include <iostream>
#include <vector>

#include <functional>
#include <algorithm>

using namespace std;

int main(){

	const int MONKEY_AMOUNT = 8;
	
	vector<function<int(int)>> operations = {
		[](int v){ return v * 17; },
		[](int v){ return v + 2; },
		[](int v){ return v + 1; },
		[](int v){ return v + 7; },
		[](int v){ return v * v; },
		[](int v){ return v + 8; },
		[](int v){ return v * 2; },
		[](int v){ return v + 6; }
	};

	vector<function<bool(int)>> testings = {
		[](int v){ return v % 3  == 0; },
		[](int v){ return v % 13 == 0; },
		[](int v){ return v % 2  == 0; },
		[](int v){ return v % 11 == 0; },
		[](int v){ return v % 19 == 0; },
		[](int v){ return v % 17 == 0; },
		[](int v){ return v % 5  == 0; },
		[](int v){ return v % 7  == 0; }
	};

	vector<pair<int,int>> test_inds = {
		{3, 6},
		{3, 0},
		{0, 1},
		{6, 7},
		{2, 5},
		{2, 1},
		{4, 7},
		{4, 5}
	};

	vector<vector<int>> startings = {
		{59, 65, 86, 56, 74, 57, 56},
		{63, 83, 50, 63, 56},
		{93, 79, 74, 55},
		{86, 61, 67, 88, 94, 69, 56, 91},
		{76, 50, 51},
		{77, 76},
		{74},
		{86, 85, 52, 86, 91, 95}
	};

	vector<int> touches(MONKEY_AMOUNT, 0);

	for (int i = 0; i < 20; i++)
		for (int m = 0; m < MONKEY_AMOUNT; m++){
			
			for (int val : startings[m]){
				touches[m]++;

				val = operations[m](val);
				val /= 3;
				if (testings[m](val))
					startings[test_inds[m].first].push_back(val);
				else
					startings[test_inds[m].second].push_back(val);
			}

			startings[m] = vector<int>(0);
		}
	
	sort(touches.begin(), touches.end(), greater<int>());
	cout << touches[0] * touches[1] << '\n';

	return 0;
}