#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <stdlib.h>
using namespace std;


// Вершина
class Vertex
{
public:
	//Высота и избыточный поток
	int h, e_flow;

	Vertex(int h, int e_flow)
	{
		this->h = h;
		this->e_flow = e_flow;
	}
};
 //ребро 
class Edge
{
public:
	// Поток и пропускная способность
	int flow, capacity;

	// Ребро u--->v has с начальной вершиной u и конечной вершиной v.
	int u, v;

	Edge(int flow, int capacity, int u, int v)
	{
		this->flow = flow;
		this->capacity = capacity;
		this->u = u;
		this->v = v;
	}
};


// Потоковая сеть
class Graph
{
	int V; // Количество вершин
	vector<Vertex> ver; //Список вершин
	vector<Edge> edge;

	// Выталкивание лишнего потока 
	bool push(int u);

	// Изменение высоты вершины
	void lift(int u);

	// Инициализация предпотока
	void preflow(int s);

	// Функция ревертирования ребра
	void updateReverseEdgeFlow(int i, int flow);

public:
	Graph(int V); // Constructor

	// Добавление ребра в граф
	void addEdge(int u, int v, int w);

	// Максимальный поток
	int getMaxFlow(int s, int t);
};

Graph::Graph(int V)
{
	this->V = V;

	// начальная инициализация в 0
	for (int i = 0; i < V; i++)
		ver.push_back(Vertex(0, 0));
}

void Graph::addEdge(int u, int v, int capacity)
{
	// Начальная инициализация потока
	edge.push_back(Edge(0, capacity, u, v));
}

//предпоток
void Graph::preflow(int s)
{

	ver[s].h = ver.size();

	//
	for (int i = 0; i < edge.size(); i++)
	{
		// Если ребро идёт от источника
		if (edge[i].u == s)
		{
			edge[i].flow = edge[i].capacity;

			ver[edge[i].v].e_flow += edge[i].flow;

			// Добавление ребра от v до s в остаточный граф с
			// размером равным нулю
			edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
		}
	}
}

// индекс переполненной вершины
int overFlowVertex(vector<Vertex>& ver)
{
	for (int i = 1; i < ver.size() - 1; i++)
		if (ver[i].e_flow > 0)
			return i;

	// -1 если такого не существует
	return -1;
}

//обновление обратного потока
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

	// добавление обратного ребра в остаточный граф
	Edge e = Edge(0, flow, u, v);
	edge.push_back(e);
}

//Толкаем поток из переполненной вершины u
bool Graph::push(int u)
{
	//Проходим через все ребра, чтобы найти соседний
	//к которому можно протолкнуть

	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i].u == u)
		{
			// если поток равен вместимости, то не получится протолкнуть
			if (edge[i].flow == edge[i].capacity)
				continue;

			//Проталкивание возможно только в том случае
			//если высота смежных объектов меньше высоты переполняющейся вершины
			if (ver[u].h > ver[edge[i].v].h)
			{
				//Толкаемый поток равен минимуму оставшегося потока на ребре
				//и избыточному потоку.
				int flow = _Min_value(edge[i].capacity - edge[i].flow,
					ver[u].e_flow);

				// Уменьшаем лишний поток для переполняющейся вершины
				ver[u].e_flow -= flow;

				// Увеличить избыточный поток для соседних вершин
				ver[edge[i].v].e_flow += flow;

				//Добавить остаточный поток(с мощностью 0 и отрицательным потоком)
				edge[i].flow += flow;

				updateReverseEdgeFlow(i, flow);

				return true;
			}
		}
	}
	return false;
}

// функция поднятия высоты
void Graph::lift(int u)
{
	// минимальная высота примыкающей вершины
	int mh = INT_MAX;

	// находим соседнюю вершину с минимальной высотой
	for (int i = 0; i < edge.size(); i++)
	{
		if (edge[i].u == u)
		{
			//если поток равен ёмкости, то не изменяем высоту
			if (edge[i].flow == edge[i].capacity)
				continue;

			//изменяем минимальную высоту
			if (ver[edge[i].v].h < mh)
			{
				mh = ver[edge[i].v].h;

				// изменяем высоту u
				ver[u].h = mh + 1;
			}
		}
	}
}

//получение максимального потока
int Graph::getMaxFlow(int s, int t)
{
	preflow(s);

	//пока ни одна из вершин не будет переполнена
	while (overFlowVertex(ver) != -1)
	{
		int u = overFlowVertex(ver);
		if (!push(u))
			lift(u);
	}

	// ver.back() возвращает последнюю вершину, у которой
	// e_flow будет максимальным потоком
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

//кол-вл вершин 
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

//Построение сети
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
