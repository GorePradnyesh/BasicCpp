//
//  Header.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/4/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include <memory>
namespace Tree
{
	template <typename T>
	class Node
	{
	public:
		Node(const T& inData)
		:mData(new T(inData))
		{}
	
		inline std::shared_ptr<Node<T>>& Left()
		{
			return mLeft;
		}

		inline std::shared_ptr<Node<T>>& Right()
		{
			return mRight;
		}
		
		inline bool isEmpty()
		{
			if(mData)
			{
				return true;
			}
			return false;
		}
		
		inline std::shared_ptr<T> GetData()
		{
			return mData;
		}
		
		T GetValue()
		{
			return *mData.get();
		}
		
		void SetLeft(const std::shared_ptr<Node>& inNode)
		{
			mLeft = inNode;
		}
		
		void SetRight(const std::shared_ptr<Node>& inNode)
		{
			mRight = inNode;
		}
		
	private:
		std::shared_ptr<T> mData;
		std::shared_ptr<Node<T>> mLeft;
		std::shared_ptr<Node<T>> mRight;
	};
	
	// Templatised alias
	template <typename T>
	using NPtr = std::shared_ptr<Node<T>>;
	
	
}

#endif /* Header_h */
