#include "stdafx.h"
#include "CppUnitTest.h"
#include "../TemplatedLinkedList/Iterator.h"
#include "../TemplatedLinkedList/List.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(LinkedList_isEmpty_true)
		{
			List<int> list;
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(get_size_true_1)
		{
			List<int> list;
			Assert::IsTrue(list.get_size() == 0);
		}

		TEST_METHOD(get_size_true_2)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.get_size() == 4);
		}

		TEST_METHOD(at)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);

			Assert::IsTrue(list.at(1) == 1
				&& list.at(2) == 2
				&& list.at(3) == 3
				&& list.at(4) == 4);
		}

		TEST_METHOD(at_empty)
		{
			try {
				List<int> list;

				Assert::IsTrue(list.at(1) == 1);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "index is larger than list size");
			}
		}
		
		TEST_METHOD(LinkedList_isEmpty_false)
		{
			List<int> list;
			list.push_front(0);
			Assert::IsFalse(list.isEmpty());
		}

		TEST_METHOD(push_back_is_valid_1)
		{
			List<int> list;
			list.push_back(1);
			Assert::IsTrue(list.at(1) == 1 && list.get_size() == 1);
		}

		TEST_METHOD(push_back_is_valid_2)
		{
			List<int> list;
			list.push_front(2);
			list.push_front(1);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.at(4) == 4); // 1 2 3 4
		}

		TEST_METHOD(push_front_is_valid_1)
		{
			List<int> list;
			list.push_front(2);
			list.push_front(1);
			list.push_back(3);
			list.push_back(4);
			Assert::IsTrue(list.at(1) == 1); // 1 2 3 4
		}

		TEST_METHOD(push_front_is_valid_2)
		{
			List<int> list;
			list.push_front(1);

			Assert::IsTrue(list.at(1) == 1 && list.get_size() == 1);
		}

		TEST_METHOD(equals_true)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(equals_true_char)
		{
			List<char> list1;
			list1.push_back('o');
			list1.push_back('a');
			list1.push_back('t');
			list1.push_back('c');

			List<char> list2;
			list2.push_back('o');
			list2.push_back('a');
			list2.push_back('t');
			list2.push_back('c');

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(equals_false_1)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(3);
			list2.push_back(3);
			list2.push_back(4);

			Assert::IsFalse(list1.is_equal(&list2));
		}

		TEST_METHOD(equals_false_2)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);

			Assert::IsFalse(list1.is_equal(&list2));
		}

		TEST_METHOD(pop_front_empty)
		{
			List<int> list1;

			List<int> list2;

			list1.pop_front();

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(pop_front)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.pop_front();

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(pop_empty)
		{
			List<int> list1;

			List<int> list2;

			list1.pop_back();

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(pop_back)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);

			list1.pop_back();

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(insert_empty)
		{
			List<int> list1;

			List<int> list2;
			list2.push_back(1);

			list1.insert(1, 1);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(insert_empty_middle_index)
		{
			try
			{
				List<int> list1;

				list1.insert(5, 1);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "index is larger than list size");
			}
		}

		TEST_METHOD(insert_middle)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(2, 2);

			Assert::IsTrue(list1.is_equal(&list2));
		}


		TEST_METHOD(insert_front)
		{
			List<int> list1;
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(1, 1);

			Assert::IsTrue(list1.is_equal(&list2));
		}
		TEST_METHOD(insert_back)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.insert(4, 4);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(remove_empty)
		{
			try
			{
				List<int> list1;

				list1.remove(3);
			}
			catch (std::out_of_range o_ex)
			{
				Assert::AreEqual(o_ex.what(), "index is larger than list size");
			}
		}
		TEST_METHOD(remove_back)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(3);

			list1.remove(4);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(remove_front)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(2);
			list2.push_back(3);
			list2.push_back(4);

			list1.remove(1);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(remove)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);
			list2.push_back(4);

			list1.remove(3);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(get_size_false)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(4);
			Assert::IsFalse(list.get_size() == 3);
		}

		TEST_METHOD(clear_1)
		{
			List<int> list;
			list.push_back(1);
			list.push_back(2);
			list.push_back(3);
			list.push_back(4);

			list.clear();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(clear_2)
		{
			List<int> list;
			list.clear();
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(set)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(1);

			List<int> list2;
			list2.push_back(1);
			list2.push_back(2);

			list1.set(2, 2);

			Assert::IsTrue(list1.is_equal(&list2));
		}

		TEST_METHOD(isEmpty_true)
		{
			List<int> list;
			Assert::IsTrue(list.isEmpty());
		}

		TEST_METHOD(isEmpty_false)
		{
			List<int> list;
			list.push_back(1);

			Assert::IsFalse(list.isEmpty());
		}

		TEST_METHOD(contains_list_with_empty_list)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;

			Assert::IsTrue(list1.contains(&list2));
		}

		TEST_METHOD(contains_list_with_fill_list_true_1)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(1);

			Assert::IsTrue(list1.contains(&list2));
		}

		TEST_METHOD(contains_list_with_fill_list_true)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			Assert::IsTrue(list1.contains(&list1));
		}

		TEST_METHOD(contains_list_with_fill_list_false)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);

			List<int> list2;
			list2.push_back(4);
			list2.push_back(3);

			Assert::IsFalse(list1.contains(&list2));
		}

		TEST_METHOD(contains_data_true)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);
			Assert::IsTrue(list1.contains(1));
		}

		TEST_METHOD(contains_data_false)
		{
			List<int> list1;
			list1.push_back(1);
			list1.push_back(2);
			list1.push_back(3);
			list1.push_back(4);
			Assert::IsFalse(list1.contains(5));
		}
	};
}