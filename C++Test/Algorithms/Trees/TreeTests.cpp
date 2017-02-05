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
	void CreatePrintBinaryTreeFromVec(const std::vector<int>& dataSource)
	{
		Tree::NPtr<int> rootNode = Tree::ConstructBinaryTreeFromVec(dataSource);
		Tree::InOrderPrint(rootNode);
		PRINT_LINE("Max depth " << Tree::GetMaxDepth(rootNode));
	}
	
	void CreatePrintBinaryTree()
	{
		std::vector<int> dataSource = {12, 4, 8, 7, 2, 33, 14};
		CreatePrintBinaryTreeFromVec(dataSource);
		PRINT_LINE("===");
		dataSource = {2, 4, 7, 8, 12, 14, 33};
		CreatePrintBinaryTreeFromVec(dataSource);
		PRINT_LINE("===");
		dataSource = {33, 14, 12, 8, 7, 4, 2};
		CreatePrintBinaryTreeFromVec(dataSource);
		PRINT_LINE("===");
	}
}
