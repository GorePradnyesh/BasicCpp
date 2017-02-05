//
//  TreeUtils.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#include "Tree.h"
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
			InOrderWalk(inNode->Left());
			PRINT_LINE(inNode->GetData());
			InOrderWalk(inNode->Right());
		}
	}
	
	/*
	**
	*/
	template <typename T>
	void ConstructBinaryTreeFromVec(const std::vector<T>& inSourceData)
	{
		// using NodePtr = std::shared_ptr<Node<T>>;
		auto currentIt = inSourceData.begin();
		NPtr<T> rootNode;
		while(currentIt != inSourceData.end())
		{
			addNode(rootNode, *currentIt);
			currentIt++;
		};
	}
	
	
	/*
	**
	*/
	template <typename T>
	void addNode(NPtr<T>& inNode, const T& inDataValue)
	{
		if(!inNode)
		{
			inNode = NPtr<T>(new Node<T>(inDataValue));
		}
		else if(inDataValue > inNode->GetValue())
		{
			addNode(inNode->Left(), inDataValue);
		}
		else
		{
			addNode(inNode->Right(), inDataValue);
		}
	}
	
}

#endif /* TreeUtils_h */
