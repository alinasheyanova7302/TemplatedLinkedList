#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "FloydWarshall.h"
using namespace std;
#pragma once

vector<string> read_file(const string& file)// вектор строк на выходе
{

	vector<string> strings;    //создаем вектор строк
	fstream input_file(file);

	if (input_file.is_open())  //если файл был открыт,считываем
	{
		while (!input_file.eof()) {
			string line;
			getline(input_file, line);
			if (!line.empty())
				strings.push_back(line);
		}
	}
	else
		throw runtime_error("Can't open file");
	input_file.close();
	return strings;
}


void make_matrix(string str, List<string>* vertices, unsigned short** matrix)
{
	short flag = 0;
	unsigned short city_1, city_2;
	string v_name = "";  //название вершины
	string weight = "";   //вес ребра между вершинами
	for (int i = 0; i < str.size() + 1; i++)
	{
		if (flag == 0) //записываем первый город
		{
			if (str[i] != ';')
				v_name += str[i];  //считываем посимвольно название города, как только полностью считали,записываем его city_1
			else {
				city_1 = vertices->indexOf(v_name);
				flag++;
				v_name = "";
			}
		}
		else if (flag == 1) //записываем второй город 
		{
			if (str[i] != ';')
				v_name += str[i];
			else {
				city_2 = vertices->indexOf(v_name);//возвращает индекс города
				flag++;
			}
		}
		else if (flag == 2)
		{
			if (str[i] != ';')//цена туда
				weight += str[i];
			else {
				if (weight != "N/A")
					matrix[city_1][city_2] = stoi(weight); //записываем вес, преобразование строки в число
				flag++;
				weight = "";
			}
		}
		else {
			if (str[i] != '\0')
				weight += str[i];//цена назад
			else {
				if (weight != "N/A")
					matrix[city_2][city_1] = stoi(weight);
			}
		}
	}
}
void getting_cities(string str, List <string> *cities)  //разложение строки на отдельные данные
{
	//вектор и список

	string name_of_cities = "";   //название города
	short flag = 0;
	unsigned i = 0;
	while (flag < 2) {
		if (str[i] != ';')
			name_of_cities += str[i];
		else {
			flag++;
			if (!cities->is_in(name_of_cities))//если этого элемента нет, добавляем в список
			{
				cities->push_back(name_of_cities);
			}
			name_of_cities = "";
		}
		i++;
	}
}
unsigned short** find_min_paths(size_t v_num, unsigned short** matrix) {
	//делаем копию матрицы смежности
	unsigned short** min_paths = new unsigned short*[v_num];
	for (int i = 0; i < v_num; i++)
		min_paths[i] = new unsigned short[v_num];
	for (int i = 0; i < v_num; i++) {
		for (int j = 0; j < v_num; j++)
			min_paths[i][j] = matrix[i][j];
	}


	for (int k = 1; k < v_num; k++) {
		for (int i = 0; i < v_num; i++) {
			for (int j = 0; j < v_num; j++) {
				if (((min_paths[i][k] + min_paths[k][j]) < min_paths[i][j]) && (i != j))
					min_paths[i][j] = min_paths[i][k] + min_paths[k][j];
			}
		}
	}
	return min_paths;
}
void print_matrix(size_t v_num, unsigned short** matrix) {
	for (int i = 0; i < v_num; i++) {
		for (int j = 0; j < v_num; j++) {
			if (matrix[i][j] == 65535)
				cout << "--" << ' ';
			else
				cout << matrix[i][j] << ' ';
		}
		cout << endl;
	}
}
void make_matrix_bases(unsigned short** matr, size_t size) {

	for (int i = 0; i < size; i++) //создаем двумерную матрицу
	{
		matr[i] = new unsigned short[size];
	}
	//заполняем нашу матрицу
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			matr[i][j] = 65535;
		}
	}
}

unsigned short min_path(std::string vertex1, std::string vertex2, unsigned short **matrix, List<std::string> *vertices) {
	int in1, in2;
	in1 = vertices->indexOf(vertex1);
	in2 = vertices->indexOf(vertex2);
	if ((in1 == -1) || (in2 == -1))
		throw std::invalid_argument("Wrong input");
	unsigned short **min_paths = find_min_paths(vertices->get_size(), matrix);
	return min_paths[in1][in2];
}