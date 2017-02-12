//
//  Matrix.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/11/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

namespace Matrix
{
	class Matrix
	{
	public:
		Matrix(int inRowCount, int inColCount)
		:mRowCount(inRowCount),
		mColCount(inColCount)
		{
			mData = new int*[mRowCount];
			for(int rowIndex = 0; rowIndex < mRowCount; rowIndex++)
			{
				mData[rowIndex] = new int[inColCount];
			}
		}
		
		Matrix& operator=(const Matrix& inMatrix)
		{
			mRowCount = inMatrix.mRowCount;
			mColCount = inMatrix.mColCount;
			mData = inMatrix.mData;
			return *this;
		}
		
		/*
		~Matrix()
		{
			for(int rowIndex=0; rowIndex < mRowCount; rowIndex++)
			{
				delete[] mData[rowIndex];
			}
			delete[] mData;
		}
		*/
		
		void Fill(int inValue)
		{
			for(int rowIndex=0; rowIndex < mRowCount; rowIndex++)
			{
				for(int colIndex=0; colIndex < mColCount; colIndex++)
				{
					mData[rowIndex][colIndex] = inValue;
				}
			}
		}
		
		void Print()
		{
			for(int rowIndex=0; rowIndex < mRowCount; rowIndex++)
			{
				for(int colIndex=0; colIndex < mColCount; colIndex++)
				{
					PRINT_STRING(mData[rowIndex][colIndex]);
					if(colIndex != mColCount-1)
					{
						PRINT_STRING(", ");
					}
				}
				PRINT_LINE("");
			}
		}
		
		int mRowCount;
		int mColCount;
		int** mData;
	};
	
	void MultiplyMatrices(const Matrix& op1, const Matrix& op2, Matrix& outMatrix)
	{
		if(op1.mColCount != op2.mRowCount)
		{
			outMatrix = Matrix(0,0);
		}
		outMatrix = Matrix(op1.mRowCount, op2.mColCount);
		outMatrix.Fill(0);
		for(int outRowIndex=0; outRowIndex< outMatrix.mRowCount; outRowIndex++)
		{
			for(int outColIndex=0; outColIndex < outMatrix.mColCount; outColIndex++)
			{
				for(int interRowIndex=0; interRowIndex<op1.mColCount; interRowIndex++)
				{
					outMatrix.mData[outRowIndex][outColIndex] += op1.mData[outRowIndex][interRowIndex] * op2.mData[interRowIndex][outColIndex];
				}
			}
		}
	}
	
	
	void TestMatrix()
	{
		Matrix m1(2,3);
		int fillValue = 0;
		for(int rowIndex=0; rowIndex<m1.mRowCount; rowIndex++)
		{
			for(int colIndex=0; colIndex<m1.mColCount; colIndex++)
			{
				m1.mData[rowIndex][colIndex] = fillValue++;
			}
		}
		m1.Print();
		
		Matrix m2(3,3);
		for(int rowIndex=0; rowIndex<m2.mRowCount; rowIndex++)
		{
			for(int colIndex=0; colIndex<m2.mColCount; colIndex++)
			{
				if(rowIndex == colIndex)
				{
					m2.mData[rowIndex][colIndex] = 1;
				}
				else
				{
					m2.mData[rowIndex][colIndex] = 0;
				}
			}
		}
		m2.Print();
		
		Matrix m3(m1.mRowCount, m2.mColCount);
		MultiplyMatrices(m1, m2, m3);
		m3.Print();
	}
}


#endif /* Matrix_h */
