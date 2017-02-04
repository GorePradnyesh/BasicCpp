//
//  ExpressionEvaluator.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 2/3/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#include "ExpressionEvaluator.hpp"
#include "CommonUtils.h"

#include <stack>
#include <string>
#include <sstream>

#include <ctype.h>

namespace ExpressionEvaluator
{
	
	
	
	TokenURef GetNextToken(std::string::const_iterator& inCurrentIterator, std::string inString)
	{
		if(inCurrentIterator == inString.end())
		{
			return TokenURef(new EndToken());
		}
		else
		{
			char currentChar = *inCurrentIterator;
			if(isdigit(currentChar))
			{
				uint64_t currentOperand;
				GetNumberFromString(inString, inCurrentIterator, currentOperand);
				// iterater already advanced
				return TokenURef(new OperandToken<uint64_t>(currentOperand));
			}
			else if(IsValidOperator(currentChar))
			{
				++inCurrentIterator;
				return TokenURef(new OperatorToken(currentChar));
			}
			else if(kOpenParan == currentChar)
			{
				++inCurrentIterator;
				return TokenURef(new OpenParanthesisToken());
			}
			else if(kClosedParan == currentChar)
			{
				++inCurrentIterator;
				return TokenURef(new ClosedParanthesisToken());
			}
			else
			{
				return TokenURef(new EndToken());
			}
		}
	}
	
	bool IsValidOperator(char inChar)
	{
		if(kAddOperator == inChar || kDivideOperator == inChar || kMultiplyOperator == inChar || kSubtractOperator == inChar)
		{
			return true;
		}
		return false;
	}
	
	void EvaluateExpression(const std::string& inExpression)
	{
		std::stack<int> 	OperandStack;
		std::stack<char>	OperatorStack;
	
		auto beginIt = inExpression.begin();
		TokenURef receivedToken;
		while(beginIt != inExpression.end())
		{
			receivedToken = std::move(GetNextToken(beginIt, inExpression));
			PRINT_LINE("TOKEN RECEIVED :" << static_cast<int>(receivedToken->GetTokenType()));
		}
		
	}
	
	
	void TestNumericEval()
	{
		std::string input = "(11+33)";
		EvaluateExpression(input);
	}
}
