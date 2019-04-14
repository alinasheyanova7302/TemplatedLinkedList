#pragma once
#include <iostream>
#include "../TemplatedLinkedList/List.h"
#include "../Map/Map.h"
class ShennonFano
{
private:
	List<Node<wchar_t, std::wstring>*> nodes;
	void ShannonCodes(Map<wchar_t, wstring>& table, List<Node<wchar_t, std::wstring>*>& nodes, int lenght, int left_index, int right_index);
	static bool count_compare(Node<wchar_t, wstring>* elem1, Node<wchar_t, wstring>* elem2)
	{
		auto a = (Node<wchar_t, wstring>*)(elem1);
		auto b = (Node<wchar_t, wstring>*)(elem2);
		return (a->getCount() > b->getCount());
	}
public:
	Map<wchar_t, wstring> get_table(std::wstring input);
	std::wstring encode(std::wstring& input, Map<wchar_t, wstring>& table);
	std::wstring decode(std::wstring input, Map<wchar_t, wstring>& table);
	ShennonFano()
	{
		nodes.clear();
	};
	~ShennonFano()
	{
		nodes.clear();
	};
};