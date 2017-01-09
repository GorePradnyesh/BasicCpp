//
//  AssignmentTesterClass.h
//  C++Test
//
//  Created by Pradnyesh Gore on 1/9/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef AssignmentTesterClass_h
#define AssignmentTesterClass_h


namespace AssignmentTester
{
	namespace
	{
		class AssignmentTester
		{
		public:
			AssignmentTester(int inData)
			{
				mIntData = inData;
			}
			
			AssignmentTester& operator=(const AssignmentTester& inAssignmentTester)
			{
				mIntData = inAssignmentTester.mIntData;
				return *this;
			}
			
			void SetData(int inData)
			{
				mIntData = inData;
			}
			
			int GetData()
			{
				return mIntData;
			}
			
		private:
			int mIntData;
		};
	}
	
	void TestAssignment()
	{
		AssignmentTester instance1(10);
		AssignmentTester instance2(20);
		AssignmentTester instance3(30);
		instance3 = instance2 = instance1;
		
		std::cout << instance1.GetData() << ", " << instance2.GetData() << ", " << instance3.GetData() << std::endl;
		instance3.SetData(20);
		std::cout << instance1.GetData() << ", " << instance2.GetData() << ", " << instance3.GetData() << std::endl;
	}
}

#endif /* AssignmentTesterClass_h */
