#ifndef BTREE_H
#define BTREE_H

#include <memory>
#include <vector>

template <typename T,class allocator = std::allocator<T>>
class BTree
{
public:
	struct Node
	{
		Node* parent;
		std::vector<T> keys;
		std::vector<Node*> children;
	};

	BTree();
	~BTree();

	// ����ڵ�
	void insert(T& key);
	void insert(T&& key);

	// ɾ���ڵ�
	void remove(T& key);
	void remove(T&& key);

	// ���ҽڵ�
	Node* find(T& key);
	Node* find(T&& key);

	// �����ڵ�
	void traverse();

	// �����
	void clear();
	 
private:
};

#endif // BTREE_H