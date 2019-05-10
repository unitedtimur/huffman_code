#include <string>
#include "Plurality.h"

typedef unsigned int ui;

class Node
{
public:
	explicit Node(const std::string& str, const ui& count = 0, Node* left = nullptr, Node* right = nullptr, Node* next = nullptr);
	Node(const Node& node);
private:
	Node* left,
		* right,
		* next;
	plurality set;
	friend class Huffman;
	ui count;
};

