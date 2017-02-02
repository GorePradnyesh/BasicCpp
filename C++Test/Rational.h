//
//  Rational.h
//  C++Test
//
//  Created by Pradnyesh Gore on 2/1/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef Rational_h
#define Rational_h
#include "CommonUtils.h"

namespace Rational
{
	namespace
	{
		class Rational
		{
		public:
			Rational(int inNumerator = 1, int inDenominator = 1)
			:
			mNumerator(inNumerator),
			mDenominator(inDenominator)
			{}
			
			int GetNumerator() const
			{
				return mNumerator;
			}
			
			int GetDenominator() const
			{
				return mDenominator;
			}
			
		private:
			int mNumerator;
			int mDenominator;
		};

		
		Rational operator*(const Rational& lhs, const Rational& rhs)
		{
			return Rational(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
		}

		std::ostream& operator<<(std::ostream& inOutputStream, const Rational& inRational)
		{
			inOutputStream << inRational.GetNumerator() << "/" << inRational.GetDenominator();
			return inOutputStream;
		}
	} // anon namespace
	
	void RationalTest()
	{
		Rational half = Rational(1, 2);
		Rational fourth = Rational(1, 4);
		Rational expectedEigth = half * fourth;
		Rational one = half * 2;
		Rational one1 = 2 * half;	// fails to compile without non-member operator
		
		PRINT_LINE(expectedEigth);
		PRINT_LINE(one);
		PRINT_LINE(one1);
	}
	
}

#endif /* Rational_h */
