#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <unordered_map>

using namespace std;

typedef long long int lli;

struct Node{
	Node(lli val)
	: m_isVal(true)
	, m_val(val)
	{}

	Node(string node1, string node2, lli (*func)(lli, lli))
	: m_isVal(false)
	, m_node1(node1)
	, m_node2(node2)
	, m_func(func)
	{}

	bool m_isVal;
	lli m_val;

	string m_node1;
	string m_node2;
	lli (*m_func)(lli, lli);
};

unordered_map<string, Node*> strToNode;

lli calc(Node* node){
	if (node->m_isVal)
		return node->m_val;
	else
		return (*node->m_func)(calc(strToNode[node->m_node1]), calc(strToNode[node->m_node2]));
}

int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	std::regex data_regex("([a-z]{4}): (?:([0-9]+)|([a-z]{4}) ([+\\-*\\/]) ([a-z]{4}))");

	auto pls = [](lli a, lli b) { return a + b; };
	auto min = [](lli a, lli b) { return a - b; };
	auto mul = [](lli a, lli b) { return a * b; };
	auto div = [](lli a, lli b) { return a / b; };

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex)){
			string nodeName = matches[1].str();

			Node * neuNode;

			if (matches[2].str() != "")
				neuNode = new Node(stoi(matches[2].str()));
			else {
				switch(matches[4].str()[0]){
					case '+':
						neuNode = new Node(matches[3].str(), matches[5].str(), pls);
						break;
					case '-':
						neuNode = new Node(matches[3].str(), matches[5].str(), min);
						break;
					case '*':
						neuNode = new Node(matches[3].str(), matches[5].str(), mul);
						break;
					case '/':
						neuNode = new Node(matches[3].str(), matches[5].str(), div);
						break;
				}
				
			}

			strToNode[nodeName] = neuNode;

		}
	}
	
	cout << calc(strToNode["root"]) << '\n';

	for (auto [k, v] : strToNode)
		delete v;

	return 0;
}