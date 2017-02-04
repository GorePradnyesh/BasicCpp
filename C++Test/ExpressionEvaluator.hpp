//
//  ExpressionEvaluator.hpp
//  C++Test
//
//  Created by Pradnyesh Gore on 2/3/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef ExpressionEvaluator_hpp
#define ExpressionEvaluator_hpp

#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>

namespace ExpressionEvaluator
{
	void TestNumericEval();
	
	const static char kOpenParan = '(';
	const static char kClosedParan = ')';
	const static char kAddOperator = '+';
	const static char kSubtractOperator = '+';
	const static char kMultiplyOperator = '/';
	const static char kDivideOperator = '*';
	
	enum class TokenType
	{
		operatorTokenType		= 0,
		operandTokenType		= 1,
		openParanTokenType		= 2,
		closedParanTokenType	= 3,
		endTokenType			= 4
	};
	
	enum class OperatorType
	{
		addOperator			= '+',
		subtractOperator	= '-',
		multipleOperator	= '*',
		divideOperator		= '/'
	};
	
	/*
	** TOKEN
 	*/
	class Token
	{
	private:
		TokenType mTokentype;
	public:
		virtual TokenType GetTokenType()
		{
			return TokenType::endTokenType;
		}
	};
	
	using TokenURef = std::unique_ptr<Token>;
	
	class EndToken:public Token
	{
	public:
		TokenType GetTokenType()
		{
			return TokenType::operatorTokenType;
		}
	};
	
	class OpenParanthesisToken:public Token
	{
	public:
		TokenType GetTokenType()
		{
			return TokenType::openParanTokenType;
		}
	};
	
	
	class ClosedParanthesisToken:public Token
	{
	public:
		TokenType GetTokenType()
		{
			return TokenType::closedParanTokenType;
		}
	};

	
	/*
	**	OPERAND
	*/
	template <typename T>
	class OperandToken:public Token
	{
	public:
		TokenType GetTokenType()
		{
			return TokenType::operandTokenType;
		}
		
		OperandToken(T inTokenValue)
		:mOperandValue(inTokenValue)
		{}
		
		T GetValue()
		{
			return mOperandValue;
		}
	private:
		T mOperandValue;
	};
	
	
	template <typename T>
	bool GetNumberFromString(const std::string& inExpression, std::string::const_iterator& stringIterator, T& outNumber)
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
	
	/*
	**	OPERATOR
	*/
	class OperatorToken:public Token
	{
	public:
		OperatorToken(char inOperatorValue)
		:mOperatorType(static_cast<OperatorType>(inOperatorValue))
		{
			switch(mOperatorType)
			{
				case OperatorType::addOperator:
				case OperatorType::subtractOperator:
					mPriority = 1;
					break;
				case OperatorType::divideOperator:
				case OperatorType::multipleOperator:
					mPriority = 2;
			}
		}
		
		TokenType GetTokenType()
		{
			return TokenType::operatorTokenType;
		}
		
		OperatorType GetOperatorType()
		{
			return mOperatorType;
		}
	private:
		OperatorType	mOperatorType;
		int				mPriority;
	};
	
	
	bool IsValidOperator(char inChar);
	
	
	
}

#endif /* ExpressionEvaluator_hpp */
