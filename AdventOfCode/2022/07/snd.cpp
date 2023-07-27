#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <climits>

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

int sumSizes(Node* node){
	int totalSize = 0;

	for (const auto& [dirname, subdir] : node->nexts){
		cout << dirname << '\n';
		totalSize += sumSizes(subdir);
	}

	for (const auto& [filename, size] : node->files){
		cout << filename << ' ' << size << '\n';
		totalSize += size;
	}

	return totalSize;
}

pair<int, int> findMin(Node* node, int required){
	int totalSize = 0;
	int minSize = INT_MAX;

	for (const auto& [dirname, subdir] : node->nexts){
		pair<int, int> addon = findMin(subdir, required);
		totalSize += addon.first;
		minSize = min(minSize, addon.second);
	}

	for (const auto& [filename, size] : node->files){
		totalSize += size;
	}

	if (totalSize >= required)
		minSize = min(minSize, totalSize);

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

	int total = sumSizes(root);
	cout << "total " << total << '\n';

	int required = 30'000'000 - (70'000'000 - total);
	cout << "min " << findMin(root, required).second << '\n';

	return 0;
}