//
//  main.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 6/15/16.
//  Copyright © 2016 Adobe. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "SharedPointer.h"
#include "ScopedDelete.h"
#include "AssignmentTester.h"
#include "Rational.h"
#include "BasicLambdaTest.h"
#include "ExpressionParseTest.h"

#include "TreeTests.h"

#define PRINTLINE(line) \
	std::cout << line << std::endl


void printExecutionOptions()
{
	PRINTLINE("");
	PRINTLINE("-- CHOOSE OPTIONS --");
	PRINTLINE("0 : Exit");
	PRINTLINE("1 : Test Shared Pointer");
	PRINTLINE("2 : Test Scoped Delete");
	PRINTLINE("3 : Test Assignment operator");
	PRINTLINE("4 : Rvalue assignment/ctor");
	PRINTLINE("5 : RationalNumber");
	PRINTLINE("6 : BasicLambda");
	std::cout << "option : ";
}


/*
 **
 */
int main(int argc, const char * argv[])
{
	while(true)
	{
		printExecutionOptions();
		int argIndex = 0;
		if(!(std::cin >> argIndex))
		{
			std::cout << "Invalid argument." << std::endl;
			return -1;
		}
		
		switch(argIndex)
		{
			case 0:
				return 0;
			case 1:
				TestShared();
				break;
			case 2:
				ScopedDelete::TestScopedDelete();
				break;
			case 3:
				AssignmentTester::TestAssignment();
				break;
			case 4:
				TestRValueRefs();
				break;
			case 5:
				Rational::RationalTest();
				break;
			case 6:
				BasicLambda::InvokeBasicLambda();
				break;
			case 7:
				BasicLambda::CapturedLambdaTest();
				break;
			case 8:
				ExpressionEvaluator::TestNumericEval();
				break;
			case 9:
				ExpressionEvaluator::TestDuplicateParanthesis();
				break;
			case 10:
				TreeTest::CreatePrintBinaryTree();
				break;
			default:
				std::cout << "Invalid argument." << std::endl;
				return -1;
		}
	}

    return 0;
}
