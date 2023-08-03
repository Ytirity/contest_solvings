#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

typedef long long int lli;

struct Node{
	Node(int id)
	: m_id(id)
	, m_next(nullptr)
	, m_prev(nullptr)
	{}

	void connectNext(Node* next){
		m_next = next;
		next->m_prev = this;
	}

	void triggerShift(lli shift){

		while (shift != 0){
			Node *lft, *rgt;

			if (shift > 0){
				shift--;
				lft = this;
				rgt = m_next;
			} else {
				shift++;
				lft = m_prev;
				rgt = this;
			}

			lft->m_prev->m_next = rgt;
			rgt->m_next->m_prev = lft;

			lft->m_next = rgt->m_next;
			rgt->m_prev = lft->m_prev;

			lft->m_prev = rgt;
			rgt->m_next = lft;
		}
	}


public:
	int m_id;

	Node *m_next;
	Node *m_prev;
};

int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	vector<Node> relations;
	vector<lli> shifts;
	int zeroNodeId;
	int counter = 0;

	long long int shift;
	while (in >> shift){
		
		if (shift == 0)
			zeroNodeId = counter;

		relations.emplace_back(Node(counter++));
		shifts.emplace_back(shift);
	}
	

	for (int i = 0; i < relations.size(); i++)
		relations[i].connectNext(&relations[(i + 1) % relations.size()]);

	const long long KEY = 811'589'153;
	const long long KEY_R = KEY % (shifts.size() - 1); //-1 because dn't have to count itself
	const int COUNTS = 10;

	cout << shifts.size() << ' ' << KEY << ' ' << KEY_R << '\n';
	for (int c = 0; c < COUNTS; c++){
		for (int i = 0; i < shifts.size(); i++){
			lli shifting = shifts[i];

			while (shifting < 0)
				shifting += (shifts.size() - 1);

			relations[i].triggerShift((shifting * KEY_R) % (shifts.size() - 1));
		}
	}

	cout << '\n';

	lli answ = 0;
	Node* curr = &relations[zeroNodeId];
	for (int i = 0; i <= 3000; i++){

		if (i == 1000 || i == 2000 || i == 3000){
			cout << shifts[curr->m_id] * KEY << '\n';
			answ += shifts[curr->m_id] * KEY;
		}

		curr = curr->m_next;
	}

	cout << answ << '\n';

	return 0;
}