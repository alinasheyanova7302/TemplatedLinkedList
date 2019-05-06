#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "../TemplatedLinkedList/List.h"
#include "FloydWarshall.h"
using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "rus");
	vector<string> strings_for_reading;
	List<string>* cities = new List<string>; //вершины графа
	unsigned short** matrix_all_itinerary; // матрица всех путей
	unsigned short** min_itenerary; //матрица минимальных путей

	strings_for_reading = read_file("Input.txt"); //считываем данные из файла

	for (int i = 0; i < strings_for_reading.size(); i++) {
		getting_cities(strings_for_reading[i], cities); //Получение всех городов
	}

	cout << endl << "Список всех городов: ";
	cout << *cities << endl;
	size_t num = cities->get_size();
	cout << "Количество считанных городов:" << num << "\n";
	matrix_all_itinerary = new unsigned short*[cities->get_size()];

	make_matrix_bases(matrix_all_itinerary, cities->get_size());//матрица всех путей

	for (int i = 0; i < strings_for_reading.size(); i++) {
		make_matrix(strings_for_reading[i], cities, matrix_all_itinerary);
	}

	cout << endl << "Таблица всех маршрутов с ценами на перелет " << endl;
	print_matrix(cities->get_size(), matrix_all_itinerary);
	cout << endl;
	cout << "********************************************************************************\n";

	min_itenerary = find_min_paths(cities->get_size(), matrix_all_itinerary);
	cout << endl << "Таблица маршрутов между городами с указанием наименьшей стоимости: " << endl;
	print_matrix(cities->get_size(), min_itenerary);

	unsigned short res = min_path("Санкт-Петербург", "Москва", matrix_all_itinerary, cities);
	std::cout << endl << res << endl;

	system("PAUSE");
}