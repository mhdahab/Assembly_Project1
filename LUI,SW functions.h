#define ull unsigned long long int
int decimalToBinary(int N)
{
 
    // To store the binary number
    ull B_Number = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        ull c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;
 
        // Count used to store exponent value
        cnt++;
    }
 
    return B_Number;
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
void Sw(string source, string destination, string offset) { // sw x9,0(x2)
	int source_value,destination_value;
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
		memory_address_values.insert({destination_value,source_value});
	else { i->second = source_value; }
	
	printMap();
}
void LUI(string rd,string constant) {
	string new_value;
	int value = (((1 << 20) - 1) & (stoi(constant) >> (1 - 1)));
	value = decimalToBinary(value);
	new_value=to_string(value)+"000000000000";
	long long temp = binaryToDecimal(new_value);
	auto it = registers.find(rd);
	it->second[0] = to_string(temp);
}

