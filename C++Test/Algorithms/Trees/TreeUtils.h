//
//  TreeUtils.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#include "Tree.h"
#include "CommonUtils.h"

#include <vector>
#ifndef TreeUtils_h
#define TreeUtils_h

namespace Tree
{
	/*
	**
	*/
	template <typename T>
	void InOrderPrint(const NPtr<T>& inNode)
	{
		if(!inNode)
		{
			return;
		}
		else
		{
			InOrderPrint(inNode->Left());
			PRINT_LINE(inNode->GetValue() << ", ");
			InOrderPrint(inNode->Right());
		}
	}
	
	/*
	**
	*/
	template <typename T>
	NPtr<T> ConstructBinaryTreeFromVec(const std::vector<T>& inSourceData)
	{
		// using NodePtr = std::shared_ptr<Node<T>>;
		auto currentIt = inSourceData.begin();
		NPtr<T> rootNode;
		while(currentIt != inSourceData.end())
		{
			addBinaryNode(rootNode, *currentIt);
			currentIt++;
		};
		return rootNode;
	}
	
	
	/*
	**
	*/
	template <typename T>
	void addBinaryNode(NPtr<T>& inNode, const T& inDataValue)
	{
		if(!inNode)
		{
			inNode = NPtr<T>(new Node<T>(inDataValue));
		}
		else if(inDataValue < inNode->GetValue())
		{
			addBinaryNode(inNode->Left(), inDataValue);
		}
		else
		{
			addBinaryNode(inNode->Right(), inDataValue);
		}
	}
	
	/*
	**
	*/
	template <typename T>
	int GetMaxDepth(const NPtr<T>& inNode)
	{
		if(!inNode)
		{
			return 0;
		}
		int leftDepth = GetMaxDepth(inNode->Left());
		int rightDepth = GetMaxDepth(inNode->Right());
		return std::max(leftDepth, rightDepth) + 1;
	}
	
}

#endif /* TreeUtils_h */
