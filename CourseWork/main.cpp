#include "PushingPreflow.h"

int main(int argc, char* argv[])
{
	ifstream file;
	string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input.txt";
	file.open(path);
	if (!file) throw runtime_error("File doesn't exist");

	vector<ParsedString> parseString;

	parseString = parseFile(file, parseString);

	vector<int> oneVertex = NumberOfVertices(parseString);

	int v = oneVertex.size();
	Graph g(v);

	vector<int> verticesInOrder;
	int start = 0;
	verticesInOrder = convertCharToNumber(oneVertex, verticesInOrder);
	int end = verticesInOrder.size();

	buildNetwork(parseString, oneVertex, verticesInOrder, g);

	cout << "Maximum flow is " << g.getMaxFlow(start, end) << endl;

	file.close();

	system("PAUSE");
	return 0;
}