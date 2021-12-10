#include<iostream>
#include<string>
#include<cmath>
#include<fstream>
#include<map>
using namespace std;
//idnex /valid/tag

map<string, map<string, string>> cache_data;
map<string, map<string, string>> cache_inst;
int numberOfAccess_data = 0;
int numberOfAccess_inst = 0;
double missRatio_data = 0;
double hitRatio_data = 0;
double missRatio_inst = 0;
double hitRatio_inst = 0;
double AMAT_data = 0;
double AMAT_inst = 0;

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
	cout << "Total Number of Accesses : " << numberOfAccess_data + numberOfAccess_inst << endl;
	cout << endl;
	cout << "Data Cache" << endl;
	cout << endl;
	cout << "Number of Access for Data Cache : " << numberOfAccess_data << endl;
	cout << "Hit Ratio : " << hitRatio_data << endl;
	cout << "Miss Ratio : " << missRatio_data << endl;
	cout << "Average Memory Access Time : " << AMAT_data << endl;
	cout << "Index		Valid		  Tag" << endl;

	for (auto itr = cache_data.begin(); itr != cache_data.end(); itr++) {
		for (auto ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
			cout << itr->first << "		  " << ptr->first << "		" << ptr->second << endl;
		}
	}


	cout << endl;
	cout << "Data Instruction" << endl;
	cout << endl;
	cout << "Number of Access for Instruction Cache : " << numberOfAccess_inst << endl;
	cout << "Hit Ratio : " << hitRatio_inst << endl;
	cout << "Miss Ratio : " << missRatio_inst << endl;
	cout << "Average Memory Access Time : " << AMAT_inst << endl;
	cout << "Index		Valid		  Tag" << endl;

	for (auto itr = cache_inst.begin(); itr != cache_inst.end(); itr++) {
		for (auto ptr = itr->second.begin(); ptr != itr->second.end(); ptr++) {
			cout << itr->first << "		  " << ptr->first << "		" << ptr->second << endl;
		}
	}

	cout << endl;
	system("pause");
}
int main()
{
	int S_data, L_data, cycleNumbers_data;
	int S_inst, L_inst, cycleNumbers_inst;

	cout << "Enter Cache Size for Data Cache : " << endl;
	cin >> S_data; //1024
	cout << "Enter Cache Line Size for Data Cache :" << endl;
	cin >> L_data; //128
	cout << "Enter Number of Cycles for Data Cache :" << endl;
	cin >> cycleNumbers_data;

	cout << "Enter Cache Size for Instruction Cache : " << endl;
	cin >> S_inst; //1024
	cout << "Enter Cache Line Size for Instruction Cache :" << endl;
	cin >> L_inst; //128
	cout << "Enter Number of Cycles for Instruction Cache :" << endl;
	cin >> cycleNumbers_inst;




	int dataSize = log2(L_data); 
	int C_data = S_data / L_data;
	int indexSize_data = log2(C_data);
	int tagSize_data = 32 - (dataSize + indexSize_data);



	int instSize = log2(L_inst);
	int C_inst = S_inst / L_inst;
	int indexSize_inst = log2(C_inst);
	int tagSize_inst = 32 - (instSize + indexSize_inst);


	for (int i = 0; i < C_data; i++)
	{
		cache_data[tobinary(i,indexSize_data)]["0"] = " ";
	}

	for (int i = 0; i < C_inst; i++)
	{
		cache_inst[tobinary(i, indexSize_inst)]["0"] = " ";
	}



	string inputfile;

	cout << "Enter Sequence of Memory Addresses file name : " << endl;
	cin >> inputfile;

	ifstream infile;
	infile.open(inputfile);

	string address;
	int data = 32 - dataSize;
	int inst = 32 - instSize;
	int miss_data = 0;
	int hit_data = 0;
	int miss_inst = 0;
	int hit_inst = 0;
	while (getline(infile, address))
	{
		if (address[0] == 'D')
		{
			numberOfAccess_data++;
			address.replace(0, 2, "");
			string value = address.substr(0, data);
			string tag = value.substr(0, tagSize_data);
			string index = value.substr(tagSize_data);

			auto itr = cache_data.find(index);
			auto ptr = itr->second.begin();
			if (ptr->first == "0")
			{
				miss_data++;
				cache_data[index].erase("0");
				cache_data[index]["1"] = tag;
			}
			else if (ptr->first == "1")
			{
				if (ptr->second == tag)
				{
					hit_data++;
				}
				else
				{
					miss_data++;
					cache_data[index]["1"] = tag;

				}


			}

			missRatio_data = double(miss_data) / double(numberOfAccess_data);
			hitRatio_data = double(hit_data) / double(numberOfAccess_data);
			AMAT_data = double(cycleNumbers_data) + missRatio_data * 100.00;
			PrintMap();
			

		}
		else if(address[0]=='I')
		{ 
			numberOfAccess_inst++;
			address.replace(0, 2, "");
			string value = address.substr(0, inst);
			string tag = value.substr(0, tagSize_inst);
			string index = value.substr(tagSize_inst);

			auto itr = cache_inst.find(index);
			auto ptr = itr->second.begin();
			if (ptr->first == "0")
			{
				miss_inst++;
				cache_inst[index].erase("0");
				cache_inst[index]["1"] = tag;
			}
			else if (ptr->first == "1")
			{
				if (ptr->second == tag)
				{
					hit_inst++;
				}
				else
				{
					miss_inst++;
					cache_inst[index]["1"] = tag;

				}


			}

			missRatio_inst = double(miss_inst) / double(numberOfAccess_inst);
			hitRatio_inst = double(hit_inst) / double(numberOfAccess_inst);
			AMAT_inst = double(cycleNumbers_inst) + missRatio_inst * 100.00;
			PrintMap();
			
		}
		

	}


	return 0;
}