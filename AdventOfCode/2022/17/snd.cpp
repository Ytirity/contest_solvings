#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <numeric>
#include <unordered_set>

using namespace std;
vector<vector<string>> rocks = 
{
	{
		"####"
	},
	{
		".#.",
		"###",
		".#."
	},
	{
		"###", //reversed
		"..#",
		"..#"
	},
	{
		"#",
		"#",
		"#",
		"#"
	},
	{
		"##",
		"##"
	}

};

int main(){

	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	string moves;
	in >> moves;
	int currMove = 0;

	long long TOTAL = 1'000'000'000'000;
	bool heightPart = 0;
	long long answ = 0;
	
	long long int beforeHeight;
	long long int betweenHeight;
	long long int afterHeight;

	unordered_set<int> currMove_vals; // to catch repeating part (start of inBetween)
	int currMove_repeating; // to catch end of repeating (end of inBetween)

	vector<vector<bool>> layout(1, vector<bool>(7, true));
	int height = 0;


	for (long long i = 0 ; i < TOTAL; i++){// removing repeating part (0 - before, 1 - before repeting, 2 - after repeating, )
		if (i % 5 == 0){
			// cout << heightPart << ' ' << currMove_repeating << ' ' << currMove % moves.size() << '\n';
			if (heightPart == 0){
				if (currMove_vals.count(currMove % moves.size()) != 0){
					heightPart = 1;
					currMove_repeating = currMove % moves.size();

					beforeHeight = height;
					answ += beforeHeight;

					TOTAL -= i;
					i = 0;
				} else {
					currMove_vals.insert(currMove % moves.size());
				}
			} else if (heightPart == 1){
				if (currMove % moves.size() == currMove_repeating){
					heightPart = 2;

					betweenHeight = (long long) height - beforeHeight;
					answ += betweenHeight * (TOTAL / i);

					TOTAL = TOTAL % i;
					i = 0;
				}
			}
		}
		

		int neuHeight = height + 5;
		int neuWidth = 2;

		while (layout.size() < neuHeight + rocks[i % 5].size())
			layout.push_back(vector<bool>(7, false));
		

		while (true){//try fall then push
			for (int h = 0; h < rocks[i % 5].size(); h++)
				for (int w = 0; w < rocks[i % 5][h].size(); w++){
					int checkH = h + neuHeight - 1;
					int checkW = w + neuWidth;

					if (checkH < layout.size() && layout[checkH][checkW] && (rocks[i % 5][h][w] == '#'))
						goto setup;			
				}

			neuHeight--;

			for (int h = 0; h < rocks[i % 5].size(); h++)
				for (int w = 0; w < rocks[i % 5][h].size(); w++){
					int checkH = h + neuHeight;
					int checkW = w + neuWidth + (moves[(currMove) %  moves.size()] == '>' ? 1 : -1 );

					if (checkW < 0 || checkW >= layout[0].size() || (layout[checkH][checkW] && rocks[i % 5][h][w] == '#'))
						goto skip;			
				}

			neuWidth += (moves[(currMove) %  moves.size()] == '>' ? 1 : -1 );

			skip:
			currMove++;

			//cout << "h " << neuHeight << ' ' << neuWidth << '\n';
		}

		setup:
		for (int h = 0; h < rocks[i % 5].size(); h++)
			for (int w = 0; w < rocks[i % 5][h].size(); w++)
				if (rocks[i % 5][h][w] == '#'){
					layout[neuHeight + h][neuWidth + w] = true;
					height = max(height, neuHeight + h);
				}
		//cout << "h " << height << '\n';
	}

	afterHeight = (long long) height - betweenHeight - beforeHeight;

	answ += afterHeight;

	cout << "Total: " << answ << '\n'; // 

	return 0;
}


// 1591977077341 too low

// hmmm tests example is 1 bigger; but real input its ok
