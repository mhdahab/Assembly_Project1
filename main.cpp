#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
using namespace std;
map<string, vector<int>> registers;


void printMap()
{
	for (int i = 0; i < 32; i++)
	{
	auto it = registers.find("x" + to_string(i));

	cout << it->first << " = " << it->second[0] << it->second[1] << it->second[2] << endl;
	}
}

void Add(string rd,string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = it->second[0];
	it = registers.find(rs2);
	int temp2 = it->second[0];
	int temp3 = temp2 + temp1;
	it = registers.find(rd);
	it->second[0] = temp3;
	//it->second[1] = tobinary(temp3);
	//it->second[2] = toHexa(temp3);
	printMap();
}

int main()
{
	string input_file_name;
	ifstream code;
	string instruction, line;

	//inisalize  map
	for (int i = 0; i < 32; i++)
	{
		string name = "x" + to_string(i);
		registers.insert(pair < string, vector<int>>(name, { 0,0,0 }));
	}

	cout << "Enter Assembly Program File" << endl;
	cin >> input_file_name;
	
	code.open(input_file_name);
	while (!code.eof())
	{
		getline(code, line);
		stringstream s(line);
		getline(s, instruction, ' ');


		if (instruction == "ADD")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);

			Add(rd, rs1, rs2);
		}


		//loop on each line 

		//instruction -> call function 

	}
}