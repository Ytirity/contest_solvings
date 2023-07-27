#include <string>
#include <iostream>
#include <vector>

#include <functional>
#include <algorithm>

using namespace std;

int main(){
	/*

	const int MONKEY_AMOUNT = 4;
	
	vector<function<long long int(long long int)>> operations = {
		[](long long int v){ return v * 19; },
		[](long long int v){ return v + 6; },
		[](long long int v){ return v * v; },
		[](long long int v){ return v + 3; }
	};

	vector<function<bool(long long int)>> testings = {
		[](long long int v){ return v % 23 == 0; },
		[](long long int v){ return v % 19 == 0; },
		[](long long int v){ return v % 13 == 0; },
		[](long long int v){ return v % 17 == 0; }
	};
	const long long int DIV = 96577;

	vector<pair<int,int>> test_inds = {
		{2, 3},
		{2, 0},
		{1, 3},
		{0, 1}
	};

	vector<vector<long long int>> startings = {
		{79, 98},
		{54, 65, 75, 74},
		{79, 60, 97},
		{74}
	};
	*/

	
	const int MONKEY_AMOUNT = 8;
	
	vector<function<long long int(long long int)>> operations = {
		[](long long int v){ return v * 17; },
		[](long long int v){ return v + 2; },
		[](long long int v){ return v + 1; },
		[](long long int v){ return v + 7; },
		[](long long int v){ return v * v; },
		[](long long int v){ return v + 8; },
		[](long long int v){ return v * 2; },
		[](long long int v){ return v + 6; }
	};

	vector<function<bool(long long int)>> testings = {
		[](long long int v){ return v % 3  == 0; },
		[](long long int v){ return v % 13 == 0; },
		[](long long int v){ return v % 2  == 0; },
		[](long long int v){ return v % 11 == 0; },
		[](long long int v){ return v % 19 == 0; },
		[](long long int v){ return v % 17 == 0; },
		[](long long int v){ return v % 5  == 0; },
		[](long long int v){ return v % 7  == 0; }
	};
	const long long int DIV = 9699690;

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

	vector<vector<long long int>> startings = {
		{59, 65, 86, 56, 74, 57, 56},
		{63, 83, 50, 63, 56},
		{93, 79, 74, 55},
		{86, 61, 67, 88, 94, 69, 56, 91},
		{76, 50, 51},
		{77, 76},
		{74},
		{86, 85, 52, 86, 91, 95}
	};
	
	vector<long long int> touches(MONKEY_AMOUNT, 0);
	
	//9699690 = 3 * 13 * 2 * 11 * 19 * 17 * 5 * 7

	for (int i = 0; i < 10000; i++){
		for (int m = 0; m < MONKEY_AMOUNT; m++){
			
			for (long long int val : startings[m]){
				touches[m]++;

				val = operations[m](val);
				val = val % DIV;
				if (testings[m](val))
					startings[test_inds[m].first].push_back(val);
				else
					startings[test_inds[m].second].push_back(val);
			}

			startings[m] = vector<long long int>(0);
		}

		i++;
		if (i == 1 || i == 20 || i == 1000 || i == 2000 || i == 3000){
			for (long long int& touch : touches)
				cout << touch << ' ';
			cout << '\n';
		}
		i--;
	}
	
	sort(touches.begin(), touches.end(), greater<long long int>());
	cout << touches[0] * touches[1] << '\n';

	return 0;
}

//1964676252 - low
//14849578140 - high
//13937702909 - just right