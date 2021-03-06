#include "BSTree.h"
#include <initializer_list>

template <typename T>
Node<T>* BSTree<T>::next(Node<T>* node) const
{
	if (node->right != nullptr)
	{
		return min(node->right);
	}
	Node<T>* pos = node->parent;
	while (pos != nullptr && node == pos->right)
	{
		node = pos;
		pos = pos->parent;
	}
	return pos;
}
template <typename T>
Node<T>* BSTree<T>::prev(Node<T>* node) const
{
	if (node->left != nullptr)
	{
		return max(node->left);
	}
	Node<T>* pos = node->parent;
	while (pos != nullptr && node == pos->left)
	{
		node = pos;
		pos = pos->parent;
	}
	return pos;
}
template <typename T>
Node<T>* BSTree<T>::max(Node<T>* node) const
{
	if (node->right == nullptr)
	{
		return node;
	}
	return max(node->right);
}
template <typename T>
Node<T>* BSTree<T>::min(Node<T>* node) const
{
	if (node->left == nullptr)
	{
		return node;
	}
	return min(node->left);
}
template <typename T>
BSTree<T>::BSTree(const std::initializer_list<T> &list)
{
	root = nullptr;
	for (auto i : list)
	{
		this->insert(i);
	}
}
template <typename T>
void BSTree<T>::insert(const T &k)
{
	if (root == nullptr)
	{
		root = new Node<T>(k);
		root->parent = nullptr;
		this->_size += 1;
	}
	else
	{
		Node<T>* p = root;
		Node<T>* prev = nullptr;
		while (p != nullptr)
		{
			prev = p;
			if (p->key > k)
			{
				p = p->left;
			}
			else
			{
				p = p->right;
			}
		}
		if (search(k) != nullptr)
		{
			//	throw "copy key";
		}
		else
		{
			this->_size += 1;
			if (prev->key > k)
			{
				prev->left = new Node<T>(k);
				prev->left->parent = prev;
			}
			else
			{
				prev->right = new Node<T>(k);
				prev->right->parent = prev;
			}
		}
	}
}
template <typename T>
Node<T>* BSTree<T>::search(const T &k) const
{
	if (root == nullptr)
	{
		throw EmptyException();
	}
	else
	{
		Node<T>* node = root;
		search(node, k);
	}
}
template <typename T>
Node<T>* BSTree<T>::search(Node<T>* node, const T &k) const
{
	if (node->key == k)
	{
		return node;
	}
	else if (node->key > k)
	{
		if (node->left != nullptr)
		{
			return search(node->left, k);
		}
		else
		{
			return nullptr;
		}
	}
	else
	{
		if (node->right != nullptr)
		{
			return search(node->right, k);
		}
		else
		{
			return nullptr;
		}
	}
}
template <typename T>
void BSTree<T>::remove(const T &k)
{
	if (root == nullptr)
	{
		throw EmptyException();
	}
	else if (search(k) == nullptr)
	{
		//throw "Empty";
	}
	else
	{
		Node<T>* node = search(k);
		if (node->left == nullptr && node->right == nullptr)
		{
			if (node->parent != nullptr)
			{
				if (node->parent->left == node)
				{
					node->parent->left = nullptr;
				}
				else
				{
					node->parent->right = nullptr;
				}
			}
			this->_size -= 1;
			delete node;
		}
		else if (node->left == nullptr || node->right == nullptr)
		{
			if (node->parent != nullptr)
			{
				if (node->left == nullptr)
				{
					if (node->parent->left == node)
					{
						node->parent->left = node->right;
					}
					else
					{
						node->parent->right = node->right;
					}
					node->right->parent = node->parent;
				}
				else
				{
					if (node->parent->left == node)
					{
						node->parent->left = node->left;
					}
					else
					{
						node->parent->right = node->left;
					}
					node->left->parent = node->parent;
				}
				this->_size -= 1;
				delete node;
			}
			else
			{
				if (node->left == nullptr)
				{
					root = node->right;
					node->right->parent = nullptr;
				}
				else
				{
					root = node->left;
					node->left->parent = nullptr;
				}
				this->_size -= 1;
				delete node;
			}
		}
		else
		{
			Node<T>* pos = next(node);
			node->key = pos->key;
			if (pos->parent->left == pos)
			{
				pos->parent->left = pos->right;
				if (pos->right != nullptr)
				{
					pos->right->parent = pos->parent;
				}
			}
			else
			{
				pos->parent->right = pos->right;
				if (pos->right != nullptr)
				{
					pos->right->parent = pos->parent;
				}
			}
			this->_size -= 1;
			delete pos;
		}
	}
}
template <typename T>
void BSTree<T>::deletetree(const T &k)
{
	if (root == nullptr)
	{
		throw EmptyException();
	}
	else if (search(k) == nullptr)
	{
		//throw "Empty";
	}
	else
	{
		Node<T>* node = search(k);
		if (node->left != nullptr)
		{
			remove(node->left->key);
		}
		if (node->right != nullptr)
		{
			remove(node->right->key);
		}
		if (node->parent != nullptr)
		{
			if (node->parent->left == node)
			{
				node->parent->left = nullptr;
			}
			else
			{
				node->parent->right = nullptr;
			}
		}
		this->_size -= 1;
		delete node;
	}
}
template <typename T>
void BSTree<T>::printBSTree(std::ostream &os/* = std::cout*/) const
{
	if (root == nullptr)
	{
		throw EmptyException();
	}
	else
	{
		Node<T>* node = root;
		{
			printBSTree(node, os);
		}
	}
}
template <typename T>
void BSTree<T>::printBSTree(Node<T>* node, std::ostream &os) const
{
	if (node->left != nullptr)
	{
		printBSTree(node->left, os);
	}
	os << node->key << " ";
	if (node->right != nullptr)
	{
		printBSTree(node->right, os);
	}
}
template <typename T>
std::ostream & operator << (std::ostream &os, BSTree<T> &out)
{
	out.printBSTree(os);
	return os;
}
template <typename T>
std::istream & operator >> (std::istream &input, BSTree<T> &in)
{
	unsigned int n;
	if (!(input >> n))
	{
		throw InputException();
	}
	T temp;
	for (unsigned int i = 0; i < n; ++i)
	{
		if (input >> temp)
		{
			in.insert(temp);
		}
		else
		{
			throw InputException();
		}
	}
	return input;
}
template <typename T>
std::fstream & operator << (std::fstream &file, BSTree<T> &out)
{
	file << out.size() << " ";
	out.printBSTree(file);
	return file;
}
template <typename T>
std::fstream & operator >> (std::fstream &file, BSTree<T> &in)
{
	unsigned int n;
	if (!(file >> n))
	{
		throw InputException();
	}
	T temp;
	for (unsigned int i = 0; i < n; ++i)
	{
		if (file >> temp)
		{
			in.insert(temp);
		}
		else
		{
			throw InputFileException();
		}
	}
	return file;
}
