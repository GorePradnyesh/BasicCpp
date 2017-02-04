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
#include <assert.h>
#include <ctype.h>

namespace ExpressionEvaluator
{
	/*
	**
	*/
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
				return TokenURef(new OperandToken(currentOperand));
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
	
	bool GetNumberFromString(const std::string& inExpression, std::string::const_iterator& stringIterator, std::uint64_t& outNumber)
	{
		std::stringstream outStringStream("");
		bool foundNumber = false;
		if(stringIterator == inExpression.end())
		{
			return false;
		}
		while(true)
		{
			if(isdigit(*stringIterator))
			{
				foundNumber = true;
				outStringStream << *stringIterator;
				++stringIterator;
			}
			else
			{
				break;
			}
		}
		// if nothing was parsed return
		if(!foundNumber)
		{
			return false;
		}
		outStringStream >> outNumber;
		return true;
	}
	
	bool IsValidOperator(char inChar)
	{
		if(kAddOperator == inChar || kDivideOperator == inChar || kMultiplyOperator == inChar || kSubtractOperator == inChar)
		{
			return true;
		}
		return false;
	}
	
	
	uint64_t EvaluateOperator(OperatorType inOperator, uint64_t inLHSOperator, uint64_t inRHSOperator)
	{
		switch (inOperator)
		{
			case OperatorType::addOperator:
				return inLHSOperator + inRHSOperator;
			case OperatorType::subtractOperator:
				return inLHSOperator - inRHSOperator;
			case OperatorType::multiplyOperator:
				return inLHSOperator * inRHSOperator;
			case OperatorType::divideOperator:
				return inLHSOperator / inRHSOperator;
			case OperatorType::nonOperator:
			default:
				return 0;
		}
	}
	
	uint64_t EvaluateExpression(const std::string& inExpression)
	{
		std::stack<std::uint64_t> 	OperandStack;
		std::stack<TokenURef>		OperatorStack;
		
		auto beginIt = inExpression.begin();
		TokenURef receivedToken;
		
		// While either stack has something remaining
		while(!(OperatorStack.empty() && OperatorStack.empty()))
		{
			receivedToken = std::move(GetNextToken(beginIt, inExpression));
			// PRINT_LINE("TOKEN RECEIVED :" << static_cast<int>(receivedToken->GetTokenType()));
			auto EvaluateAndPush = [&OperandStack, &OperatorStack]()
			{
				std::uint64_t rhsValue = OperandStack.top();
				OperandStack.pop();
				std::uint64_t lhsValue = OperandStack.top();
				OperandStack.pop();
				TokenURef& operatorToken = OperatorStack.top();
				assert(OperatorType::nonOperator != operatorToken->GetOperatorType());
				uint64_t result = EvaluateOperator(operatorToken->GetOperatorType(), lhsValue, rhsValue);
				OperandStack.push(result);
			};
			
			switch (receivedToken->GetTokenType())
			{
				case TokenType::openParanTokenType:
					OperatorStack.push(std::move(receivedToken));
					break;
				case TokenType::operandTokenType:
					{
						OperandStack.push(receivedToken->GetValue());
						break;
					}
				case TokenType::operatorTokenType:
					{
						TokenURef& topToken = OperatorStack.top();
						while(topToken->GetPriority() > receivedToken->GetPriority())
						{
							// evaluate and push, update topToken
							EvaluateAndPush();
						}
						OperatorStack.push(std::move(receivedToken));
					}
					break;
				case TokenType::closedParanTokenType:
					{
						while(true)
						{
							EvaluateAndPush();
							TokenURef& nextToken = OperatorStack.top();
							// If while evaluing, encounter a (, pop it and stop evaluating
							if(TokenType::openParanTokenType == nextToken->GetTokenType())
							{
								OperatorStack.pop();
								break;
							}
						}
					}
					break;
				case TokenType::endTokenType:
					if(!OperatorStack.empty())
					{
						EvaluateAndPush();
					}
					if(!OperandStack.empty())
					{
						assert(OperandStack.size() == 1);
						return OperandStack.top();
					}
					break;
			}
		}
		assert("Control should not reach this");
		return 1;
	}
	
	
	void TestNumericEval()
	{
		std::string input = "(11+33)";
		EvaluateExpression(input);
	}
}
