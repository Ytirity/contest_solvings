#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <algorithm>
#include <numeric>


using namespace std;

struct Arr;

union S{
	S(){}
	~S(){}

	vector<Arr*> vec;
	int val;
};

bool isNum(char ch){
	return '0' <= ch && ch <= '9';
}

int getVal(const string& str, int& l){
	int answ = 0;
	while (l < str.size() && isNum(str[l]))
		answ = answ * 10 + (str[l++] - '0');

	return answ;
}

struct Arr{
	Arr(const string& str, int& l){
		if (str[l] == '['){
			isVal = false;
			new (&data.vec) vector<Arr*>;
			l++;
			while (l < str.size() && str[l] != ']'){
				if (str[l] == ',')
					l++;
				data.vec.push_back(new Arr(str, l));
			}

			if (l != str.size())
				l++;
		} else {
			isVal = true;

			data.val = getVal(str, l);
		}
	}

	~Arr(){
		if (!isVal)
			for (Arr* arr : data.vec)
				delete arr;
	}


	bool operator<(const Arr& other) const{

		if (isVal && other.isVal)
			return data.val < other.data.val;
		
		if (!isVal && other.isVal)
			return data.vec.empty() || (*data.vec[0] < other);
		
		if (isVal && !other.isVal)
			return !other.data.vec.empty() && (*this == *other.data.vec[0] ? other.data.vec.size() > 1 : *this < *other.data.vec[0]);

		for (int i = 0; i < min(data.vec.size(), other.data.vec.size()); i++)
			if (!(*data.vec[i] == *other.data.vec[i]))
				return *data.vec[i] < *other.data.vec[i];

		return data.vec.size() < other.data.vec.size();
	}

	bool operator==(const Arr& other) const{
		return !(*this < other || other < *this); //можно быстрее с проверкой размера
	}

private:

	bool isVal;
	S data;
};

int main(){
	// std::ifstream in("input.txt");
	std::ifstream in("test.txt");


	string fst_str = "[[2]]";
	int tmp1 = 0;
	string snd_str = "[[6]]";
	int tmp2 = 0;
	vector<Arr*> packets;
	packets.push_back(new Arr(fst_str, tmp1));
	packets.push_back(new Arr(snd_str, tmp2));

	for (std::string line; std::getline(in, line); ){

		string left, right;

		std::istringstream iss1(line);
		iss1 >> left;

		std::getline(in, line);
		std::istringstream iss2(line);
		iss2 >> right;

		std::getline(in, line);

		int tmpl = 0, tmpr = 0;

		packets.push_back(new Arr(left, tmpl));
		packets.push_back(new Arr(right, tmpr));
	}

	vector<int> inds(packets.size());
	iota(inds.begin(), inds.end(), 0);

	auto cmp = [& packets](int i1, int i2){ return *packets[i1] < *packets[i2]; };
	sort(inds.begin(), inds.end(), cmp);

	int answ = 1;
	for (int i = 0; i < inds.size(); i++)
		if (inds[i] <= 1)
			answ *= (i + 1);

	cout << answ << '\n';

	return 0;
}