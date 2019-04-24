#include "stdafx.h"
#include "CppUnitTest.h"
#include"../Huffman/Huffman.h"
#include "../Huffman/Huffman.cpp"
#include <string.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Разместите здесь код своего теста
		}

		TEST_METHOD(encode_1_symbol_in_string)
		{
			Huffman alg;
			std::string expected = "000";
			Assert::AreEqual(expected, alg.encode_string("!!!"));
		}

		TEST_METHOD(encode_2_symbols_in_string)
		{
			Huffman alg;
			std::string expected = "000111";
			Assert::AreEqual(expected, alg.encode_string("aaabbb"));
		}

		TEST_METHOD(encode_quote)
		{
			Huffman alg;
			std::string expected = "0101111100111001110000010110111001110000111111011110101110100111000011011100010000011101111110100010010110000001010101001011111011101111101100000000011001010001100101111101110111110110000000001100010110110110100100100111001010100111100010110111000011011100000111111101001001110001111011110101101010";
			Assert::AreEqual(expected, alg.encode_string("Success consists of going from failure to failure without loss of enthusiasm"));
		}

		TEST_METHOD(encode_3_symbols_with_same_frequency)
		{
			Huffman alg;
			std::string expected = "111111101010000";
			Assert::AreEqual(expected, alg.encode_string("***)))TTT"));
		}
		
		TEST_METHOD(encode_empty_string)
		{
			Huffman alg;
			std::string expected = "";
			Assert::AreEqual(expected, alg.encode_string(""));
		}


		TEST_METHOD(decode_1_symbol_in_string)
		{
			Huffman alg;
			std::string to_encode = "!!!";
			Assert::AreEqual(alg.decode_string(alg.encode_string(to_encode)), to_encode);
		}

		TEST_METHOD(decode_2_symbols_in_string)
		{
			Huffman alg;
			std::string to_encode = "@@@???";
			Assert::AreEqual(alg.decode_string(alg.encode_string(to_encode)), to_encode);
		}

		TEST_METHOD(decode_quote)
		{
			Huffman alg;
			std::string to_encode = "Success consists of going from failure to failure without loss of enthusiasm";
			Assert::AreEqual(alg.decode_string(alg.encode_string(to_encode)), to_encode);
		}

		TEST_METHOD(decode_3_symbols_with_same_frequency)
		{
			Huffman alg;
			std::string to_encode = "***)))TTT";
			Assert::AreEqual(alg.decode_string(alg.encode_string(to_encode)), to_encode);
		}

		TEST_METHOD(decode_empty_string)
		{
			Huffman alg;
			std::string to_encode = "";
			Assert::AreEqual(alg.decode_string(alg.encode_string(to_encode)), to_encode);
		}

		TEST_METHOD(decode_random_word)
		{
			Huffman alg;
			alg.encode_string("It is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change");
			std::string expected_decode = "useless";
			Assert::AreEqual(expected_decode, alg.decode_string("111011111101111100001111111111"));
		}
		
		TEST_METHOD(decode_random_word_not_enough_for_the_last)
		{
			Huffman alg;
			alg.encode_string("It is not the strongest of the species that survives, nor the most intelligent, but the one most responsive to change");
			std::string expected_decode = "useles";
			Assert::AreEqual(expected_decode, alg.decode_string("11101111110111110000111111111"));
		}
	};
}