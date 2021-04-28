#include <iostream>
//#include <fmt/core.h>
#include<string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct Pair_m
{
	int value;
	fstream file;

	bool operator<(const Pair_m& rhs) const
	{
		return value > rhs.value;
	}
};
int main()
{
	//creating new small sorted files
	fstream file;
	file.open("random numbers.txt");
	int size_of_1kb = 250;
	int tmp;
	int j = 1;
	string nameOfNewFile;
	while (!file.eof())
	{
		vector<int> vec;
		for (int i = 0; i < size_of_1kb; i++)
		{
			file >> tmp;
			vec.push_back(tmp);
		}
		std::sort(vec.begin(), vec.end());
		ofstream MyFile(to_string(j) + ".txt");
		for (int i = 0; i < vec.size(); i++)
		{
			MyFile << vec[i] << endl;
		}
		++j;
	}
	//merging
	fstream filenew;
	vector<Pair_m> pvec;
	while (j != 0) //opening all files
	{
		int first_number = -1;
		filenew.open(to_string(j) + ".txt");
		filenew >> first_number;
		Pair_m obj;
		obj.value = first_number;
		obj.file = std::move(filenew);
		pvec.push_back(std::move(obj));
		--j;
	}

	make_heap(pvec.begin(), pvec.end());
	ofstream FinalFile("final result.txt");

	while (!pvec.empty()) {
		pop_heap(pvec.begin(), pvec.end());
		FinalFile << pvec.back().value << endl;
		if (pvec.back().file.eof()) {
			pvec.pop_back();
		}
		else {
			pvec.back().file >> pvec.back().value;
			make_heap(pvec.begin(), pvec.end());
		}
	}
}
