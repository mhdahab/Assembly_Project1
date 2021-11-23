#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include <cstdlib>
#include <math.h>
using namespace std;
map<string, vector<string>> registers;
multimap<int, string>insta_addresses;
map<int, int>memory_address_values;

// create to_decimal function 
//fill hexa and binary with zero

//input user (start address) (nada )

//input user (program data) (nada)
//create memory map  (nada)

//read file store in map (nada)
//test case 

//map insta <int(address , start +4) , string(ins)>
//map memory <int (address (2000) , int (value , -7)>


string tobinary(string num)
{
	int n = stoi(num);
	int r;
	vector<string> bin;
	if (stoi(num) < 0)
		num.erase(0, 1);
	r = stoi(num);
	string binary = "0";

	for (int i = 31; i >= 0; i--) {
		int k = r >> i;
		if (k & 1)
			bin.push_back("1");
		else
			bin.push_back("0");
	}
	for (int i = 0; i < bin.size(); i++)
		binary += bin[i];
	if (n < 0)
	{
		int b = binary.length();
		int i;
		for (i = b - 1; i >= 0; i--)
			if (binary[i] == '1')
				break;
		if (i == -1)
			return '1' + binary;
		for (int k = i - 1; k >= 0; k--)
		{
			if (binary[k] == '1')
				binary[k] = '0';
			else
				binary[k] = '1';
		}
	}

	return binary;
}
string tohexa(string value)
{
	int num = stoi(value);
	map<int, char> m;

	char digit = '0';
	char c = 'a';

	for (int i = 0; i <= 15; i++) {
		if (i < 10) {
			m[i] = digit++;
		}
		else {
			m[i] = c++;
		}
	}

	// string to be returned
	string res = "";

	// check if num is 0 and directly return "0"
	if (!num) {
		return "0";
	}
	// if num>0, use normal technique as
	// discussed in other post
	if (num > 0) {
		while (num) {
			res = m[num % 16] + res;
			num /= 16;
		}

		while (res.length() != 8)
			res = "0" + res;
	}
	// if num<0, we need to use the elaborated
	// trick above, lets see this
	else {
		// store num in a u_int, size of u_it is greater,
		// it will be positive since msb is 0
		uint8_t n = num;

		// use the same remainder technique.
		while (n) {
			res = m[n % 16] + res;
			n /= 16;
		}
		while (res.length() != 8)
			res = "f" + res;
	}

	return res;

}
void printMap()
{
	cout << "Register" << "   " << "Decimal" << "		" << "Binary" << "		" << "Hexadecimal" << endl;
	for (int i = 0; i < 32; i++)
	{
		auto it = registers.find("x" + to_string(i));

		cout << it->first << " :		" << it->second[0] << "		" << it->second[1] << "		" << it->second[2] << endl;
	}

	cout << "Memory Address" << "   " << "Value" << endl;
	for (auto it = memory_address_values.begin(); it != memory_address_values.end(); it++)
	{

		cout << it->first << " :		" << it->second << endl;
	}


	system("pause");

}
void Add(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp2 + temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void sub(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp1 - temp2;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
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
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void oring(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp2 | temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void xoring(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3 = temp2 ^ temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void ADDI(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3 = temp2 + temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();

}
void XORI(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3 = temp2 ^ temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();

}
void ORI(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3 = temp2 | temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();

}
void ANDI(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3 = temp2 & temp1;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();

}
void lw(string source, string destination, string offset) {
	int resgister_address_value;
	for (auto i : registers) {
		if (i.first == source)
		{
			resgister_address_value = stoi(i.second[0]);
			break;
		}

	}
	int destination_address_value = stoi(offset) + resgister_address_value;
	int value;
	for (auto i : memory_address_values) {
		if (i.first == destination_address_value)
		{
			value = i.second;
			break;
		}
	}
	auto it = registers.find(destination);
	it->second[0] = to_string(value);
	printMap();
}
void SLT(string rd, string rs1, string rs2)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3;
	if (temp1 < temp2)
		temp3 = 1;
	else
		temp3 = 0;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SLTU(string rd, string rs1, string rs2)
{

	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3;
	if (rs1 == "x0")
	{
		if (temp2 != 0)
			temp3 = 1;
		else
			temp3 = 0;
	}
	else
	{
		if (abs(temp1) < abs(temp2))
			temp3 = 1;
		else
			temp3 = 0;
	}
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SLTI(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3;
	if (temp1 < temp2)
		temp3 = 1;
	else
		temp3 = 0;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SLTIU(string rd, string rs1, string imm)
{
	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3;
	if (imm == "1")
	{
		if (temp1 == 0)
			temp3 = 1;
		else
			temp3 = 0;
	}
	else
	{
		if (abs(temp1) < abs(temp2))
			temp3 = 1;
		else
			temp3 = 0;
	}
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SLL(string rd, string rs1, string rs2)
{

	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3, temp4;
	temp4 = pow(2.0, temp2);
	temp3 = temp1 * temp4;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SLLI(string rd, string rs1, string imm)
{

	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3, temp4;
	temp4 = pow(2.0, temp2);
	temp3 = temp1 * temp4;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SRL(string rd, string rs1, string rs2)
{

	auto it = registers.find(rs1);
	unsigned int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3, temp4;
	temp4 = pow(2.0, temp2);
	temp3 = temp1 / temp4;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SRLI(string rd, string rs1, string imm)
{

	auto it = registers.find(rs1);
	unsigned int temp1 = stoi(it->second[0]);
	int temp2 = stoi(imm);
	int temp3, temp4;
	temp4 = pow(2.0, temp2);
	temp3 = temp1 / temp4;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SRA(string rd, string rs1, string rs2)
{

	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	int temp2 = stoi(it->second[0]);
	int temp3;
	string binarynum;
	temp3 = temp1 >> temp2;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
void SRAI(string rd, string rs1, string imm)
{

	auto it = registers.find(rs1);
	int temp1 = stoi(it->second[0]);
	it = registers.find(imm);
	int temp2 = stoi(it->second[0]);
	int temp3;
	temp3 = temp1 >> temp2;
	it = registers.find(rd);
	it->second[0] = to_string(temp3);
	it->second[1] = "0b" + tobinary(to_string(temp3));
	it->second[2] = "0x" + tohexa(to_string(temp3));
	printMap();
}
int main()
{
	string input_file_name, program_file_name;
	int address;
	ifstream code, address_file;
	string instruction, line;

	//inisalize  map
	for (int i = 0; i < 32; i++)
	{
		string name = "x" + to_string(i);
		registers.insert(pair < string, vector<string>>(name, { "0","0b" + tobinary("0"),"0x" + tohexa("0") }));
	}

	//get user input
	cout << "Enter Assembly Program File name" << endl;
	cin >> input_file_name;
	cout << "Enter the starting address: " << endl;
	cin >> address;
	cout << "Enter Program Data File name" << endl;
	cin >> program_file_name;


	//read and store instructions
	code.open(input_file_name);
	while (getline(code, line))
	{
		insta_addresses.insert({ address ,line });
		address += 4;
	}
	code.close();

	//read and set memory address
	address_file.open(program_file_name);
	while (!address_file.eof()) {
		string address, value;
		getline(address_file, line);
		stringstream s(line);
		getline(s, address, ',');
		getline(s, value, ',');
		memory_address_values.insert({ stoi(address),stoi(value) });
	}
	address_file.close();

	//generate each instruction
	for (auto it = insta_addresses.begin(); it != insta_addresses.end(); it++)
	{
		cout << endl;
		cout << "Address Number : " << it->first << endl;
		string line = it->second;
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
		else if (instruction == "ADDI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			ADDI(rd, rs1, imm);

		}
		else if (instruction == "SUB")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			sub(rd, rs1, rs2);
		}
		else if (instruction == "XOR")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			xoring(rd, rs1, rs2);

		}
		else if (instruction == "XORI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			XORI(rd, rs1, imm);

		}
		else if (instruction == "OR")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			oring(rd, rs1, rs2);
		}
		else if (instruction == "ORI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			ORI(rd, rs1, imm);

		}
		else if (instruction == "AND")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			anding(rd, rs1, rs2);

		}
		else if (instruction == "ANDI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			ANDI(rd, rs1, imm);

		}
		else if (instruction == "SLT")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			SLT(rd, rs1, rs2);

		}
		else if (instruction == "SLTU")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			SLTU(rd, rs1, rs2);

		}
		else if (instruction == "SLTI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			SLTI(rd, rs1, imm);

		}
		else if (instruction == "SLTIU")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			SLTIU(rd, rs1, imm);

		}
		else if (instruction == "SLL")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			SLL(rd, rs1, rs2);
		}
		else if (instruction == "SRL")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			SRL(rd, rs1, rs2);
		}
		else if (instruction == "SRA")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			SRA(rd, rs1, rs2);
		}
		else if (instruction == "SLLI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			SLLI(rd, rs1, imm);
		}
		else if (instruction == "SRLI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			SRLI(rd, rs1, imm);
		}
		else if (instruction == "SRAI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			SRAI(rd, rs1, imm);
		}
		else if (instruction == "LW")
		{
			string source, destination, offset;
			getline(s, destination, ',');
			getline(s, offset, '(');
			getline(s, source, ')');
			lw(source, destination, offset);

		}

		else if (instruction == "FENCE" || instruction == "ECALL" || instruction == "EBREAK")
			return 0;
		else
		{
			cout << "Invalid Input : " << line << endl;
			return 0;
		}


		//loop on each line 

		//instruction -> call function 

	}

	return 0;
}