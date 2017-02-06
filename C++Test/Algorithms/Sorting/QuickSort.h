
//
//  Header.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/5/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef Header_h
#define Header_h
namespace QuickSort
{
	namespace
	{		
		int Partition(std::vector<int>& inDataSource, int leftIndex, int rightIndex)
		{
			int left = leftIndex;
			int right = rightIndex;
			
			int pivotIndex = (leftIndex + rightIndex) / 2;
			int pivotValue = inDataSource[pivotIndex];
			
			std::swap(inDataSource[left], inDataSource[pivotIndex]);
			left += 1;
			
			while(left <= right)
			{
				while(inDataSource[left] <= pivotValue && left <= right)
				{
					left++;
				}
				while(inDataSource[right] > pivotValue && left <= right)
				{
					right--;
				}
				if(left<right)
				{
					std::swap(inDataSource[left], inDataSource[right]);
				}
			}
			std::swap(inDataSource[left-1], inDataSource[leftIndex]);
			return left -1;
		}
		
		void QuickSort(std::vector<int>& inDataSource, int left, int right)
		{
			int part = Partition(inDataSource, left, right);
			if(left < part-1)
			{
				QuickSort(inDataSource, left, part-1);
			}
			if(part+1<right)
			{
				QuickSort(inDataSource, part+1, right);
			}
		}
	}
	
	void TestQuickSort()
	{
		std::vector<int> sourceData = {1, 12, 5, 26, 7, 14, 3, 9, 2};
		QuickSort(sourceData, 0, (int)sourceData.size() -1);
		PrintVector(sourceData);
		PRINT_LINE("==");
		sourceData = {14, 26, 9, 12};
		QuickSort(sourceData, 0, (int)sourceData.size() -1);
		PrintVector(sourceData);
	}
}

#endif /* Header_h */
