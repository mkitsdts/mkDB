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

	// 插入节点
	void insert(T& key);
	void insert(T&& key);

	// 删除节点
	void remove(T& key);
	void remove(T&& key);

	// 查找节点
	Node* find(T& key);
	Node* find(T&& key);

	// 遍历节点
	void traverse();

	// 清空树
	void clear();
	 
private:
};

#endif // BTREE_H