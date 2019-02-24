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

		~Node() {
		
		};

	};

	Node * head;

	Node * tail;

public:

	List();

	~List();

	void reset_list();

	void add_first(T newElem);

	void push_back(T); // add to end of list

	void push_front(T); // adding to the top of the list

	void pop_back(); // delete last item

	void pop_front(); // delete first item

	void insert(T, size_t); // add item by index

	T at(size_t); // getting item by index

	void remove(size_t); // delete item by index

	size_t get_size(); // getting list size
	
	void set_size(size_t); //setting list size

	void clear(); // delete all list items

	void set(size_t, T); // replacing an item by index with a passed item

	bool isEmpty(); // check for empty list

	bool contains(List *list); // check for the contents of another list in the list

	bool contains(T data); // check for the content of an item in the list

	bool is_equal(List *list); // comparing two lists
	

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
			return outstream << "[NULL]";
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
bool List<T>::contains(List *list)

{  

	if (list->size == 0)

	{

		return 1;

	}


	Node * current = head;

	Node * current_find = list->head;

	bool contains = false;

	do {

		if (current->data == current_find->data)

		{

			if (current_find->next == nullptr)

			{

				contains = true;

				break;

			}

			current_find = current_find->next;

			current = current->next;

		}

		else

		{

			contains = false;

			current_find = list->head;

			current = current->next;

		}

	} while (current != nullptr);

	return contains;

}

template <class T>
bool List<T>::contains(T data)
{
	Node * current = head;
	bool contains = false;
	do {
		if (current->data == data)
		{
			return true;
		}
		current = current->next;
	} while (current != nullptr);
	return false;
}

template<typename T>
bool List<T>::is_equal(List *list) {

	if (size != list->size)return false;

	if (size == 0 && list->size == 0) return true;

	else {

		Node * current = head;

		Node * current1 = list->head;

		while (current != tail) {

			if (current->data != current1->data)return false;

			current = current->next;

			current1 = current1->next;

		}

		if (current->data != current1->data)return false;

		return true;

	}

}


template<typename T>
List<T>::~List()

{

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

		throw std::out_of_range("index is larger than list size");

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

		throw out_of_range("index is larger than list size");


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

		throw std::out_of_range("index is larger than list size");

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

		throw out_of_range("index is larger than list size");


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

