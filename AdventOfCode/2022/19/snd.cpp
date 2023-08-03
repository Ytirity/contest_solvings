#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <utility>
#include <climits>

using namespace std;

struct Blueprint{
	Blueprint (int oe, int cl, pair<int, int> ob, pair<int, int> ge)
	{
		basics[0] = oe;
		basics[1] = cl;
		basics[2] = ob.first;
		basics[3] = ge.first;

		extras[0] = ob.second;
		extras[1] = ge.second;
	}

	int basics[4];
	int extras[2];
};

int mx;
int bst[4];

struct State{
	State(Blueprint* bp)
	: m_bp(bp)
	, bots({1, 0, 0 ,0})
	, limit({0, 0, 0, INT_MAX})
	, recs({0, 0, 0, 0})
	, stage(0) // 0 - oreOnly; 1 - withClay; 2 - withObs
	{
		for (int i = 0; i < 4; i++)
			limit[0] = max(limit[0], m_bp->basics[i]);
		limit[1] = m_bp->extras[0];
		limit[2] = m_bp->extras[1];
	}

	State(State& other) = default;

public:

	bool canCreateBot(int bot_id){
		if (m_bp->basics[bot_id] > recs[0])
			return false;
		if (bot_id >= 2 && m_bp->extras[bot_id - 2] > recs[bot_id - 1])
			return false;
		return true;
	}

	bool createBot(int bot_id){
		if (!canCreateBot(bot_id))
			return false;

		bots[bot_id]++;
		recs[0] -= m_bp->basics[bot_id];
		if (bot_id >= 2)
			recs[bot_id - 1] -= m_bp->extras[bot_id - 2];

		stage = max(stage, bot_id);

		return true;
	}

	void tick(){
		for (int i = 0; i < 4; i++)
			recs[i] += bots[i];
	}

	int getGEO(){
		if (recs[3] > mx){
			cout << mx << " <- ";
			for (int i = 0; i < 4; i++){
				cout << bst[i] << ' ';
				mx = recs[3];
				bst[i] = bots[i];
			}
			cout << '\n';
		}
		return recs[3];
	}

	int getStage(){ // !!
		return min(stage, 2);
	}

	bool enoughBots(int bot_type){
		return bots[bot_type] >= limit[bot_type];
	}

private:

	int bots[4];
	int limit[4];

	int recs[4];

	int stage;

	Blueprint* m_bp;
};

int find(State st, int timer, int plannedBot){ // 0 - ore; 1 - clay; 2 - obs; 3 - geo
	
	while (timer != 0 && !st.canCreateBot(plannedBot)){ // toOptimize: no ticking -> can calc secs to gen
		timer--;
		st.tick();
	}
	
	if (timer == 0)
		return st.getGEO();

	st.tick();
	st.createBot(plannedBot);
	timer--;

	if (timer == 0)
		return st.getGEO();

	int answ = 0;
	for (int i = 0; i <= st.getStage() + 1; i++)
		if (!st.enoughBots(i))
			answ = max(answ, find(st, timer, i));

	return answ;
}

int main(){
	mx = 0;
	std::ifstream in("input.txt");
	//std::ifstream in("test.txt");

	std::regex data_regex("Blueprint [0-9]+: Each ore robot costs ([0-9]+) ore. Each clay robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.");

	vector<Blueprint> blueprints;

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex)){

			blueprints.emplace_back(Blueprint(stoi(matches[1].str()), stoi(matches[2].str()), {stoi(matches[3].str()), stoi(matches[4].str())}, {stoi(matches[5].str()), stoi(matches[6].str())}));
		}
	}

	const int BP_AMOUNT = 3;

	int answ = 1;
	for (int i = 0; i < min(3, (int)blueprints.size()); i++){

		answ *= max(find(State(&blueprints[i]), 32, 0), find(State(&blueprints[i]), 32, 1));

		cout << "max " << mx << " <- ";
		for (int i = 0; i < 4; i++)
				cout << bst[i] << ' ';
		cout << '\n';

		mx = 0;
	}
	
	cout << answ << '\n';
	return 0;
}