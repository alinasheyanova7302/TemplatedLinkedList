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
			Assert::IsTrue(map.getSize() == 0);
		}

		TEST_METHOD(map_insert_all_new)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 3 &&
				getKeys.at(0) == -1 && getValues.at(0) == 0 &&
				getKeys.at(1) == 0 && getValues.at(1) == 1 &&
				getKeys.at(2) == 1 && getValues.at(2) == 2);
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
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 3 &&
				getKeys.at(0) == -1 && getValues.at(0) == 0 &&
				getKeys.at(1) == 0 && getValues.at(1) == 1 &&
				getKeys.at(2) == 1 && getValues.at(2) == 2);
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
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 3 &&
				getKeys.at(0) == -1 && getValues.at(0) == 10 &&
				getKeys.at(1) == 0 && getValues.at(1) == 21 &&
				getKeys.at(2) == 1 && getValues.at(2) == 22);
		}

		TEST_METHOD(map_keys_non_empty)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 3 &&
				getKeys.at(0) == -1 &&
				getKeys.at(1) == 0 &&
				getKeys.at(2) == 1);
		}

		TEST_METHOD(map_keys_empty)
		{
			Map<int, int> map;
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 0 && getKeys.isEmpty());
		}

		TEST_METHOD(map_values_non_empty)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto getValues = map.getValues();
			Assert::IsTrue(map.getSize() == 3 &&
				getValues.at(0) == 0 &&
				getValues.at(1) == 1 &&
				getValues.at(2) == 2);
		}

		TEST_METHOD(map_values_empty)
		{
			Map<int, int> map;
			auto getValues = map.getValues();
			Assert::IsTrue(map.getSize() == 0 && getValues.isEmpty());
		}

		TEST_METHOD(map_remove_non_empty_exist_first)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);

			map.remove("first");

			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 2 &&
				getKeys.at(0) == "second" && getValues.at(0) == 1 &&
				getKeys.at(1) == "third" && getValues.at(1) == 2);
		}

		TEST_METHOD(map_remove_non_empty_exist_second)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("second");
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 2 &&
				getKeys.at(0) == "first" && getValues.at(0) == 0 &&
				getKeys.at(1) == "third" && getValues.at(1) == 2);
		}

		TEST_METHOD(map_remove_non_empty_exist_third)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("third");
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 2 &&
				getKeys.at(0) == "first" && getValues.at(0) == 0 &&
				getKeys.at(1) == "second" && getValues.at(1) == 1);
		}

		TEST_METHOD(map_remove_empty)
		{
			Map<bool, int> map;
			map.remove(false);
			Assert::IsTrue(map.getSize() == 0);
		}

		TEST_METHOD(map_remove_non_empty_non_exist_forth)
		{
			Map<string, int> map;
			map.insert("first", 0);
			map.insert("second", 1);
			map.insert("third", 2);
			map.remove("forth");
			auto getValues = map.getValues();
			auto getKeys = map.getKeys();
			Assert::IsTrue(map.getSize() == 3 &&
				getKeys.at(0) == "first" && getValues.at(0) == 0 &&
				getKeys.at(1) == "second" && getValues.at(1) == 1 &&
				getKeys.at(2) == "third" && getValues.at(2) == 2);
		}

		TEST_METHOD(map_contains_non_empty_non_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto getValues = map.getValues();
			Assert::IsFalse(map.isContainedIn(2));
		}

		TEST_METHOD(map_contains_empty)
		{
			Map<int, int> map;
			auto getValues = map.getValues();
			Assert::IsFalse(map.isContainedIn(0));
		}

		TEST_METHOD(map_contains_non_empty_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto getValues = map.getValues();
			Assert::IsTrue(
				map.isContainedIn(-1) &&
				map.isContainedIn(0) &&
				map.isContainedIn(1));
		}

		TEST_METHOD(map_find_non_empty_exist)
		{
			Map<int, int> map;
			map.insert(-1, 0);
			map.insert(0, 1);
			map.insert(1, 2);
			auto n = map.find(1) == 2;
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
			Assert::IsTrue(map.getSize() == 0);
		}

		TEST_METHOD(map_clear_empty)
		{
			Map<int, int> map;
			map.clear();
			Assert::IsTrue(map.getSize() == 0);
		}
	};
}