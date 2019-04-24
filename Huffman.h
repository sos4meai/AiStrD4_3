#pragma once
#include "../Sem4_Lab1/List.h"
#include "../AiStrD_4.2/Map.h"
#include "../AiStrD_4.2/Map.cpp"

struct FreqCode
{
	size_t frequency;
	string code;

	FreqCode(size_t frequency = 0)
	{
		this->frequency = frequency;
		code = "";
	};

};

class Huffman;

class HuffNode
{
	char symbol;
	FreqCode* info;

	HuffNode* left;
	HuffNode* right;

	friend Huffman;

public:
	HuffNode(FreqCode* info = nullptr)
	{
		this->info = info;
		left = nullptr;
		right = nullptr;
	};
};

class Huffman
{
	HuffNode* root;
	List<HuffNode*> list;
	Map<char, FreqCode*> data;
	void buildTree(string input); //creates Huffman's tree
	void fill_list(string input); //creates HuffNodes and count frequency
	void codes(HuffNode* current); //encodes symbols

	void clearTree(HuffNode* current)
	{
		if (current != nullptr)
		{
			if (current->right != nullptr) clearTree(current->right);
			if (current->left != nullptr) clearTree(current->left);
			delete current->info;
			delete current;
		}
	}

public:

	string encode_string(string to_encode); // encode symbols and string
	string decode_string(string to_decode); // only with not empty tree
	void print_info(string input, string encoded); //frequency and code table, aspect ratio

	Huffman()
	{
		root = nullptr;
	};
	~Huffman()
	{
		data.~Map();
		clearTree(root);
		root = nullptr;
	};
};