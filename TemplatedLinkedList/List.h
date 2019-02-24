#pragma once

#include <iostream>
#include <stdexcept>
#include "Iterator.h"
using namespace std;

template<typename T>
class List

{

private:
	size_t size;

	class Node
	{

	public:

		T data;

		Node * next;

		Node(T data, Node * next = nullptr) {

			this->data = data;

			this->next = next;

		};

		~Node() {};

	};

	Node * head;

	Node * tail;

public:

	List();

	~List();

	void reset_list();

	void add_first(T newElem);

	void push_back(T); // ���������� � ����� ������

	void push_front(T); // ���������� � ������ ������

	void pop_back(); // �������� ���������� ��������

	void pop_front(); // �������� ������� ��������

	void insert(T, size_t); // ���������� �������� �� �������

	T at(size_t); // ��������� �������� �� �������

	void remove(size_t); // �������� �������� �� �������

	size_t get_size(); // ��������� ������� ������
	
	void set_size(size_t);

	void clear(); // �������� ���� ��������� ������

	void set(size_t, T); // ������ �������� �� ������� �� ������������ �������

	bool isEmpty(); // �������� �� ������� ������

	

	class ListIterator : public Iterator<T>
	{
	public:
		ListIterator(Node* head)
		{
			current = head;
		};

	private:
		T next() override;
		bool has_next() override;
		Node* current;
	};

	Iterator<T>* create_list_iterator();

	friend std::ostream& operator<<(std::ostream& outstream, List<T>& linked_list) {
		if (linked_list.get_size() == 0)
			return outstream << "[nullptr]";
		Iterator<T>* list = linked_list.create_list_iterator();
		while (list->has_next()) {
			outstream << "[" << list->next() << "] -> ";
		}
		outstream << "[NULL]" << std::endl;
		return outstream;
	};

};

template <class T>
T List<T>::ListIterator::next()
{
	if (!current) return T();
	const T data = current->data;
	current = current->next;
	return data;
}

template <class T>
bool List<T>::ListIterator::has_next()
{
	return (current != nullptr);
}

template <class T>
Iterator<T>* List<T>::create_list_iterator()
{
	if (this == nullptr && this->head == nullptr) throw std::exception("Does not exist");
	return new ListIterator(this->head);
}

template<typename T>
List<T>::List()
{
	reset_list();

	size = 0;

}

template<typename T>
List<T>::~List()

{

	cout << "�������� ����������!" << endl;

	clear();

}

template<typename T>
void List<T>::reset_list()

{

	head = nullptr;

	tail = nullptr;

	size = 0;

}

template<typename T>
void List<T>::clear()

{

	if (size == 0)

	{

		return;

	}

	if (size == 1)

	{

		reset_list();

		delete head;

		delete tail;

	}

	else

	{

		while (head != nullptr)

		{

			pop_front();

		}

		reset_list();

		delete head;

		delete tail;

	}

}

template<typename T>
void List<T>::add_first(T newElem)

{

	head = new Node(newElem);

	tail = head;

}

template<typename T>
void List<T>::set_size(size_t size) {
	this->size = size;
}

template<typename T>
void List<T>::push_back(T newElem)

{

	if (size == 0) {

		add_first(newElem);

	}

	else {

		tail->next = new Node(newElem);

		tail = tail->next;

	}

	size++;

}

template<typename T>
void List<T>::push_front(T newElem)

{

	if (size == 0) {

		add_first(newElem);

	}

	else {

		head = new Node(newElem, head);

	}

	size++;

}

template<typename T>
void List<T>::pop_back()

{

	if (size == 0) return;

	if (size == 1) {

		delete head;

		reset_list();

		return;

	}

	else {

		Node * current = head;

		while (current->next != tail) {

			current = current->next;

		}

		current->next = nullptr;

		delete tail;

		tail = current;

	}

	size--;

}

template<typename T>
void List<T>::pop_front()
{

	if (size == 0) return;

	if (size == 1) {

		delete head;

		reset_list();

		return;

	}

	else {

		Node * current = head;

		head = head->next;

		delete current;

	}

	size--;

}

template<typename T>
void List<T>::insert(T newElem, size_t index) {

	if (index > size + 1) {

		throw std::out_of_range("������ ������ ������� ������");

	}

	if (index == 0 || index == 1)

		push_front(newElem);

	else if (size + 1 == index)

		push_back(newElem);

	else {

		index--;

		size_t count = 0;

		Node * current = new Node(newElem);

		Node* temp = head;

		while (count != index - 1) {

			temp = temp->next;

			count++;

		}

		current->next = temp->next;

		temp->next = current;

		size++;

	}

}

template<typename T>
T List<T>::at(size_t index)
{

	if (index >= size + 1) {

		throw out_of_range("������ ������ ������� ������");


	}

	else {

		index--;

		size_t counter = 0;

		Node * current = head;

		while (counter != index) {

			current = current->next;

			counter++;

		}

		return current->data;

	}

}

template<typename T>
void List<T>::remove(size_t index)

{

	if (index > size)

	{

		throw std::out_of_range("������ ������ ������� ������");

		return;

	}

	if (index == size)

	{

		pop_back();

		size;

		return;

	}

	if (index == 1)

	{

		pop_front();

		size;

	}

	else

	{

		index--;

		size_t counter = 0;

		Node * current = head;

		while (counter != index - 1) {

			current = current->next;

			counter++;

		}

		Node * temp = current->next;

		current->next = temp->next;

		delete temp;

		size--;

	}

}

template<typename T>
size_t List<T>::get_size()

{
	return size;
}

template<typename T>
void List<T>::set(size_t index, T newElem)

{

	if (index >= size + 1)

	{

		throw out_of_range("������ ������ ������� ������");

		//cout << "������ ��������� ������, ���������� ��� ���!" << endl;

		return;

	}

	else {

		index--;

		size_t counter = 0;

		Node * current = head;

		while (counter != index) {

			current = current->next;

			counter++;

		}

		current->data = newElem;

	}

}

template<typename T>
bool List<T>::isEmpty()

{

	if (size == 0)

		return true;

	else

		return false;

}
