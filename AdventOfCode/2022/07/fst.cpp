#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

using namespace std;

struct Node{
	Node(Node* p)
		: prev(p)
	{}

	int size;
	Node* prev;
	unordered_map<string, Node*> nexts;
	unordered_map<string, int> files;
};

pair<int, int> sumSizes(Node* node){
	int totalSize = 0;
	int minSize = 0;

	for (const auto& [dirname, subdir] : node->nexts){
		cout << dirname << '\n';
		pair<int, int> addon = sumSizes(subdir);
		totalSize += addon.first;
		minSize += addon.second;
	}

	for (const auto& [filename, size] : node->files){
		cout << filename << ' ' << size << '\n';
		totalSize += size;
	}
	

	if (totalSize <= 100000)
		minSize += totalSize;

	return {totalSize, minSize};
}

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");

	Node* root = new Node(nullptr);
	root->prev = root;

	Node* curr = root;

	for (std::string line; std::getline(in, line); ){

		if (line == "$ cd /"){
			curr = root;
			continue;
		}

		if (line == "$ cd .."){
			curr = curr->prev;
			continue;
		}

		if (line == "$ ls")
			continue;


		std::istringstream iss(line);

		if (line[0] == '$'){
			string tmp, dirname;
			iss >> tmp >> tmp >> dirname;

			if (curr->nexts.count(dirname) == 0)
				curr->nexts[dirname] = new Node(curr);
			curr = curr->nexts[dirname];

			continue;
		}

		if (line[0] == 'd'){
			string tmp, dirname;
			iss >> tmp >> dirname;

			if (curr->nexts.count(dirname) == 0)
				curr->nexts[dirname] = new Node(curr);

			continue;
		}
		
		int size;
		string name;
		iss >> size >> name;

		curr->files[name] = size;
	}

	cout << sumSizes(root).second;

	return 0;
}