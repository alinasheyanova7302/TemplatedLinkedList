#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdlib.h>
using namespace std;


// �������
class Vertex
{
public:
	//������ � ���������� �����
	int h, e_flow;

	Vertex(int h, int e_flow)
	{
		this->h = h;
		this->e_flow = e_flow;
	}
};
 //����� 
class Edge
{
public:
	// ����� � ���������� �����������
	int flow, capacity;

	// ����� u--->v has � ��������� �������� u � �������� �������� v.
	int u, v;

	Edge(int flow, int capacity, int u, int v)
	{
		this->flow = flow;
		this->capacity = capacity;
		this->u = u;
		this->v = v;
	}
};


// ��������� ����
class Graph
{
	int V; // ���������� ������
	vector<Vertex> ver; //������ ������
	vector<Edge> edge;

	// ������������ ������� ������ 
	bool push(int u);

	// ��������� ������ �������
	void lift(int u);

	// ������������� ����������
	void preflow(int s);

	// ������� �������������� �����
	void updateReverseEdgeFlow(int i, int flow);

public:
	Graph(int V); // Constructor

	// ���������� ����� � ����
	void addEdge(int u, int v, int w);

	// ������������ �����
	int getMaxFlow(int s, int t);
};

Graph::Graph(int V)
{
	this->V = V;

	// ��������� ������������� � 0
	for (int i = 0; i < V; i++)
		ver.push_back(Vertex(0, 0));
}

void Graph::addEdge(int u, int v, int capacity)
{
	// ��������� ������������� ������
	edge.push_back(Edge(0, capacity, u, v));
}

//���������
void Graph::preflow(int s)
{

	ver[s].h = ver.size();

	//
	for (int i = 0; i < edge.size(); i++)
	{
		// ���� ����� ��� �� ���������
		if (edge[i].u == s)
		{
			edge[i].flow = edge[i].capacity;

			ver[edge[i].v].e_flow += edge[i].flow;

			// ���������� ����� �� v �� s � ���������� ���� �
			// �������� ������ ����
			edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
		}
	}
}

// ������ ������������� �������
int overFlowVertex(vector<Vertex>& ver)
{
	for (int i = 1; i < ver.size() - 1; i++)
		if (ver[i].e_flow > 0)
			return i;

	// -1 ���� ������ �� ����������
	return -1;
}

//���������� ��������� ������
void Graph::updateReverseEdgeFlow(int i, int flow)
{
	int u = edge[i].v, v = edge[i].u;

	for (int j = 0; j < edge.size(); j++)
	{
		if (edge[j].v == v && edge[j].u == u)
		{
			edge[j].flow -= flow;
			return;
		}
	}

	// ���������� ��������� ����� � ���������� ����
	Edge e = Edge(0, flow, u, v);
	edge.push_back(e);
}

//������� ����� �� ������������� ������� u
bool Graph::push(int u)
{
	//�������� ����� ��� �����, ����� ����� ��������
	//� �������� ����� �����������

	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i].u == u)
		{
			// ���� ����� ����� �����������, �� �� ��������� �����������
			if (edge[i].flow == edge[i].capacity)
				continue;

			//������������� �������� ������ � ��� ������
			//���� ������ ������� �������� ������ ������ ��������������� �������
			if (ver[u].h > ver[edge[i].v].h)
			{
				//��������� ����� ����� �������� ����������� ������ �� �����
				//� ����������� ������.
				int flow = _Min_value(edge[i].capacity - edge[i].flow,
					ver[u].e_flow);

				// ��������� ������ ����� ��� ��������������� �������
				ver[u].e_flow -= flow;

				// ��������� ���������� ����� ��� �������� ������
				ver[edge[i].v].e_flow += flow;

				//�������� ���������� �����(� ��������� 0 � ������������� �������)
				edge[i].flow += flow;

				updateReverseEdgeFlow(i, flow);

				return true;
			}
		}
	}
	return false;
}

// ������� �������� ������
void Graph::lift(int u)
{
	// ����������� ������ ����������� �������
	int mh = INT_MAX;

	// ������� �������� ������� � ����������� �������
	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i].u == u)
		{
			//���� ����� ����� �������, �� �� �������� ������
			if (edge[i].flow == edge[i].capacity)
				continue;

			//�������� ����������� ������
			if (ver[edge[i].v].h < mh)
			{
				mh = ver[edge[i].v].h;

				// �������� ������ u
				ver[u].h = mh + 1;
			}
		}
	}
}

//��������� ������������� ������
int Graph::getMaxFlow(int s, int t)
{
	preflow(s);

	//���� �� ���� �� ������ �� ����� �����������
	while (overFlowVertex(ver) != -1)
	{
		int u = overFlowVertex(ver);
		if (!push(u))
			lift(u);
	}

	// ver.back() ���������� ��������� �������, � �������
	// e_flow ����� ������������ �������
	return ver.back().e_flow;
}


class ParsedString
{
public:
	int from = 0;
	int in = 1;
	int capacity = 0;

	ParsedString(int from, int in, int capacity)
	{
		this->from = from;
		this->in = in;
		this->capacity = capacity;
	}

	bool isEqual(ParsedString another)
	{
		return this->capacity == another.capacity &&
			this->from == another.from &&
			this->in == another.in;
	}
};

//���-�� ������ 
vector<int> NumberOfVertices(vector<ParsedString>& parse)
{
	vector<int> oneVertex;
	oneVertex.push_back((int)'S');

	int counter = 1;

	for (int i = 0; i < parse.size(); i++)
	{
		bool flag1 = true;
		for (int j = 0; j < oneVertex.size(); j++)
		{
			if (parse[i].from == oneVertex[j])
				flag1 = false;
		}
		if (flag1 && parse[i].from != (int)'S' && parse[i].from != (int)'T')
		{
			oneVertex.push_back(parse[i].from);
			counter++;
		}

		bool flag2 = true;
		for (int j = 0; j < oneVertex.size(); j++)
		{
			if (parse[i].in == oneVertex[j])
				flag2 = false;
		}
		if (flag2 && parse[i].in != (int)'S' && parse[i].in != (int)'T')
		{
			oneVertex.push_back(parse[i].in);
			counter++;
		}

	}
	oneVertex.push_back((int)'T');
	return oneVertex;
}

//���������� ����
void buildNetwork(vector<ParsedString>& parse, vector<int>& oneVertex, vector<int>& verticesInOrder, Graph& g)
{
	for (int i = 0; i < parse.size(); i++)
	{
		int from = 0;
		int in = 0;
		for (int j = 0; j < oneVertex.size(); j++)
		{
			if (parse[i].from == oneVertex[j])
				from = verticesInOrder[j];
			if (parse[i].in == oneVertex[j])
			{
				in = verticesInOrder[j];
			}

		}
		g.addEdge(from, in, parse[i].capacity);
	}
}

vector<ParsedString> parseFile(ifstream& file, vector<ParsedString>& parseString)
{
	while (!file.eof())
	{
		string oneString;
		string bufferStr;

		int dividedString[3];
		int j = 0;
		getline(file, oneString);
		if (oneString == "")
			throw out_of_range("Incorrect file");
		for (int i = 0; i < oneString.size(); i++)
		{
			char ch = oneString[i];
			if (ch != ' ')
				bufferStr += ch;
			else
			{
				if (bufferStr.size() == 1 && (int)bufferStr[0] >= 65 && (int)bufferStr[0] <= 90)
				{
					dividedString[j] = (int)bufferStr[0];
					bufferStr = "";
				}
				else
					if (j < 2)
						throw out_of_range("Incorrect file");
				j++;
			}
			if (j == 2)
			{
				bool flag = true;
				for (int k = 0; k < bufferStr.size(); k++)
				{
					if ((int)bufferStr[k] < 48)
						flag = false;
					else
						if ((int)bufferStr[k] > 57)
							flag = false;
				}
				if (flag)
					dividedString[2] = atoi(bufferStr.c_str());
				else
					throw out_of_range("Incorrect file");
			}
			if (j > 2)
				throw out_of_range("Incorrect file");
		}
		parseString.push_back(ParsedString(dividedString[0], dividedString[1], dividedString[2]));
		cout << (char)dividedString[0] << " " << (char)dividedString[1] << " " << dividedString[2] << endl;
	}
	return parseString;
}

vector<int> convertCharToNumber(vector<int>& oneVertex, vector<int>& verticesInOrder)
{
	verticesInOrder.push_back(0);

	int counter = 1;
	for (int i = 0; i < oneVertex.size(); i++)
	{
		if (oneVertex[i] != (int)'S' && oneVertex[i] != (int)'T')
		{
			verticesInOrder.push_back(counter);
			counter++;
		}
	}
	verticesInOrder.push_back(verticesInOrder.size());

	return verticesInOrder;
}
