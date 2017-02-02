//
//  CommonTestClasses.h
//  C++Test
//
//  Created by Pradnyesh Gore on 1/26/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef CommonTestClasses_h
#define CommonTestClasses_h
// public namespace
// InnerData class
class InnerData
{
public:
	InnerData(int inData)
	:data(inData)
	{}
	
private:
	int data;
};

// Wrapper Class
class Wrapper
{
public:
	Wrapper(const InnerData& inInnerdata)
	:mInnerData(inInnerdata)
	{}
private:
	InnerData mInnerData;
};


#endif /* CommonTestClasses_h */
