#include<ctime>
#include "Map.h"

using namespace std;

int main() {
	Map<int, int> rbTree1;

	rbTree1.insert(1, 1);

	rbTree1.insert(2, 2);

	rbTree1.insert(3, 3);
	rbTree1.insert(4, 4);
	rbTree1.insert(5, 5);

	rbTree1.remove(1);
	rbTree1.remove(3);
	rbTree1.remove(5);
	system("pause");
	return 0;
}
