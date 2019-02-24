#pragma once

#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class List

{

private:

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

	void push_back(T); // добавление в конец списка

	void push_front(T); // добавление в начало списка

	void pop_back(); // удаление последнего элемента

	void pop_front(); // удаление первого элемента

	void insert(T, size_t); // добавление элемента по индексу

	T at(size_t); // получение элемента по индексу

	void f_delete(size_t); // удаление элемента по индексу

	size_t get_size(); // получение размера списка

	void print_to_console(); // вывод элементов списка в консоль через разделитель, не использовать at

	void clear(); // удаление всех элементов списка

	void set(size_t, T); // замена элемента по индексу на передаваемый элемент

	bool isEmpty(); // проверка на пустоту списка

	bool contains(List *list); // проверка на содержание другого списка в списке

	bool is_equal(List *list); // сравнение двух списков

	size_t size;

};

template<typename T>
List<T>::List()

{

	reset_list();

	size = 0;

}

template<typename T>
List<T>::~List()

{

	cout << "Вызвался деструктор!" << endl;

	clear();

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

		throw std::out_of_range("Индекс больше размера списка");

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

		throw out_of_range("Индекс больше размера списка");


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
void List<T>::f_delete(size_t index)

{

	if (index > size)

	{

		throw std::out_of_range("Индекс больше размера списка");

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
void List<T>::print_to_console()

{

	if (size == 0)

	{

		cout << "Список пустой!" << endl;

		return;

	}

	Node * current = head;

	while (current != NULL)

	{

		cout << current->data << " -> ";

		current = current->next;

	}

	cout << " |X| "<< endl;

}

template<typename T>
void List<T>::set(size_t index, T newElem)

{

	if (index >= size + 1)

	{

		throw out_of_range("Индекс больше размера списка");

		//cout << "Индекс превышает размер, попробуйте еще раз!" << endl;

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

template<typename T>
bool List<T>::contains(List *list)

{

	if (list->size == 0 && size == 0)

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