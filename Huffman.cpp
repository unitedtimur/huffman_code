#include "Huffman.h"

Huffman::Huffman(const string& file_name) :
	root(nullptr),
	size_of_text(0)
{
	create(file_name);
}

Huffman::~Huffman()
{
}

auto Huffman::create(const string& file_name) -> void
{
	this->file_name = file_name;

	ifstream is(this->file_name);

	if (is.is_open())
	{
		char ch;

		is >> ch;

		for(;!is.eof();)
		{
			auto index = table.find(ch);

			if (index != -1)
			{
				table[index].second++;
			}
			else
			{
				table.push_back({ ch, 1 });
			}

		}
	}
}
