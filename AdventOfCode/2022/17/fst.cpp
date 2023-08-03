#include <fstream>
#include <string>
#include <iostream>
#include <vector>

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

	const int TOTAL = 2022;


	vector<vector<bool>> layout(1, vector<bool>(7, true));
	int height = 0;
	for (int i = 0 ; i < TOTAL; i++){
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

	cout << height << '\n'; // 

	for (int i = 0; i < 50; i++){
		for (bool b : layout[i])
			cout << (b ? '#' : '.');
		cout << '\n';
	}


	return 0;
}