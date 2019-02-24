#include<iostream>
#include "List.h"
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	List<int> List1;

	List<string> List2;

	List<double> List3;

	List1.set_size(0);

	List2.set_size(0);

	List1.push_back(10);

	List1.push_back(20);

	List1.push_back(30);

	List1.push_back(40);

	List2.push_back("String 1");

	List2.push_back("String 2");

	List2.push_back("String 3");

	List3.push_back(10.1);

	List3.push_back(20.2);

	List3.push_back(30.3);

	List3.push_back(40.4);


	cout << List1 << endl;

	cout << List2 << endl;

	cout << List3 << endl;

	cout << endl;

	system("pause");
}