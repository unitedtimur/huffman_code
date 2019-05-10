#include "Node.h"
#include <fstream>
#include "DynamycArray.h"

typedef unsigned int ui;

class Huffman
{
public:
	Huffman(const string& file_name = "");
	~Huffman();

	auto create(const string& file_name) -> void;

private:
	D_A <pair<char, int>> table;
	D_A<int> test;
	Node* root;
	string file_name;
	int size_of_text;
};

