#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Node{
	Node(int shift)
	: m_shift(shift)
	, m_next(nullptr)
	, m_prev(nullptr)
	{}

	void connectNext(Node* next){
		m_next = next;
		next->m_prev = this;
	}

	void triggerShift(){
		int shift = m_shift;

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
	int m_shift;

	Node *m_next;
	Node *m_prev;
};

int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	vector<Node> shifts;
	int zeroNodeId;

	int shift;
	while (in >> shift){
		
		if (shift == 0)
			zeroNodeId = shifts.size();

		shifts.emplace_back(Node(shift));
	}
	

	for (int i = 0; i < shifts.size(); i++)
		shifts[i].connectNext(&shifts[(i + 1) % shifts.size()]);

	for (Node& node : shifts)
		node.triggerShift();

	int answ = 0;
	Node* curr = &shifts[zeroNodeId];
	for (int i = 0; i <= 3000; i++){
		if (i == 1000 || i == 2000 || i == 3000)
			answ += curr->m_shift;

		curr = curr->m_next;
	}

	cout << answ << '\n';

	return 0;
}