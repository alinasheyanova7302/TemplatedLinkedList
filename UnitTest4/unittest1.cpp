#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "../FloydWarshall/FloydWarshall.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Vertices_num) {
			setlocale(LC_ALL, "rus");
			auto* vertices = new List<std::string>;
			vector<string> strings;    //������� ������ �����
			string line;
			line = "C����-���������;������;10;20";
			strings.push_back(line);
			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			auto num = vertices->get_size();

			Assert::IsTrue(num == 2);
		}

		TEST_METHOD(Adj_matrix)//������������ �������� �������
		{
			unsigned short** matrix;
			setlocale(LC_ALL, "rus");
			auto* vertices = new List<std::string>;
			vector<string> strings;    //������� ������ �����
			string line1, line2, line3;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";
			line3 = "���;������;40;20";
			strings.push_back(line1); strings.push_back(line2); strings.push_back(line3);
			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}
			Assert::IsTrue(matrix[0][1] == 10);
		}

		TEST_METHOD(AdjMatr_diag) {
			setlocale(LC_ALL, "rus");
			auto* vertices = new List<std::string>;
			vector<string> strings;    //������� ������ �����
			string line1, line2, line3;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";
			line3 = "���;������;40;20";
			strings.push_back(line1); strings.push_back(line2); strings.push_back(line3);
			unsigned short** matrix;


			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}
			Assert::IsTrue(matrix[0][0] == matrix[1][1]);
		}
		TEST_METHOD(AdjMatr_NA) {
			setlocale(LC_ALL, "rus");
			auto* vertices = new List<std::string>;
			vector<string> strings;    //������� ������ �����
			string line1, line2;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";

			strings.push_back(line1); strings.push_back(line2);
			unsigned short** matrix;


			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}

			Assert::IsTrue(matrix[1][2] == 65535);
		}

		TEST_METHOD(MinPath) {

			auto* vertices = new List<std::string>;
			unsigned short** matrix;
			unsigned short** min_paths;
			setlocale(LC_ALL, "rus");
			vector<string> strings;    //������� ������ �����
			string line1, line2, line3;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";
			line3 = "���;������;40;10";
			strings.push_back(line1); strings.push_back(line2); strings.push_back(line3);

			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}

			min_paths = find_min_paths(vertices->get_size(), matrix);

			Assert::IsTrue(min_paths[0][2] < matrix[0][2]);
		}

		TEST_METHOD(MinPath_diag) {
			auto* vertices = new List<std::string>;
			unsigned short** matrix;
			unsigned short** min_paths;
			setlocale(LC_ALL, "rus");
			vector<string> strings;    //������� ������ �����
			string line1, line2, line3;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";
			line3 = "���;������;40;10";
			strings.push_back(line1); strings.push_back(line2); strings.push_back(line3);

			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}

			min_paths = find_min_paths(vertices->get_size(), matrix);
			Assert::IsTrue(min_paths[1][1] == 65535);
		}

		TEST_METHOD(MinPath_NotChangePath) {
			auto* vertices = new List<std::string>;
			unsigned short** matrix;
			unsigned short** min_paths;
			setlocale(LC_ALL, "rus");
			vector<string> strings;    //������� ������ �����
			string line1, line2, line3;
			line1 = "C����-���������;������;10;20";
			line2 = "C����-���������;���;30;25";
			line3 = "���;������;40;20";
			strings.push_back(line1);
			strings.push_back(line2);
			strings.push_back(line3);

			for (int i = 0; i < strings.size(); i++) {
				getting_cities(strings[i], vertices);
			}
			matrix = new unsigned short*[vertices->get_size()];
			make_matrix_bases(matrix, vertices->get_size());

			for (int i = 0; i < strings.size(); i++) {
				make_matrix(strings[i], vertices, matrix);
			}

			min_paths = find_min_paths(vertices->get_size(), matrix);


			Assert::IsTrue(min_paths[0][2] == matrix[0][2]);
		}

		TEST_METHOD(MinPathRight) {
			vector<string> strings_for_reading;
			List<string>* cities = new List<string>; 
			unsigned short** matrix_all_itinerary; 
			unsigned short** min_itenerary; 

			string line1, line2, line3, line4, line5, line6, line7, line8, line9, line10;

			line1 = "������;���-����;30;50";
			line2 = "������;������;45;78";
			line3 = "������;���;60;70";
			line4 = "���-����;������;120;80";
			line5 = "���-����;��������;100;80";
			line6 = "������;������;35; 50";
			line7 = "������;������;120;140";
			line8 = "�����-���������;���������;60;30";
			line9 = "�����-���������;������;10;20";
			line10 = "���;������;70;110";

			strings_for_reading.push_back(line1);
			strings_for_reading.push_back(line2);
			strings_for_reading.push_back(line3);
			strings_for_reading.push_back(line4);
			strings_for_reading.push_back(line5);
			strings_for_reading.push_back(line6);
			strings_for_reading.push_back(line7);
			strings_for_reading.push_back(line8);
			strings_for_reading.push_back(line9);
			strings_for_reading.push_back(line10);

			for (int i = 0; i < strings_for_reading.size(); i++) {
				getting_cities(strings_for_reading[i], cities); 
			}


			matrix_all_itinerary = new unsigned short*[cities->get_size()];

			make_matrix_bases(matrix_all_itinerary, cities->get_size());

			for (int i = 0; i < strings_for_reading.size(); i++) {
				make_matrix(strings_for_reading[i], cities, matrix_all_itinerary);
			}

			min_itenerary = find_min_paths(cities->get_size(), matrix_all_itinerary);

			unsigned short res = min_path("�����-���������", "������", matrix_all_itinerary, cities);

			Assert::IsTrue(res == 10);
		};

	};
}