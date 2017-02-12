//
//  BinaryOperations.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/11/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef BinaryOperations_h
#define BinaryOperations_h

#include "CommonUtils.h"

#include <string>
#include <sstream>

namespace BinaryOperations
{
	void GetBinaryFromDecimal(std::uint64_t inNumber, std::string& outString)
	{
		std::stringstream outStream("");
		std::uint64_t remainder = inNumber;
		if(0 == inNumber)
		{
			outString = "0";
			return;
		}
		while(remainder != 1)
		{
			std::uint64_t modulo = remainder % 2;
			remainder = remainder/2;
			outStream << modulo;
		}
		outStream << 1;
		outStream >> outString;
		std::reverse(outString.begin(), outString.end());
	}
	
	void GetDecimalFromBinary(const std::string& inString, std::uint64_t& outDecimal)
	{
		int index = 0;
		for(auto rIter = inString.rbegin(); rIter != inString.rend(); ++rIter)
		{
			const char bitChar = *rIter;
			if('1' == bitChar)
			{
				outDecimal += 1 << index;
			}
			index++;
		}
	}
	

	void TestDecimalToBinary()
	{
		std::uint64_t num = 8;
		std::string outString;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
		
		num = 12;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
		
		num = 0;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
		
		num = 1;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
		
		num = 65535;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
		
		num = 1048576;
		GetBinaryFromDecimal(num, outString);
		PRINT_LINE(num << " in Binary: " << outString);
	}
	
	
	void TestBinaryToDecimal()
	{
		std::string binary = "101";
		std::uint64_t decimal;
		GetDecimalFromBinary(binary, decimal);
		PRINT_LINE("Binary : " << binary << " Decimal : " << decimal);
		
		binary = "101";
		decimal = 0;
		GetDecimalFromBinary(binary, decimal);
		PRINT_LINE("Binary : " << binary << " Decimal : " << decimal);
		
		binary = "1111111111111111";
		decimal = 0;
		GetDecimalFromBinary(binary, decimal);
		PRINT_LINE("Binary : " << binary << " Decimal : " << decimal);
		
		binary = "00000000000";
		decimal = 0;
		GetDecimalFromBinary(binary, decimal);
		PRINT_LINE("Binary : " << binary << " Decimal : " << decimal);
		
		binary = "100000000000000000000";
		decimal = 0;
		GetDecimalFromBinary(binary, decimal);
		PRINT_LINE("Binary : " << binary << " Decimal : " << decimal);
	}
	
	void TestBinaryAddition()
	{
		uint64_t op1 = 4;
		uint64_t op2 = 6;
		std::string binaryOp1;
		std::string binaryOp2;
		GetBinaryFromDecimal(op1, binaryOp1);
		GetBinaryFromDecimal(op2, binaryOp2);
		PRINT_LINE("Addition : " << (op1 | op2));
	}
	
}


#endif /* BinaryOperations_h */
