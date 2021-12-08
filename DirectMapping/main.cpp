#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<map>
using namespace std;
//idnex /valid/tag

map<string, map<string, string>> cache;

string tobinary(int n , int indexSize) {
	string result = "";
	while (n > 0) {
		result = string(1, (char)(n % 2 + 48)) + result;
		n = n / 2;
	}
	while (result.length() < indexSize)
		result = "0" + result;

	return result;
}
void PrintMap()
{
	cout << "Index		Valid		  Tag" << endl;
	for (auto itr = cache.begin(); itr != cache.end(); itr++) {
		for (auto ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
			cout << itr->first << "		  " << ptr->first << "		" << ptr->second << endl;
		}
	}

	system("pause");
}
int main()
{
	int S, L, cycleNumbers;

	cout << "Enter Cache Size : " << endl;
	cin >> S; //1024
	cout << "Enter Cache Line Size :" << endl;
	cin >> L; //128
	cout << "Enter Number of Cycles :" << endl;
	cin >> cycleNumbers;

	int dataSize = log2(L); 
	int C = S / L;
	int indexSize = log2(C); 
	int tagSize = 32 - (dataSize + indexSize);

	string j = "0";
	for (int i = 0; i < C; i++)
	{
		cache[tobinary(i,indexSize)][j] = " ";
	}

	string inputfile;

	cout << "Enter Sequence of Memory Addresses file name : " << endl;
	cin >> inputfile;

	ifstream infile;
	infile.open(inputfile);

	string address;
	int data = 32 - dataSize;
	int numberOfAccess = 1;
	int hit = 0;
	int miss = 0;
	while (getline(infile, address))
	{
		cout << "Number of Access : " << numberOfAccess << endl;
		string value = address.substr(0, data);
		string tag = value.substr(0, tagSize);
		string index = value.substr(tagSize);

		auto itr = cache.find(index);
		auto ptr = itr->second.begin();
		if (ptr->first == "0")
		{
			miss++;
			cache[index].erase("0");
			cache[index]["1"] = tag;
		}
		else if (ptr->first == "1")
		{
			if (ptr->second == tag)
			{
				hit++;
			}
			else
			{
				miss++;
				cache[index]["1"] = tag;

			}


		}

		double missRatio = double(miss) / double(numberOfAccess);
		double hitRatio = double(hit) / double(numberOfAccess);
		cout << "Hit Ratio : " << hitRatio << endl;
		cout << "Miss Ratio : " << missRatio << endl;
		double AMAT = double(cycleNumbers) + missRatio * 100.00;
		cout << "Average Memory Access Time : " << AMAT << endl;
		PrintMap();
		numberOfAccess++;
		cout << endl;

	}


	return 0;
}