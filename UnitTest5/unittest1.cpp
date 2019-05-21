#include "stdafx.h"
#include "CppUnitTest.h"
#include "../CourseWork/PushingPreflow.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest5
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(check_vertices_in_order)
		{

			vector<int> testVerticesInOrder;
			testVerticesInOrder.push_back(0);
			testVerticesInOrder.push_back(1);
			testVerticesInOrder.push_back(2);
			testVerticesInOrder.push_back(3);
			testVerticesInOrder.push_back(4);
			testVerticesInOrder.push_back(5);

			ifstream file;
			string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input_test_3.txt";
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
			
			Assert::IsTrue(verticesInOrder.size() == 6);
			for (int i = 0; i < verticesInOrder.size(); i++) {
				Assert::AreEqual(testVerticesInOrder[i], verticesInOrder[i]);
			}
		}

		TEST_METHOD(check_parsed_string)
		{

			vector<ParsedString> testParsedString;
			testParsedString.push_back(ParsedString((int)'S', (int)'O', 3));
			testParsedString.push_back(ParsedString((int)'S', (int)'P', 3));
			testParsedString.push_back(ParsedString((int)'O', (int)'Q', 3));
			testParsedString.push_back(ParsedString((int)'O', (int)'P', 2));
			testParsedString.push_back(ParsedString((int)'P', (int)'R', 2));
			testParsedString.push_back(ParsedString((int)'Q', (int)'R', 4));
			testParsedString.push_back(ParsedString((int)'Q', (int)'T', 2));
			testParsedString.push_back(ParsedString((int)'R', (int)'T', 3));

			ifstream file;
			string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input_test_3.txt";
			file.open(path);
			if (!file) throw runtime_error("File doesn't exist");

			vector<ParsedString> parseString;

			parseString = parseFile(file, parseString);

			Assert::IsTrue(testParsedString.size() == 8);
			for (int i = 0; i < testParsedString.size(); i++) {
				Assert::IsTrue(parseString[i].isEqual(testParsedString[i]));
			}
		}

		TEST_METHOD(check_one_vertex)
		{
			vector<int> oneVertex, testVertex;
			testVertex.push_back((int)'S');
			testVertex.push_back((int)'O');
			testVertex.push_back((int)'P');
			testVertex.push_back((int)'Q');
			testVertex.push_back((int)'R');
			testVertex.push_back((int)'T');
			ifstream file;
			string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input_test_3.txt";
			file.open(path);
			if (!file) throw runtime_error("File doesn't exist");

			vector<ParsedString> parseString;

			parseString = parseFile(file, parseString);

			oneVertex = NumberOfVertices(parseString);

			Assert::IsTrue(oneVertex.size() == 6);
			for (int i = 0; i < oneVertex.size(); i++) {
				Assert::AreEqual(testVertex[i], oneVertex[i]);
			}
		}

		TEST_METHOD(check_vertex_size_correct) 
		{
			ifstream file;
			string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input_test_2.txt";
			file.open(path);
			if (!file) throw runtime_error("File doesn't exist");

			vector<ParsedString> parseString;

			parseString = parseFile(file, parseString);


			vector<int> oneVertex = NumberOfVertices(parseString);

			int v = oneVertex.size();
			Assert::AreEqual(v, 6);
		}

		TEST_METHOD(check_max_flow_correct)
		{
			ifstream file;
			string path = "C:\\Users\\Алина\\source\\repos\\TemplatedLinkedList\\CourseWork\\input_test_1.txt";
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

			int maxFlow = g.getMaxFlow(start, end);

			file.close();
			Assert::AreEqual(maxFlow, 5);
		}
	};
}