//
//  SharedPointer.cpp
//  C++Test
//
//  Created by Pradnyesh Gore on 12/20/16.
//  Copyright © 2016 Adobe. All rights reserved.
//

#include "SharedPointer.h"
#include "CommonUtils.h"
#include "CommonTestClasses.h"
#include <memory>
#include <iostream>

namespace SharedPointerTest
{
	
	// RefCount implementation
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
		std::atomic<T> mReferenceCounter;
	};
	
	
	// Custom Shared Pointer implemenation
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
			return *this;
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
		
		// Move constructors and operators
		CSharedPointer(const CSharedPointer<T>&& inCSharedPointer)
		{
			
		}
		
		
		
	private:
		typedef RefCount<std::uint32_t> int32RefCount;
		int32RefCount*					mRefCount;
		T*								mData;
	};
	
	// Wrapper to test copy and move construction
	class NewWrapper
	{
	public:
		NewWrapper(const InnerData& inInnerData)
		:mInnerData(inInnerData)
		{}
		
		// Copy Ctor
		NewWrapper(const NewWrapper& inNewWrapper)
		:mInnerData(inNewWrapper.mInnerData)
		{
			PRINT_LINE("Copy constructed");
		}
		
		// Move constructor
		NewWrapper(NewWrapper&& inNewWrapper)
		:mInnerData(std::move(inNewWrapper.mInnerData))
		{
			PRINT_LINE("Move constructed");
		}
		
		// Move constructor
		NewWrapper(const NewWrapper&& inNewWrapper)
		:mInnerData(std::move(inNewWrapper.mInnerData))
		{
			PRINT_LINE("Const Move constructed");
		}
		
		// move assignment
		NewWrapper& operator=(InnerData&& inInnerData)
		{
			PRINT_LINE("Move Assigned");
			mInnerData = std::move(inInnerData);
			return *this;
		}
		
		// copy assgnment
		NewWrapper& operator=(const InnerData& inInnerData)
		{
			PRINT_LINE("Copy Assigned");
			mInnerData = inInnerData;
			return *this;
		}
		
	private:
		InnerData mInnerData;
	};
	
	NewWrapper GetNewWrapper(const NewWrapper& inNewWrapper)
	{
		return inNewWrapper;
	}
	
}	// anon namespace


void TestRValueRefs()
{
	using namespace SharedPointerTest;
	using UWrapper = std::unique_ptr<Wrapper>;
	UWrapper UWrapper1 = UWrapper(new Wrapper(12));
	UWrapper UWrapper2 = std::move(UWrapper1);
	UWrapper UWrapper3(std::move(UWrapper2));
	
	NewWrapper newWrapper = NewWrapper(InnerData(3));
	
	PRINT_LINE("====");
	NewWrapper movedWrapper(std::move(newWrapper));
	NewWrapper copiedWrapper(newWrapper);
	
	PRINT_LINE("====");
	const NewWrapper constNewWrapper = NewWrapper(InnerData(4));
	NewWrapper constMovedWrapper(std::move(constNewWrapper));		// inspite of xvalue, const-ness preceeds
	
	PRINT_LINE("====");
	NewWrapper&& nw1 = std::move(GetNewWrapper(newWrapper));
	
	// when nw1 comes in as argument it is an lvalue ( name rvalue is treated as lvalue ).
	// Hence to move construct it we use std::move
	NewWrapper nw2(std::move(nw1));
	
	PRINT_LINE("====");
	NewWrapper fromFunc(std::move(GetNewWrapper(newWrapper)));
	
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
