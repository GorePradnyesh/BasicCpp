//
//  SharedPointer.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 12/20/16.
//  Copyright © 2016 Adobe. All rights reserved.
//

#include "SharedPointer.h"
#include <memory>
#include <iostream>

namespace SharedPointerTest
{
	
	class InnerData
	{
	public:
		InnerData(int inData)
			:data(inData)
		{}
		
	private:
		int data;
	};
	
	class Wrapper
	{
	public:
		Wrapper(const InnerData& inInnerdata)
			:mInnerData(inInnerdata)
		{}
	private:
		InnerData mInnerData;
	};
}

void TestShared()
{
	using namespace SharedPointerTest;
	typedef std::shared_ptr<Wrapper> WrapperPtr;
	InnerData data(4);
	WrapperPtr wrapper1(new Wrapper(data));
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	
	WrapperPtr wrapper2 = wrapper1;
	std::cout << std::endl;
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	std::cout << "Use Count wrapper2 " << wrapper2.use_count() << std::endl;
	
	WrapperPtr wrapper3(wrapper1);
	std::cout << std::endl;
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	std::cout << "Use Count wrapper2 " << wrapper2.use_count() << std::endl;
	std::cout << "Use Count wrapper3 " << wrapper3.use_count() << std::endl;
	
	wrapper1.reset();
	std::cout << std::endl;
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	std::cout << "Use Count wrapper2 " << wrapper2.use_count() << std::endl;
	std::cout << "Use Count wrapper3 " << wrapper3.use_count() << std::endl;
	
}
