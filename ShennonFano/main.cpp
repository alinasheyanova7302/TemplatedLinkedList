#include <iostream>
#include "ShennonFano.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::wstring test_string = L"гигабайт";
	std::wstring test_string2 = L"~гигатайд";
	ShennonFano shennon;
	auto table = shennon.get_table(test_string);
	auto n = table.getKeys();
	auto encode_str = shennon.encode(test_string2, table);
	auto decode_str = shennon.decode(encode_str, table);
	std::cout << "Hello World!\n";
	system("PAUSE");
	return 0;
}