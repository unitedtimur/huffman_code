#include "Node.h"

Node::Node(const std::string& str, const ui& count, Node* left, Node* right, Node* next):
	set(str.c_str()),
	count(count),
	left(left),
	right(right),
	next(next)
{
}

Node::Node(const Node& node)
{
	if (this != &node)
	{
		set = node.set;
		count = node.count;
		left = node.left;
		right = node.right;
		next = node.right;
	}
}

