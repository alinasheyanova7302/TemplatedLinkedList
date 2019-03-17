#include<ctime>
#include "Map.h"

using namespace std;

void test_int() {
	Map<int, int> map;

	map.insert(7, 3);
	map.insert(2, 8);
	map.insert(1, 9);
	map.insert(3, 7);
	map.insert(4, 6);
	map.insert(9, 1);
	map.insert(8, 2);

	if (map.contains(9))
		cout << " test 1" << endl;
	map.remove(9);
	if (!map.contains(9))
		cout << " test 2" << endl;
	if (map.find(8) == 2)
		cout << " test 3" << endl;
	cout << endl;
	auto list_keys = map.getKeys().create_list_iterator();
	auto list_values = map.getValues().create_list_iterator();
	while (list_keys->has_next() && list_values->has_next())
	{
		cout << list_keys->next() << " " << list_values->next() << endl;
	}

	map.insert(4, 555);
	list_keys = map.getKeys().create_list_iterator();
	list_values = map.getValues().create_list_iterator();
	while (list_keys->has_next() && list_values->has_next())
	{
		cout << list_keys->next() << " " << list_values->next() << endl;
	}
}

int main() {
	test_int();
	system("pause");
	return 0;
}