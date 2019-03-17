#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Map/Map.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(map_initialize_empty)
		{
			Map<int, int> map;
			Assert::IsTrue(map.size() == 0);
		}

		TEST_METHOD(map_insert_all_new)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 0 &&
				keys.at(1) == 0 && values.at(1) == 1 &&
				keys.at(2) == 1 && values.at(2) == 2);
		}

		TEST_METHOD(map_insert_all_exists_same)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);

			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 0 &&
				keys.at(1) == 0 && values.at(1) == 1 &&
				keys.at(2) == 1 && values.at(2) == 2);
		}

		TEST_METHOD(map_insert_all_exists_another)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);

			map.insert(-1, 10);
			map.insert(0, 21);
			map.insert(1, 22);
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 10 &&
				keys.at(1) == 0 && values.at(1) == 21 &&
				keys.at(2) == 1 && values.at(2) == 22);
		}

		TEST_METHOD(map_keys_non_empty)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 3 &&
				keys.at(0) == -1 &&
				keys.at(1) == 0 &&
				keys.at(2) == 1);
		}

		TEST_METHOD(map_keys_empty)
		{
			Map<int, int> map;
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 0 && keys.isEmpty());
		}

		TEST_METHOD(map_values_non_empty)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto values = map.getValues();
			Assert::IsTrue(map.size() == 3 &&
				values.at(0) == 0 &&
				values.at(1) == 1 &&
				values.at(2) == 2);
		}

		TEST_METHOD(map_values_empty)
		{
			Map<int, int> map;
			auto values = map.getValues();
			Assert::IsTrue(map.size() == 0 && values.isEmpty());
		}

		TEST_METHOD(map_remove_non_empty_exist_first)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("first");
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 2 &&
				keys.at(0) == "second" && values.at(0) == 1 &&
				keys.at(1) == "third" && values.at(1) == 2);
		}

		TEST_METHOD(map_remove_non_empty_exist_second)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("second");
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 2 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "third" && values.at(1) == 2);
		}

		TEST_METHOD(map_remove_non_empty_exist_third)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("third");
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 2 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "second" && values.at(1) == 1);
		}

		TEST_METHOD(map_remove_empty)
		{
			Map<bool, int> map;
			map.remove(false);
			Assert::IsTrue(map.size() == 0);
		}

		TEST_METHOD(map_remove_non_empty_non_exist_forth)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("forth");
			auto values = map.getValues();
			auto keys = map.getKeys();
			Assert::IsTrue(map.size() == 3 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "second" && values.at(1) == 1 &&
				keys.at(2) == "third" && values.at(2) == 2);
		}

		TEST_METHOD(map_contains_non_empty_non_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto values = map.getValues();
			Assert::IsFalse(map.contains(2));
		}

		TEST_METHOD(map_contains_empty)
		{
			Map<int, int> map;
			auto values = map.getValues();
			Assert::IsFalse(map.contains(0));
		}

		TEST_METHOD(map_contains_non_empty_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto values = map.getValues();
			Assert::IsTrue(
				map.contains(-1) &&
				map.contains(0) &&
				map.contains(1));
		}

		TEST_METHOD(map_find_non_empty_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			Assert::IsTrue(
				map.find(-1) == 0 &&
				map.find(0) == 1 &&
				map.find(1) == 2);
		}

		TEST_METHOD(map_find_non_empty_non_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			int default = {};
			Assert::IsTrue(map.find(2) == default);
		}

		TEST_METHOD(map_clear_non_empty)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			map.clear();
			Assert::IsTrue(map.size() == 0);
		}

		TEST_METHOD(map_clear_empty)
		{
			Map<int, int> map;
			map.clear();
			Assert::IsTrue(map.size() == 0);
		}
	};
}