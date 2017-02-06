//
//  CommonUtils.h
//  C++Test
//
//  Created by Pradnyesh Gore on 1/24/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef CommonUtils_h
#define CommonUtils_h

#include <iostream>
#include <vector>

#define PRINT_LINE(line) (std::cout << line << std::endl)
#define PRINT_STRING(string) (std::cout << string)


template <typename T>
void PrintVector(const std::vector<T> inVector)
{
	for(auto element: inVector)
	{
		PRINT_STRING(element);PRINT_STRING(", ");
	}
}

#endif /* CommonUtils_h */
