//
//  ExpressionParseTest.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#include "ExpressionParseTest.h"
#include "ExpressionParser.h"
#include "CommonUtils.h"

#include <string>

namespace ExpressionEvaluator
{
	void TestNumericEval()
	{
		std::string input = "(1+3*4)";
		std::uint64_t result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(1*3+4)";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "1*3";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(1*3+4)";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(1)";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "11";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(40/2*4)";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(40/(2*4))";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
		
		input = "(40*2/4)";
		result = EvaluateExpression(input);
		PRINT_LINE(input << " RESULT = " << result);
	}
	
	void TestDuplicateParanthesis()
	{
		std::string input = "(1+3)";
		PRINT_LINE(input << " DUPLICATE " << ExpressionEvaluator::DetectDoubleParans(input));
		
		input = "((1+3))";
		PRINT_LINE(input << " DUPLICATE " << ExpressionEvaluator::DetectDoubleParans(input));
		
		input = "((1+3)*6)";
		PRINT_LINE(input << " DUPLICATE " << ExpressionEvaluator::DetectDoubleParans(input));
		
		input = "(((1+3)*6))";
		PRINT_LINE(input << " DUPLICATE " << ExpressionEvaluator::DetectDoubleParans(input));
		
		input = "(((1+3))*6)";
		PRINT_LINE(input << " DUPLICATE " << ExpressionEvaluator::DetectDoubleParans(input));
	}
	
	void TestRedundantParanthesis()
	{
		std::string input = "(1+3)";
		PRINT_LINE(input << " REDUNDANT " << ExpressionEvaluator::DetectRedundantParans(input));
		
		input = "((1+3))";
		PRINT_LINE(input << " REDUNDANT " << ExpressionEvaluator::DetectRedundantParans(input));
		
		input = "((1+3)*6)";
		PRINT_LINE(input << " REDUNDANT " << ExpressionEvaluator::DetectRedundantParans(input));
		
		input = "((1+3)+6)";
		PRINT_LINE(input << " REDUNDANT " << ExpressionEvaluator::DetectRedundantParans(input));
	}
	
}
