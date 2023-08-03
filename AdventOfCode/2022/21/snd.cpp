#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <regex>
#include <unordered_map>
#include <variant>
#include <functional>

using namespace std;

typedef long long int lli;

typedef function<lli(lli)> lli_f;

struct Node{
	Node(lli val)
	: m_isVal(true)
	, m_val(val)
	{}

	Node(string node1, string node2, char op)
	: m_isVal(false)
	, m_node1(node1)
	, m_node2(node2)
	, m_op(op)
	{}

	bool m_isVal;
	lli m_val;

	string m_node1;
	string m_node2;
	char m_op;
};

unordered_map<string, Node*> strToNode;

// x + 1 = y -> x = y - 1
// x - 1 = y -> x = y + 1
// 1 - x = y -> x = 1 - y

// x * 1 = y -> x = y / 1
// x / 1 = y -> x = y * 1
// 1 / x = y -> x = 1 / y

lli forwCalc(lli v1, lli v2, char op){
	switch(op){
		case '+':
			return v1 + v2;
		case '-':
			return v1 - v2;
		case '*':
			return v1 * v2;
		case '/':
			return v1 / v2;
	}
	return 1;
}

lli_f backwCalcL(lli_f func, lli rightV, char op){
	switch(op){
		case '+':
			return [func, rightV](lli bef){ return func(bef - rightV); };
		case '-':
			return [func, rightV](lli bef){ return func(bef + rightV); };
		case '*':
			return [func, rightV](lli bef){ return func(bef / rightV); };
		case '/':
			return [func, rightV](lli bef){ return func(bef * rightV); };
	}

	return func;
}

lli_f backwCalcR(lli leftV, lli_f func, char op){
	switch(op){
		case '+':
			return [func, leftV](lli bef){ return func(bef - leftV); };
		case '-':
			return [func, leftV](lli bef){ return func(leftV - bef); };
		case '*':
			return [func, leftV](lli bef){ return func(bef / leftV); };
		case '/':
			return [func, leftV](lli bef){ return func(leftV / bef); };
	}

	return func;
}

variant<lli, lli_f> reduceNode(Node* node, bool& varInside){ // calced val OR formula for x calcing

	if (node->m_isVal){
		varInside = false;
		return node->m_val;
	}

	variant<lli, lli_f> left;
	variant<lli, lli_f> right;

	bool varInsideL, varInsideR;


	if (node->m_node1 == "humn"){
		varInsideL = true;
		left = lli_f([](lli answ ){ return answ; });
	} else 
		left = reduceNode(strToNode[node->m_node1], varInsideL);

	if (node->m_node2 == "humn"){
		varInsideR = true;
		right = lli_f([](lli answ){ return answ; });
	} else 
		right = reduceNode(strToNode[node->m_node2], varInsideR);


	if (!varInsideL && !varInsideR){ // can calc
		varInside = false;
		return forwCalc(get<lli>(left), get<lli>(right), node->m_op);
	}

	varInside = true;

	if (varInsideL)
		return backwCalcL(get<lli_f>(left), get<lli>(right), node->m_op);
	
	if (varInsideR)
		return backwCalcR(get<lli>(left), get<lli_f>(right), node->m_op);

	// both varInsides cannot be
	return 0;
}

int main(){
	std::ifstream in("input.txt");
	// std::ifstream in("test.txt");

	std::regex data_regex("([a-z]{4}): (?:([0-9]+)|([a-z]{4}) ([+\\-*\\/]) ([a-z]{4}))");

	for (std::string line; std::getline(in, line); ){

		std::smatch matches;
		if (std::regex_search(line, matches, data_regex)){
			string nodeName = matches[1].str();

			Node * neuNode;

			if (matches[2].str() != "")
				neuNode = new Node(stoi(matches[2].str()));
			else 
				neuNode = new Node(matches[3].str(), matches[5].str(), matches[4].str()[0]);
				
			strToNode[nodeName] = neuNode;
		}
	}
	
	Node* root = strToNode["root"];

	bool varInsideL, varInsideR;

	// check for humn is also needed here
	variant<lli, lli_f> left = reduceNode(strToNode[root->m_node1], varInsideL); 
	variant<lli, lli_f> right = reduceNode(strToNode[root->m_node2], varInsideR);

	if (varInsideL)
		cout << get<lli_f>(left)(get<lli>(right)) << '\n';
	else //if (valrInsideR)
		cout << get<lli_f>(right)(get<lli>(left)) << '\n';

	for (auto [k, v] : strToNode)
		delete v;

	return 0;
}