//
//  TreeTests.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#include "TreeTests.h"
#include "TreeUtils.h"

#include <vector>

namespace TreeTest
{
	void CreatePrintBinaryTree()
	{
		std::vector<int> dataSource = {12};
		Tree::ConstructBinaryTreeFromVec(dataSource);
	}
}
