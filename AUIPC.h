#define BITS sizeof(int) * 8 

void AUIPC(string rd, string constant) {
	string new_value;
	int value = (((1 << 20) - 1) & (stoi(constant) >> (1 - 1)));
	value = stoi(tobinary(to_string(value)));
	new_value = to_string(value) + "000000000000";
	long long temp = binaryToDecimal(new_value);
	auto it = registers.find(rd);
	it->second[0] = to_string(temp);
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
		value =stoi(imm)+address;
		AUIPC(rd, to_string(value));

		}