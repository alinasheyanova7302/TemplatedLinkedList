#pragma once
#include <iostream>
#include "../TemplatedLinkedList/List.h"
#include "../TemplatedLinkedList/Iterator.h"
using namespace std;

enum Color { R, B };

template<class Key, class Value> 
class Node
{ public:
	Key key;
	Value value;
	bool color;
	Node* left, *right, *parent;
	unsigned int count;//number of inserts with value changes

	Node(Key key, Value value)
	{
		this->key = key;
		this->value = value;
		this->count = 1;
		color = R;
		left = right = parent = nullptr;
	}

	Key getKey() { return this->key; }
	Value getValue() { return this->value; }
	unsigned int getCount() { return this->count; }
};

template<class Key, class Value> 
class Map
{
private:
	Node<Key, Value>* root; 
	size_t size;
protected:
	void rotateLeft(Node<Key, Value>*&);
	void rotateRight(Node<Key, Value>*&);
	void fixInsertRBTree(Node<Key, Value>*&);
	void fixDeleteRBTree(Node<Key, Value>*&);
	static bool getColor(Node<Key, Value>*&);
	static void setColor(Node<Key, Value>*&, bool);
	static Node<Key, Value>* minValueNode(Node<Key, Value>*);
	static Node<Key, Value>* maxValueNode(Node<Key, Value>*);
	Node<Key, Value>* insertBST(Node<Key, Value>*, Node<Key, Value>*);
	Node<Key, Value>* deleteBST(Node<Key, Value>*, Key);
	int getBlackHeight(Node<Key, Value>*);
	void tree_delete(Node<Key, Value>*);
	Node<Key, Value>* node_find(Node<Key, Value>*, Key);

	class SftIterator : public Iterator<Node<Key, Value>*>
	{
	public:
		SftIterator(Node < Key, Value>* root)
		{
			current = root;
		};

	private:
		Node<Key, Value>* next() override;
		bool has_next() override
		{
			return (list.get_size() || current != nullptr);
		};
		List<Node<Key, Value>*> list;
		Node<Key, Value>* current;
	};
	Iterator<Node<Key, Value>*>* create_sft_iterator() const
	{
		if (this == nullptr && this->root == nullptr) throw std::exception("Map does not exist");
		return new SftIterator(this->root);
	};
public:
	Map() { root = nullptr; size = 0; };
	~Map() { 
		//clear(); 
	}
	size_t getSize()
	{
		return size;
	};
	List<Node<Key, Value>*> getNodes();
	void insert(Key key, Value value); //insert key and value to map, or replace value by key
	void remove(Key);
	Value find(Key); //return nullptr if not find
	bool find(Key, Value * &);
	bool isContainedIn(Key key);
	void clear(); //clear whole map
	List<Key> getKeys();
	List<Value> getValues();
};

template <class Key, class Value>
void Map<Key, Value>::rotateLeft(Node<Key, Value>*& node)
{
	Node<Key, Value>* right_child = node->right;
	node->right = right_child->left;

	if (node->right != nullptr)
		node->right->parent = node;

	right_child->parent = node->parent;

	if (node->parent == nullptr)
		root = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;

	right_child->left = node;
	node->parent = right_child;
}

template <class Key, class Value>
void Map<Key, Value>::rotateRight(Node<Key, Value> * &node)
{
	Node<Key, Value>* left_child = node->left;
	node->left = left_child->right;

	if (node->left != nullptr)
		node->left->parent = node;

	left_child->parent = node->parent;

	if (node->parent == nullptr)
		root = left_child;
	else if (node == node->parent->left)
		node->parent->left = left_child;
	else
		node->parent->right = left_child;

	left_child->right = node;
	node->parent = left_child;
}

template <class Key, class Value>
void Map<Key, Value>::fixInsertRBTree(Node<Key, Value> * &node)
{
	Node<Key, Value>* parent = nullptr;
	Node<Key, Value>* grandparent = nullptr;
	while (node != root && getColor(node) == R && getColor(node->parent) == R) {
		parent = node->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			Node<Key, Value>* uncle = grandparent->right;
			if (getColor(uncle) == R) {
				setColor(uncle, B);
				setColor(parent, B);
				setColor(grandparent, R);
				node = grandparent;
			}
			else {
				if (node == parent->right) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		else {
			Node<Key, Value>* uncle = grandparent->left;
			if (getColor(uncle) == R) {
				setColor(uncle, B);
				setColor(parent, B);
				setColor(grandparent, R);
				node = grandparent;
			}
			else {
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				swap(parent->color, grandparent->color);
				node = parent;
			}
		}
	}
	setColor(root, B);
}

template <class Key, class Value>
void Map<Key, Value>::fixDeleteRBTree(Node<Key, Value> * &node)
{
	if (node == nullptr)
		return;

	if (node == root) {
		root = nullptr;
		size--;
		return;
	}

	if (getColor(node) == R || getColor(node->left) == R || getColor(node->right) == R) {
		Node<Key, Value>* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, B);
			delete (node);
			size--;
		}
		else {
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, B);
			delete (node);
			size--;
		}
	}
	else {
		Node<Key, Value>* sibling = nullptr;
		Node<Key, Value>* parent = nullptr;
		Node<Key, Value>* temp = node;
		//setColor(node, DOUBLE_BLACK);
		while (temp != root && /*getColor(node) == DOUBLE_BLACK*/ temp->right == nullptr && temp->left == nullptr) { // check if not root and while leaf (both == nullprt)
			parent = temp->parent;
			if (temp == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == R) {
					setColor(sibling, B);
					setColor(parent, R);
					rotateLeft(parent);
				}
				else {
					if (getColor(sibling->left) == B && getColor(sibling->right) == B) {
						setColor(sibling, R);
						if (getColor(parent) == R)
							setColor(parent, B);
						temp = parent;
					}
					else {
						if (getColor(sibling->right) == B) {
							setColor(sibling->left, B);
							setColor(sibling, R);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, B);
						setColor(sibling->right, B);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == R) {
					setColor(sibling, B);
					setColor(parent, R);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == B && getColor(sibling->right) == B) {
						setColor(sibling, R);
						if (getColor(parent) == R)
							setColor(parent, B);
						temp = parent;
					}
					else {
						if (getColor(sibling->left) == B) {
							setColor(sibling->right, B);
							setColor(sibling, R);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, B);
						setColor(sibling->left, B);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		delete(node);
		size--;
		setColor(root, B);
	}
}

template <class Key, class Value>
bool Map<Key, Value>::getColor(Node<Key, Value> * &node)
{
	if (node == nullptr)
		return B;

	return node->color;
}

template <class Key, class Value>
void Map<Key, Value>::setColor(Node<Key, Value> * &node, bool color)
{
	if (node == nullptr)
		return;

	node->color = color;
}

template <class Key, class Value>
Node<Key, Value>* Map<Key, Value>::minValueNode(Node<Key, Value> * node) {
	while (node->left != nullptr)
		node = node->left;
	return node;
}

template <class Key, class Value>
Node<Key, Value>* Map<Key, Value>::maxValueNode(Node<Key, Value> * node)
{
	while (node->right != nullptr)
		node = node->right;
	return node;
}

template <class Key, class Value>
Node<Key, Value>* Map<Key, Value>::insertBST(Node<Key, Value> * root, Node<Key, Value> * node)
{
	if (root == nullptr) {
		size++;
		return node;
	}

	if (root->key > node->key) {
		root->left = insertBST(root->left, node);
		root->left->parent = root;
	}
	else if (root->key < node->key) {
		root->right = insertBST(root->right, node);
		root->right->parent = root;
	}
	else if (root->key == node->key) {
		root->value = node->value;
		++root->count;
	}

	return root;
}

template <class Key, class Value>
Node<Key, Value>* Map<Key, Value>::deleteBST(Node<Key, Value> * root, Key key)
{
	if (root == nullptr) {
		return root;
	}

	if (key < root->key)
		return deleteBST(root->left, key);

	if (key > root->key)
		return deleteBST(root->right, key);

	if (root->left == nullptr || root->right == nullptr)
		return root;

	Node<Key, Value> * temp = minValueNode(root->right);
	root->key = temp->key;
	root->value = temp->value;
	return deleteBST(root->right, temp->key);
}

template <class Key, class Value>
int Map<Key, Value>::getBlackHeight(Node<Key, Value> * node)
{
	int count = 0;
	while (node != nullptr) {
		if (getColor(node) == B)
			count++;
		node = node->left;
	}
	return count;
}

template <class Key, class Value>
void Map<Key, Value>::tree_delete(Node<Key, Value> * node)
{
	if (node == nullptr) return;
	tree_delete(node->left);
	tree_delete(node->right);
	delete node;
	size--;
}

template <class Key, class Value>
Node<Key, Value>* Map<Key, Value>::node_find(Node<Key, Value> * node, Key key)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
		return node_find(node->left, key);
	if (key > node->key)
		return node_find(node->right, key);
	if (node->key == key)
		return node;
	return nullptr;
}

template <class Key, class Value>
Node<Key, Value> * Map<Key, Value>::SftIterator::next()
{
	while (current != nullptr) {
		list.push_front(current);
		current = current->left;
	}
	current = list.at(0);
	list.pop_front();
	auto temp = current;
	current = current->right;
	return temp;
}

template <class Key, class Value>
void Map<Key, Value>::insert(Key key, Value value)
{
	auto* node = new Node<Key, Value>(key, value);
	root = insertBST(root, node);
	fixInsertRBTree(node);
}

template <class Key, class Value>
void Map<Key, Value>::remove(Key key)
{
	Node<Key, Value>* node = deleteBST(root, key);
	fixDeleteRBTree(node);
}

template <class Key, class Value>
Value Map<Key, Value>::find(Key key)
{
	Node<Key, Value>* temp = node_find(root, key);
	if (temp == nullptr)
		return {};
	return temp->value;
}

template <class Key, class Value>
bool Map<Key, Value>::isContainedIn(Key key)
{
	Node<Key, Value>* temp = node_find(root, key);
	if (temp == nullptr) return false;
	return temp->key == key;
}

template <class Key, class Value>
void Map<Key, Value>::clear()
{
	tree_delete(root);
	root = nullptr;
}

template <class Key, class Value>
List<Key> Map<Key, Value>::getKeys()
{
	List<Key> keys;
	if (this->getSize() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			keys.push_back(iterator->next()->key);
		}
	}
	return keys;
}

template <class Key, class Value>
List<Value> Map<Key, Value>::getValues()
{
	List<Value> values;
	if (this->getSize() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			values.push_back(iterator->next()->value);
		}
	}
	return values;
}

template <class Key, class Value>
bool Map<Key, Value>::find(Key key, Value * &value)
{
	Node<Key, Value>* temp = node_find(root, key);
	if (temp == nullptr)
		return false;
	value = &temp->value;
	return true;
}

template <class Key, class Value>
List<Node<Key, Value>*> Map<Key, Value>::getNodes()
{
	List<Node<Key, Value>*> nodes;
	if (this->getSize() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			nodes.push_back(iterator->next());
		}
	}
	return nodes;
}