#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
using namespace std;
map<string, vector<string>> registers;
string tobinary(string decimal);


// create to_decimal function 
//check if convert is needed (print and / or )
//system ("pause")

//input user (start address) (nada )

//input user (program data) (nada)
//create memory map  (nada)

//read file store in map (nada)
//to_hexa 
//test case 

//map insta <int(address , start +4) , string(ins)>
//map memory <int (address (2000) , int (value , -7)>

void printMap()
{
	for (int i = 0; i < 32; i++)
	{
		auto it = registers.find("x" + to_string(i));

		cout << it->first << " = " << it->second[0] << it->second[1] << it->second[2] << endl;
	}
}

void Add(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi( it->second[0]);
	int temp3 = temp2 + temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	//it->second[2] = toHexa(temp3);
	printMap();
}
void sub(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp2 - temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b"+ tobinary(to_string(temp3));
	//it->second[2] = toHexa(temp3);
	printMap();
}
void anding(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp2 & temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b"+ tobinary(to_string(temp3));
	//it->second[2] = toHexa(temp3);
	printMap();
}
/*void oring(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = it->second[0];
	it = registers.find(rs2);
	int temp2 = it->second[0];
	int temp3 = temp2 | temp1;
	it = registers.find(rd);
	it->second[0] = temp3;
	it->second[1] = tobinary(temp3);
	//it->second[2] = toHexa(temp3);
	printMap();
}
void xoring(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = it->second[0];
	it = registers.find(rs2);
	int temp2 = it->second[0];
	int temp3 = temp2 ^ temp1;
	it = registers.find(rd);
	it->second[0] = temp3;
	it->second[1] = tobinary(temp3);
	//it->second[2] = toHexa(temp3);
	printMap();
}*/
string tobinary(string num) //convert num to int 
{
	int r, i = 0, s = 0, bin = 0;
	int arr[32] = { 0 };
	while (num != 0)
	{
		r = num % 2;
		arr[i++] = r;
		num /= 2;
	}
	for (int j = i - 1; j >= 0; j--)
	{
		arr[s] = arr[j];
		s++;
	}
	for (int i = 0; i > 32; i++) {
		int val = 1;
		for (int j = 0; j < i; j++) {
			val *= 10;
		}
		bin += arr[i] * val;
	}
	return bin;

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
		registers.insert(pair < string, vector<string>>(name, { "0","0b"+tobinary("0"),"0"}));
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