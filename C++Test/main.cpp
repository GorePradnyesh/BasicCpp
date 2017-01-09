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
			default:
				std::cout << "Invalid argument." << std::endl;
				return -1;
		}
	
	}

    return 0;
}
