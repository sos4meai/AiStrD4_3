#include "Huffman.h"
#include <iostream>
#include <iomanip>
#include <string>

void Huffman::buildTree(string input)
{

	fill_list(input);
	if (list.isEmpty())
		return;
	if (list.get_size() == 1) //only one symbol in string
	{
		list.at(0)->info->code = "0";
		root = list.at(0);
		return;
	}
	while (list.get_size() != 1)
	{
		size_t min1, min2, index_min1, index_min2;
		min1 = list.at(0)->info->frequency; // two min frequencies
		min2 = list.at(1)->info->frequency;
		index_min1 = 0; index_min2 = 1; // keep their index in list

		for (size_t i = 2; i < list.get_size(); i++) //find two symbols with min frequencies
		{
			size_t buff = list.at(i)->info->frequency;
			if (buff < min1)
			{
				min1 = buff;
				index_min1 = i;
			}
			else if (buff < min2)
			{
				min2 = buff;
				index_min2 = i;
			}
		}

		HuffNode* node = new HuffNode;
		FreqCode* info = new FreqCode(min1 + min2);
		node->info = info; //create new node with summ of frequencies
		node->left = list.at(index_min1); node->right = list.at(index_min2);
		list.push_back(node); // add new node in list
		if (index_min1 > index_min2) //remove from list two nodes, first delete - closest to tail
		{
			list.remove(index_min1); list.remove(index_min2);
		}
		else if (index_min1 < index_min2)
		{
			list.remove(index_min2); list.remove(index_min1);
		}
	}
	root = list.at(0);
}

void Huffman::fill_list(string input)
{
	size_t symbols[255]; for (size_t i = 0; i < 255; i++) symbols[i] = 0; // array of symbol's frequencies
	for (size_t i = 0; input[i] != '\0'; i++)
	{
		size_t buff = input[i];
		symbols[buff] += 1;
	}

	for (size_t i = 0; i < 255; i++)
		if (symbols[i] != 0) // add in list symbols with non-zero frequencies
		{
			HuffNode* node = new HuffNode;
			FreqCode* info = new FreqCode(symbols[i]); 
			node->symbol = i; node->info = info;
			list.push_back(node);
		}
}

void Huffman::codes(HuffNode * current)
{
	if (current == nullptr) // if Huffman tree isn't exist
		return;

	if (current->left == nullptr && current->right == nullptr) { // if it is a symbol
		data.insert(current->symbol, current->info);
		cout << current->symbol << ": " << current->info->frequency << "   " << current->info->code << endl;
		return;
	}

	if (current->left != nullptr) {
		current->left->info->code = current->info->code + "0";
		codes(current->left);
	}
	if (current->right != nullptr) {
		current->right->info->code = current->info->code + "1";
		codes(current->right);
	}
}

string Huffman::encode_string(string to_encode)
{
	buildTree(to_encode);
	codes(root);

	string encoded = "";
	for (size_t i = 0; to_encode[i] != '\0'; i++)
		encoded += data.findNode(to_encode[i])->value->code;
	return encoded;
}

string Huffman::decode_string(string to_decode)
{
	string decoded = "";
	if (root != nullptr)
	{
		for (size_t i = 0; to_decode[i] != '\0'; )
		{
			HuffNode* current = root;
			while (current->left != nullptr && current->right != nullptr)
			{
				if (to_decode[i] == '\0') //if not enough for symbol
					break;
				if (to_decode[i] == '0')
					current = current->left;
				else if (to_decode[i] == '1')
					current = current->right;
				i++;
			}
			if (current->left==nullptr && current->right==nullptr)
			 decoded += current->symbol;
			if (current == root)
				i++;
		}
	}
	return decoded;
}

void Huffman::print_info(string input, string encoded)
{
	double input_length, encoded_length;
	input_length = input.length() * 8;
	encoded_length = encoded.length();
	double compression = input_length / encoded_length;
	cout << "\nString length: " << input_length << ", encoded string length: " << encoded_length << "\nCompression: " << compression;
}
