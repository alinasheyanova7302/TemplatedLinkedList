#pragma once
#include "../TemplatedLinkedList/List.h"
#include "../TemplatedLinkedList/Iterator.h"
using namespace std;

template <class Key, class Value> class Map;

template <class Key, class Value> class node
{
private:
	Key key;
	Value value;
	node *father;
	node *left;
	node *right;
	bool color;

	node(Key key, Value value)
	{
		this->key = key;
		this->value = value;
		left = nullptr;
		right = nullptr;
		father = nullptr;
		color = true;
	}
	friend Map<Key, Value>;
};

template <class Key, class Value> class Map
{
	node<Key, Value> *root;
	size_t size(node<Key, Value>*);
	void rotate_left(node<Key, Value>*);
	void rotate_right(node<Key, Value>*);
	void insert_fix(node<Key, Value>*);
	node<Key, Value>* successor(node<Key, Value>*);
	void delete_fix(node<Key, Value>*);
	node<Key, Value>* node_find(Key key);
	void tree_delete(node<Key, Value>*);
	class SftIterator : public Iterator<node<Key, Value> *>
	{
	public:
		SftIterator(node < Key, Value> * root)
		{
			current = root;
		};

	private:
		node<Key, Value>* next() override;
		bool has_next() override
		{
			return (list.get_size() || current != nullptr);
		};
		List<node<Key, Value>*> list;
		node<Key, Value> * current;
	};
	Iterator<node<Key, Value> *>* create_sft_iterator() const
	{
		if (this == nullptr && this->root == nullptr) throw std::exception("Map does not exist");
		return new SftIterator(this->root);
	};
public:
	size_t size()
	{
		return size(root);
	};

	Map() { root = nullptr; };
	~Map() { clear(); }
	void insert(Key key, Value value);
	void remove(Key);
	Value find(Key);
	bool contains(Key key);
	List<Key> getKeys();
	List<Value> getValues();
	void clear();

};

template <class Key, class Value>
void Map<Key, Value>::insert(Key key, Value value) {
	node<Key, Value> *create = new node<Key, Value>(key, value);
	node<Key, Value> *p = root;
	node<Key, Value> *q = nullptr;
	if (root == nullptr)
	{
		root = create;
		create->father = nullptr;
	}
	else
	{
		while (p != nullptr)
		{
			q = p;
			if (p->key > create->key) p = p->left;
			else if (p->key < create->key) p = p->right;
			else {
				p->value = value;
				return;
			};
		}
		create->father = q;
		if (q->key < create->key) q->right = create;
		else if (q->key > create->key)q->left = create;
		else return;
	}
	insert_fix(create);
}

template<class Key, class Value>
void Map<Key, Value>::insert_fix(node<Key, Value> *p)
{
	node<Key, Value> *x = p;
	while (x != root && x->father->color)
	{
		if (x->father == x->father->father->left)
		{
			node<Key, Value> *y = x->father->father->right;
			if ((y != nullptr) && (y->color))
			{
				x->father->color = 0;
				y->color = 0;
				x->father->father->color;
				x = x->father->father;
			}
			else
			{
				if (x->father->right == x)
				{
					x = x->father;
					rotate_left(x);
				}
				x->father->color = 0;
				x->father->father->color = 1;
				rotate_right(x->father->father);
			}
		}
		else
		{
			node<Key, Value> *y = x->father->father->left;
			if ((y != nullptr) && (y->color))
			{
				x->father->color = 0;
				y->color = 0;
				x->father->father->color = 1;
				x = x->father->father;
			}
			else
			{
				if (x->father->left == x)
				{
					x = x->father;
					rotate_right(x);
				}
				x->father->color = 0;
				x->father->father->color = 1;
				rotate_left(x->father->father);
			}
		}
	}
	root->color = 0;
}

template<class Key, class Value>
void Map<Key, Value>::rotate_right(node<Key, Value>* y)
{
	if (y->left == nullptr)
		return;
	node<Key, Value> *x = y->left;
	node<Key, Value> *b = x->right;
	node<Key, Value> *f = y->father;
	if (f == nullptr)
	{
		x->father = nullptr;
		root = x;
	}
	else
	{
		x->father = f;
		if (f->left == y)
			f->left = x;
		if (f->right == y)
			f->right = x;
	}
	x->right = y;
	y->father = x;
	y->left = b;
	if (b != nullptr)
		b->father = y;
}

template <class Key, class Value>
void Map<Key, Value>::rotate_left(node<Key, Value>* x)
{
	if (x->right == nullptr)
		return;
	node<Key, Value> *y = x->right;
	node<Key, Value> *b = y->left;
	node<Key, Value> *f = x->father;
	if (f == nullptr)
	{
		y->father = nullptr;
		root = y;
	}
	else
	{
		y->father = f;
		if (f->left == x)
			f->left = y;
		if (f->right == x)
			f->right = y;
	}
	y->left = x;
	x->father = y;
	x->right = b;
	if (b != nullptr)
		b->father = x;
}
template<class Key, class Value>
node<Key, Value>* Map<Key, Value>::node_find(Key key)
{
	node<Key, Value> *t = root;
	while (t != nullptr)
	{
		if (t->key == key)
			break;
		if (key > t->key)
			t = t->right;
		else if (key < t->key)
			t = t->left;
	}
	if (t == nullptr)
		return nullptr;
	if (t->key == key)
		return t;
	return nullptr;
}

template <class Key, class Value>
void Map<Key, Value>::tree_delete(node<Key, Value> * p)
{
	if (p == nullptr) return;
	tree_delete(p->left);
	tree_delete(p->right);
	free(p);
}

template <class Key, class Value>
node<Key, Value>* Map<Key, Value>::SftIterator::next()
{
	while (current != nullptr) {
		list.push_front(current);
		current = current->left;
	}
	current = list.at((size_t)0);
	list.pop_front();
	auto p = current;
	current = current->right;
	return p;
}

template <class Key, class Value>
bool Map<Key, Value>::contains(Key key)
{
	node<Key, Value> *t = node_find(key);
	if (t == nullptr) return false;
	return t->key == key;
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
	if (this->size() != 0) {
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
	if (this->size() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			values.push_back(iterator->next()->value);
		}
	}
	return values;
}

template <class Key, class Value>
Value Map<Key, Value>::find(Key key)
{
	node<Key, Value> *t = node_find(key);
	if (t == nullptr)
		return {};
	return t->value;
}

template<class Key, class Value>
size_t Map<Key, Value>::size(node<Key, Value> * p)
{
	if (p == nullptr) return 0;
	return size(p->left) + size(p->right) + 1;
}

template<class Key, class Value>
node<Key, Value>* Map<Key, Value>::successor(node<Key, Value> *p)
{
	node<Key, Value> *y;
	if (p->left != nullptr)
	{
		y = p->left;
		while (y->right != nullptr)
			y = y->right;
	}
	else
	{
		y = p->right;
		while (y->left != nullptr)
			y = y->left;
	}
	return y;
}

template <class Key, class Value>
void Map<Key, Value>::remove(Key key)
{
	if (root == nullptr)
	{
		return;
	}
	node<Key, Value> *p = root;
	node<Key, Value> *y;
	node<Key, Value> *q;
	bool found = false;
	while (p != nullptr && !found)
	{
		if (p->key == key)
			found = true;
		if (!found)
		{
			if (p->key < key)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (!found)
		return;
	if (p->left == nullptr || p->right == nullptr)
		y = p;
	else
		y = successor(p);
	if (y->left != nullptr)
		q = y->left;
	else
	{
		if (y->right != nullptr)
			q = y->right;
		else
			q = nullptr;
	}
	if (q != nullptr)
		q->father = y->father;
	if (y->father == nullptr)
		root = q;
	else
	{
		if (y == y->father->left)
			y->father->left = q;
		else
			y->father->right = q;
	}
	if (y != p)
	{
		p->color = y->color;
		p->key = y->key;
		p->value = y->value;
	}
	if (y->color == 0)
		delete_fix(q);
}

template <class Key, class Value>
void Map<Key, Value>::delete_fix(node<Key, Value> *p)
{
	if (p != nullptr)
	{
		node<Key, Value> *s;
		while (p != root && !p->color)
		{
			if (p->father->left == p)
			{
				s = p->father->right;
				if (s->color == 1)
				{
					s->color = 0;
					p->father->color = 1;
					rotate_left(p->father);
					s = p->father->right;
				}
				if (!s->right->color && !s->left->color)
				{
					s->color = 1;
					p = p->father;
				}
				else
				{
					if (!s->right->color)
					{
						s->left->color = 0;
						s->color = 1;
						rotate_right(s);
						s = p->father->right;
					}
					s->color = p->father->color;
					p->father->color = 0;
					s->right->color = 0;
					rotate_left(p->father);
					p = root;
				}
			}
			else
			{
				s = p->father->left;
				if (s->color)
				{
					s->color = 1;
					p->father->color = 1;
					rotate_right(p->father);
					s = p->father->left;
				}
				if (!s->left->color && !s->right->color)
				{
					s->color = 1;
					p = p->father;
				}
				else
				{
					if (!s->left->color)
					{
						s->right->color = 0;
						s->color = 1;
						rotate_left(s);
						s = p->father->left;
					}
					s->color = p->father->color;
					p->father->color = 0;
					s->left->color = 0;
					rotate_right(p->father);
					p = root;
				}
			}
			p->color = 0;
			root->color = 0;
		}
	}
}