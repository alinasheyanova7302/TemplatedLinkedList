#include "ShennonFano.h"

void ShennonFano::ShannonCodes(Map<wchar_t, wstring>& table, List<Node<wchar_t, std::wstring>*>& nodes,
	int lenght, int left_index, int right_index)
{
	if (lenght == 0) {
		return;
	}
	if (left_index == right_index)
	{
		return;
	}
	if (right_index - left_index == 1)
	{
	
		std::wstring* str;
		if (table.find(nodes.at(left_index)->getKey(), str))
			str->append(L"0");
		if (table.find(nodes.at(right_index)->getKey(), str))
			str->append(L"1");
	}
	else
	{
	
		float p_full = 0;
		for (int i = left_index; i <= right_index; ++i)
		{
			p_full += nodes.at(i)->getCount() / static_cast<float>(lenght);
		}

	
		float p = 0;
		int split_index = -1;
		const float p_half = p_full * 0.5f;
		for (int i = left_index; i <= right_index; ++i)
		{
			std::wstring* str;
			p += nodes.at(i)->getCount() / static_cast<float>(lenght);
			if (p <= p_half || split_index < 0) {
			split_index = i;
				if (table.find(nodes.at(i)->getKey(), str))
					str->append(L"0");
			}
			else
			{
				if (table.find(nodes.at(i)->getKey(), str))
					str->append(L"1");
			}
		}

		//recursive
		ShannonCodes(table, nodes, lenght, left_index, split_index/* - 1*/);
		ShannonCodes(table, nodes, lenght, split_index + 1, right_index);
	}
}

std::wstring ShennonFano::encode(std::wstring& input, Map<wchar_t, wstring>& table)
{
	std::wstring output;
	if (input.length() && table.getSize())
		for (wchar_t letter : input)
		{
			std::wstring* str;
			if (table.find(letter, str))
				output.append(*str);
		}
	return output;
}

std::wstring ShennonFano::decode(std::wstring input, Map<wchar_t, wstring>& table)
{
	std::wstring output = L"";
	while (input.length() && table.getSize())
	{
		auto iterator = table.getNodes().create_list_iterator();
		bool found = false;
		while (iterator->has_next())
		{
			auto code = iterator->next();
			const unsigned int code_length = code->getValue().length();
			if (input.compare(0, code_length, code->getValue()) == 0)
			{
				output += code->getKey();
				input = input.substr(code_length);
				found = true;
			};
		}
		if (!found) break;
	};
	return output;
}

Map<wchar_t, wstring> ShennonFano::get_table(std::wstring input)
{
	static Map<wchar_t, wstring> letters;
	if (input.length()) {
		for (wchar_t letter : input)
		{
			letters.insert(letter, L"");
		}
		List<Node<wchar_t, std::wstring>*> nodes = letters.getNodes();
		nodes.sort(count_compare);
		ShannonCodes(letters, nodes, input.length(), 0, letters.getSize() - 1);
	}
	return letters;
}