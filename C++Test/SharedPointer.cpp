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
	
	template <typename T>
	class RefCount
	{
	public:
		RefCount()
		:mReferenceCounter(0)
		{}
		
		T AddRef()
		{
			return mReferenceCounter++;
		}
		
		T Release()
		{
			return mReferenceCounter--;
		}
		
		T GetCount()
		{
			return mReferenceCounter;
		}
		
	private:
		T mReferenceCounter;
	};
	
	
	template <typename T>
	class CSharedPointer
	{
	public:
		CSharedPointer()
		:mData(NULL), mRefCount(new int32RefCount())
		{
			mRefCount = 0;
		}
		
		
		CSharedPointer(T* inData)
		:mData(inData), mRefCount(new int32RefCount())
		{
			mRefCount->AddRef();
		}
		
		
		~CSharedPointer()
		{
			if(mRefCount->Release() == 0)
			{
				delete mData;
				delete mRefCount;
			}
		}
		
		
		CSharedPointer(const CSharedPointer<T>& inCSharedPointer)
		:mData(inCSharedPointer.mData),
		mRefCount(inCSharedPointer.mRefCount)
		{
			mRefCount->AddRef();
		}
		
		
		CSharedPointer<T>& operator=(const CSharedPointer<T>& inCSharedPointer)
		{
			if(this != &inCSharedPointer)
			{
				if(mRefCount->Release() == 0)
				{
					delete mData;
					delete mRefCount;
				}
				
				mData		= inCSharedPointer.mData;
				mRefCount	= inCSharedPointer.mRefCount;
				mRefCount->AddRef();
			}
		}
		
		T& operator*()
		{
			return *mData;
		}
		
		T* operator->()
		{
			return mData;
		}
		
		void reset(T* inData = NULL)
		{
			if(mRefCount->Release() == 0)
			{
				delete mRefCount;
				delete mData;
			}
			if(inData != NULL)
			{
				mData = inData;
				mRefCount = new int32RefCount();
			}
		
		}
		
		std::uint32_t use_count()
		{
			return mRefCount->GetCount();
		}
		
	private:
		typedef RefCount<std::uint32_t> int32RefCount;
		int32RefCount*					mRefCount;
		T*								mData;
	};
}

void TestShared()
{
	using namespace SharedPointerTest;
	InnerData data(4);
	
#define USE_STD_IMPL 0
#if USE_STD_IMPL
	typedef std::shared_ptr<Wrapper> WrapperPtr;
#else
	typedef CSharedPointer<Wrapper> WrapperPtr;
#endif
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
	
	wrapper2.reset();
	std::cout << std::endl;
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	std::cout << "Use Count wrapper2 " << wrapper2.use_count() << std::endl;
	std::cout << "Use Count wrapper3 " << wrapper3.use_count() << std::endl;
	
	wrapper3.reset();
	std::cout << std::endl;
	std::cout << "Use Count wrapper1 " << wrapper1.use_count() << std::endl;
	std::cout << "Use Count wrapper2 " << wrapper2.use_count() << std::endl;
	std::cout << "Use Count wrapper3 " << wrapper3.use_count() << std::endl;
	
}
