//
//  ExpressionParser.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef ExpressionParser_h
#define ExpressionParser_h

#include <stdio.h>
#include <string>

namespace ExpressionEvaluator
{
	bool DetectDoubleParans(const std::string& inExpression);
	uint64_t EvaluateExpression(const std::string& inExpression);
	bool DetectRedundantParans(const std::string& inExpression);
}

#endif /* ExpressionParser_h */
