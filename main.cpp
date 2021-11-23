#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<map>
#include<vector>
#include <cstdlib>
using namespace std;
#define BITS sizeof(int) * 8 


map<string, vector<string>> registers;
multimap<int, string>insta_addresses;
map<int, int>memory_address_values;

string tobinary(string num)
{
	int n = stoi(num);
	int r;
	vector<string> bin;
	if (stoi(num) < 0)
		num.erase(0, 1);
	r = stoi(num);
	string binary = "";

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
	string binnum = tobinary(value);
	char hexa[1000];
	int temp;
	long int i = 0, j = 0;
	while (binnum[i])
	{
		binnum[i] = binnum[i] - 48;
		++i;
	}
	--i;
	while (i - 2 >= 0)
	{
		temp = binnum[i - 3] * 8 + binnum[i - 2] * 4 + binnum[i - 1] * 2 + binnum[i];
		if (temp > 9)
			hexa[j++] = temp + 55;
		else
			hexa[j++] = temp + 48;
		i = i - 4;
	}
	if (i == 1)
		hexa[j] = binnum[i - 1] * 2 + binnum[i] + 48;
	else if (i == 0)
		hexa[j] = binnum[i] + 48;
	else
		--j;
	string s = "";
	while (j >= 0)
	{
		s += hexa[j--];
	}
	return s;
}
int binaryToDecimal(string n)
{
	string num = n;
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;

	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}

	return dec_value;
}
void printMap()
{
	cout << "Register" << "   " << "Decimal" << "			" << "Binary" << "                            " << "Hexadecimal" << endl;
	for (int i = 0; i < 32; i++)
	{
		auto it = registers.find("x" + to_string(i));

		cout << it->first << " :		" << it->second[0] <<"		" << it->second[1] << "	" << it->second[2] << endl;
	}

	cout << "Memory Address" << "   " << "Value" << endl;
	for (auto it=memory_address_values.begin() ; it!=memory_address_values.end() ;it++)
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
	int temp2 = stoi( it->second[0]);
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
	it->second[1] = "0b"+ tobinary(to_string(temp3));
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
	it->second[1] = "0b"+ tobinary(to_string(temp3));
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
	cout << "immediate :" << imm<<endl;
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
void ANDI (string rd, string rs1, string imm)
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
	unsigned int temp1 = stoi(it->second[0]);
	it = registers.find(rs2);
	unsigned int temp2 = stoi(it->second[0]);
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
		if (temp1 < temp2)
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
	unsigned int temp1 = stoi(it->second[0]);
	unsigned int temp2 = stoi(imm);
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
		if (temp1 < temp2)
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
void Sw(string source, string destination, string offset) { // sw x9,0(x2)
	int source_value, destination_value;
	for (auto i : registers) {
		if (i.first == source)
		{
			source_value = stoi(i.second[0]);
			break;
		}

	}
	for (auto i : registers) {
		if (i.first == destination)
		{
			destination_value = stoi(i.second[0]);
			break;
		}

	}
	destination_value = destination_value + stoi(offset);
	map<int, int>::iterator i = memory_address_values.find(destination_value);

	if (i == memory_address_values.end())
		memory_address_values.insert({ destination_value,source_value });
	else { i->second = source_value; }

	printMap();
}
void LUI(string rd, string constant) {
	string new_value;
	int value = (((1 << 20) - 1) & (stoi(constant) >> (1 - 1)));
	value = stoi(tobinary(to_string(value)));
	new_value = to_string(value) + "000000000000";
	long long temp = binaryToDecimal(new_value);
	auto it = registers.find(rd);
	it->second[0] = to_string(temp);
}
void SH(string source, string destination, string offset) { // sw x9,0(x2)
	int source_value, destination_value;
	for (auto i : registers) {
		if (i.first == source)
		{
			source_value = stoi(i.second[0]);
			break;
		}

	}
	source_value = source_value & ((1 << 16) - 1);
	for (auto i : registers) {
		if (i.first == destination)
		{
			destination_value = stoi(i.second[0]);
			break;
		}

	}
	offset = to_string(stoi(offset) / 4);
	destination_value = destination_value + stoi(offset) * 4;

	map<int, int>::iterator i = memory_address_values.find(destination_value);

	if (i == memory_address_values.end())
		memory_address_values.insert({ destination_value,source_value });
	else {
		if (i->second == 0) i->second = source_value;
		else {
			int position = stoi(offset) % 4;
			i->second = i->second & ((1 << position * 8) - 1);
			string binary_value = tobinary(to_string(i->second));
			binary_value += i->second;
			i->second = binaryToDecimal(binary_value);
		}

	}

	printMap();
}
void SB(string source, string destination, string offset) { // sw x9,0(x2)
	int source_value, destination_value;
	for (auto i : registers) {
		if (i.first == source)
		{
			source_value = stoi(i.second[0]);
			break;
		}

	}
	source_value = source_value & ((1 << 8) - 1);
	for (auto i : registers) {
		if (i.first == destination)
		{
			destination_value = stoi(i.second[0]);
			break;
		}

	}
	offset = to_string(stoi(offset) / 4);
	destination_value = destination_value + stoi(offset) * 4;

	map<int, int>::iterator i = memory_address_values.find(destination_value);

	if (i == memory_address_values.end())
		memory_address_values.insert({ destination_value,source_value });
	else {
		if (i->second == 0) i->second = source_value;
		else {
			int position = stoi(offset) % 4;
			i->second = i->second & ((1 << position * 8) - 1);
			string binary_value = tobinary(to_string(i->second));
			binary_value += i->second;
			i->second = binaryToDecimal(binary_value);
		}

	}

	printMap();
}
void LH(string source, string destination, string offset) {
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
	value = value & ((1 << 16) - 1);
	int msb = 1 << (BITS - 1);
	if (value & msb) msb = 1;
	else msb = 0;
	string binary_value;
	for (int i = 0; i < 32 - tobinary(to_string(value)).size(); i++)
		binary_value += msb;
	value = binaryToDecimal(binary_value);
	auto it = registers.find(destination);
	it->second[0] = to_string(value);
	printMap();
}
void LB(string source, string destination, string offset) {
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
	value = value & ((1 << 8) - 1);
	int msb = 1 << (BITS - 1);
	if (value & msb) msb = 1;
	else msb = 0;
	string binary_value;
	for (int i = 0; i < 32 - tobinary(to_string(value)).size(); i++)
		binary_value += msb;
	value = binaryToDecimal(binary_value);
	auto it = registers.find(destination);
	it->second[0] = to_string(value);
	printMap();
}
void LBU(string source, string destination, string offset) {
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
	value = value & ((1 << 8) - 1);

	string binary_value;
	for (int i = 0; i < 32 - tobinary(to_string(value)).size(); i++)
		binary_value += "0";
	value = binaryToDecimal(binary_value);
	auto it = registers.find(destination);
	it->second[0] = to_string(value);
	printMap();
}
void LHU(string source, string destination, string offset) {
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
	value = value & ((1 << 16) - 1);

	string binary_value;
	for (int i = 0; i < 32 - tobinary(to_string(value)).size(); i++)
		binary_value += "0";
	value = binaryToDecimal(binary_value);
	auto it = registers.find(destination);
	it->second[0] = to_string(value);
	printMap();
}
void AUIPC (string rd, string constant) {
	string new_value;
	int value = (((1 << 20) - 1) & (stoi(constant) >> (1 - 1)));
	value = stoi(tobinary(to_string(value)));
	new_value = to_string(value) + "000000000000";
	long long temp = binaryToDecimal(new_value);
	auto it = registers.find(rd);
	it->second[0] = to_string(temp);
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
	auto it = insta_addresses.begin();
	
	while (it != insta_addresses.end())
	{
		cout << endl;
		cout << "Address Number : " << it->first << endl;
		string line = it->second;
		stringstream s(line);
		getline(s, instruction, ' ');
		address = it->first + 4;
		


		if (instruction == "ADD")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			Add(rd, rs1, rs2);
		}
		else if (instruction == "ADDI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			ADDI(rd, rs1, imm);

		}
		else if (instruction == "SUB")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			sub(rd, rs1, rs2);
		}
		else if (instruction == "XOR")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			xoring(rd, rs1, rs2);

		}
		else if (instruction == "XORI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			XORI(rd, rs1, imm);

		}
		else if (instruction == "OR")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			oring(rd, rs1, rs2);
		}
		else if (instruction == "ORI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			ORI(rd, rs1, imm);

		}
		else if (instruction == "AND")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			anding(rd, rs1, rs2);

		}
		else if (instruction == "ANDI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			ANDI(rd, rs1, imm);

		}
		else if (instruction == "SLT")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			SLT(rd, rs1, rs2);

		}
		else if (instruction == "SLTU")
		{
			string rd, rs1, rs2;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, rs2);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			SLTU(rd, rs1, rs2);

		}
		else if (instruction == "SLTI")
		{
			string rd, rs1, imm;
			getline(s, rd, ',');
			getline(s, rs1, ',');
			getline(s, imm);
			if (rd == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			SLTI(rd, rs1, imm);

		}
		else if (instruction == "SLTIU")
		{
		string rd, rs1, imm;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SLTIU(rd, rs1, imm);

		}
		else if (instruction == "SLL")
		{
		string rd, rs1, rs2;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, rs2);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SLL(rd, rs1, rs2);
		}
		else if (instruction == "SRL")
		{
		string rd, rs1, rs2;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, rs2);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SRL(rd, rs1, rs2);
		}
		else if (instruction == "SRA")
		{
		string rd, rs1, rs2;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, rs2);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SRA(rd, rs1, rs2);
		}
		else if (instruction == "SLLI")
		{
		string rd, rs1, imm;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SLLI(rd, rs1, imm);
		}
		else if (instruction == "SRLI")
		{
		string rd, rs1, imm;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SRLI(rd, rs1, imm);
		}
		else if (instruction == "SRAI")
		{
		string rd, rs1, imm;
		getline(s, rd, ',');
		getline(s, rs1, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		SRAI(rd, rs1, imm);
		}
		else if (instruction == "BNE")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		int temp2 = stoi(it1->second[0]);
		if (temp1 != temp2)
			address = it->first + stoi(imm);
		printMap();
        }
		else if (instruction == "BEQ")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		int temp2 = stoi(it1->second[0]);
		if (temp1 == temp2)
			address = it->first + stoi(imm);
		printMap();
 }
		else if (instruction == "BLT")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		int temp2 = stoi(it1->second[0]);
		if (temp1 < temp2)
			address = it->first + stoi(imm);

		printMap();

        }
		else if (instruction == "BLTU")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		unsigned int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		unsigned int temp2 = stoi(it1->second[0]);
		if (temp1 < temp2)
			address = it->first + stoi(imm);
		printMap();

 }
		else if (instruction == "BGE")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		int temp2 = stoi(it1->second[0]);
		if (temp1 > temp2)
			address = it->first + stoi(imm);
		printMap();

 }
		else if (instruction == "BGEU")
		{
		string rs1, rs2, imm;
		getline(s, rs1, ',');
		getline(s, rs2, ',');
		getline(s, imm);
		auto it1 = registers.find(rs1);
		unsigned int temp1 = stoi(it1->second[0]);
		it1 = registers.find(rs2);
		unsigned int temp2 = stoi(it1->second[0]);
		if (temp1 > temp2)
			address = it->first + stoi(imm);
		printMap();

 }
		else if (instruction == "JAL")
		{
		string ra, imm;
		getline(s, ra, ',');
		getline(s, imm);

		if (ra == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		auto it1 = registers.find(ra);
		it1->second[0] = to_string(address-4);
		address = it->first + stoi(imm);
		
		printMap();

 }
		else if (instruction == "JALR")
		{
		string zero, ra, offset;
		getline(s, zero, ',');
		getline(s, offset, '(');
		getline(s, ra, ')');

		auto it1 = registers.find(ra);
		address = stoi(it1->second[0]) + stoi(offset);


 }
		else if (instruction == "SW") 
		{
			string source, destination, offset;
			getline(s, source, ',');
			getline(s, offset, '(');
			getline(s, destination, ')');
			Sw(source, destination, offset);

		}
		else if (instruction == "SH")
		{
			string source, destination, offset;
			getline(s, destination, ',');
			getline(s, offset, '(');
			getline(s, source, ')');
			SH(source, destination, offset);

		}
		else if (instruction == "SB")
		{
		string source, destination, offset;
		getline(s, destination, ',');
		getline(s, offset, '(');
		getline(s, source, ')');
		SB(source, destination, offset);

		}
		else if (instruction == "LH")
		{
		string source, destination, offset;
		getline(s, destination, ',');
		getline(s, offset, '(');
		getline(s, source, ')');
		if (destination == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		LH(source, destination, offset);

		}
		else if (instruction == "LB")
		{
		string source, destination, offset;
		getline(s, destination, ',');
		getline(s, offset, '(');
		getline(s, source, ')');
		if (destination == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		LB(source, destination, offset);

		}
		else if (instruction == "LBU")
		{
		string source, destination, offset;
		getline(s, destination, ',');
		getline(s, offset, '(');
		getline(s, source, ')');
		if (destination == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		LBU(source, destination, offset);

		}
		else if (instruction == "LHU")
		{
		string source, destination, offset;
		getline(s, destination, ',');
		getline(s, offset, '(');
		getline(s, source, ')');
		if (destination == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		LHU(source, destination, offset);

		}
		else if (instruction == "LW")
		{
			string source, destination, offset;
			getline(s, destination, ',');
			getline(s, offset, '(');
			getline(s, source, ')');
			if (destination == "x0")
			{
				cout << "Invalid Input !" << endl;
				cout << line << endl;
				cout << "Can't modify register 0 " << endl;
				return 0;
			}
			lw(source, destination, offset);

		}
		else if (instruction == "LUI")
		{
		string rd,imm;
		getline(s, rd, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		LUI(rd,imm);

		}
		else if (instruction == "AUIPC")
		{
		string rd, imm;
		getline(s, rd, ',');
		getline(s, imm);
		if (rd == "x0")
		{
			cout << "Invalid Input !" << endl;
			cout << line << endl;
			cout << "Can't modify register 0 " << endl;
			return 0;
		}
		int value;
		value = stoi(imm) + address;
		AUIPC(rd, to_string(value));

		}
		else if (instruction == "FENCE" || instruction == "ECALL" || instruction == "EBREAK")
			return 0;
		else
		{
			cout << "Invalid Input : " << line << endl;
			return 0;
		}

 
		it = insta_addresses.find(address);
	}

	return 0;
}