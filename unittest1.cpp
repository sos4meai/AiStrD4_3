#include "stdafx.h"
#include "CppUnitTest.h"
#include "../AiStrD4_3/Huffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HuffmanTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(encode_string_one_symbol)
		{
			Huffman alg;
			string encoded = alg.encode_string("777777");
			string expected = "000000";
			Assert::IsTrue(encoded == expected);
		}

	};
}