#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>


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

	int answ = 0;
	int counter = 1;

	for (std::string line; std::getline(in, line); ){

		string left, right;

		std::istringstream iss1(line);
		iss1 >> left;

		std::getline(in, line);
		std::istringstream iss2(line);
		iss2 >> right;

		std::getline(in, line);

		int tmpl = 0, tmpr = 0;
		Arr l(left, tmpl), r(right, tmpr);

		if (l < r){
			answ += counter;
			cout << counter << '\n';
		}
		counter++;
	}

	cout << answ << '\n';

	return 0;
}