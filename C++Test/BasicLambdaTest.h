//
//  BasicLambdaTest.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/2/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef BasicLambdaTest_h
#define BasicLambdaTest_h

namespace BasicLambda
{
	
	namespace
	{
		class TestData
		{
		public:
			TestData(double inData);
			
			inline double GetData() const
			{
				return mData;
			}
			
		private:
			double mData;
		};
		
			TestData::TestData(double inData):
		mData(inData){}
	
	
		auto Doubler =
			[](int inValue) -> int
			{
				return inValue * 2;
			};
		
	}
	
	std::function<int(int)> DoublerFunction = [](int inValue){ return inValue * 2; };
	
	void InvokeBasicLambda()
	{
		PRINT_LINE(Doubler(4));
		PRINT_LINE(DoublerFunction(4));
		PRINT_LINE("Size of auto " << sizeof(Doubler));
		PRINT_LINE("Size of std::function " << sizeof(DoublerFunction));
	}
	
	
	void CapturedLambdaTest()
	{
		TestData d1(3.0);
		auto CapturedMultiplier = [d1](double inValue) -> double
			{
				return inValue * d1.GetData();
			};
		PRINT_LINE("Size of TestData: " << sizeof(d1));
		PRINT_LINE("Size of capture multiplier: " << sizeof(CapturedMultiplier));
		PRINT_LINE(CapturedMultiplier(4.0));
		
		std::function<double(double)> CapturedMultiplierFunction = [d1](double inValue) -> double{ return inValue * d1.GetData(); };
		PRINT_LINE("Size of TestData Function: " << sizeof(CapturedMultiplierFunction));
	}
}
#endif /* BasicLambdaTest_h */
