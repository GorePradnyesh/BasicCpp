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
	const static char kOpenParan = '(';
	const static char kClosedParan = ')';
	const static char kAddOperator = '+';
	const static char kSubtractOperator = '-';
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
		multiplyOperator	= '*',
		divideOperator		= '/',
		nonOperator			= -1
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
		
		virtual std::uint64_t GetValue()
		{
			return 0;
		}
		
		virtual int GetPriority()
		{
			return -1;
		}
		
		virtual OperatorType GetOperatorType()
		{
			return OperatorType::nonOperator;
		}
	};
 
	class EndToken:public Token
	{
	public:
		TokenType GetTokenType() override
		{
			return TokenType::endTokenType;
		}
	};
	
	class OpenParanthesisToken:public Token
	{
	public:
		TokenType GetTokenType() override
		{
			return TokenType::openParanTokenType;
		}
	};
	
	
	class ClosedParanthesisToken:public Token
	{
	public:
		TokenType GetTokenType() override
		{
			return TokenType::closedParanTokenType;
		}
	};
	
	/*
	**	OPERAND
	*/
	class OperandToken:public Token
	{
	public:
		TokenType GetTokenType() override
		{
			return TokenType::operandTokenType;
		}
		
		OperandToken(std::uint64_t inTokenValue)
		:mOperandValue(inTokenValue)
		{}
		
		std::uint64_t GetValue() override
		{
			return mOperandValue;
		}
	private:
		std::uint64_t mOperandValue;
	};
	
	
	bool GetNumberFromString(const std::string& inExpression, std::string::const_iterator& stringIterator, std::uint64_t& outNumber);
	
	/*
	**	OPERATOR
	*/
	class OperatorToken:public Token
	{
	public:
		OperatorToken(char inOperatorValue)
		:mOperatorType(static_cast<OperatorType>(inOperatorValue))
		{
			// can use enum values for priority as well
			switch(mOperatorType)
			{
				case OperatorType::addOperator:
				case OperatorType::subtractOperator:
					mPriority = 1;
					break;
				case OperatorType::divideOperator:
				case OperatorType::multiplyOperator:
					mPriority = 2;
					break;
				case OperatorType::nonOperator:
					mPriority = -1;
				
			}
		}
		
		TokenType GetTokenType() override
		{
			return TokenType::operatorTokenType;
		}
		
		OperatorType GetOperatorType() override
		{
			return mOperatorType;
		}
		
		int GetPriority() override
		{
			return mPriority;
		}
	private:
		OperatorType	mOperatorType;
		int				mPriority;
	};
	
	
	bool IsValidOperator(char inChar);
	
	// Aliases
	using TokenURef		= std::unique_ptr<Token>;
	using OperandURef	= std::unique_ptr<OperandToken>;
	
}

#endif /* ExpressionEvaluator_hpp */
