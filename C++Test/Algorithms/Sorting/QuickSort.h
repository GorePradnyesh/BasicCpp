
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
		
		void Partition2(std::vector<int>& inDataSource, size_t inLeftIndex, size_t inRightIndex)
		{
			size_t leftIndex = inLeftIndex;
			size_t rightIndex = inRightIndex;
			if(leftIndex == rightIndex)
			{
				return; // single element, no partitioning
			}
			int pivotValue = inDataSource[(leftIndex + rightIndex)/2];
			
			while(leftIndex < rightIndex )
			{
				while(inDataSource[leftIndex] <= pivotValue)
				{
					leftIndex++;
				}
				while(inDataSource[rightIndex] > pivotValue)
				{
					rightIndex--;
				}
				if(leftIndex < rightIndex)
				{
					std::swap(inDataSource[leftIndex], inDataSource[rightIndex]);
				}
			}
			// here leftIndex == rightIndex
			Partition2(inDataSource, leftIndex +1, inRightIndex);
			Partition2(inDataSource, inLeftIndex, leftIndex - 1);
		}
		
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
