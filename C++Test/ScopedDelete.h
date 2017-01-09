//
//  ScopedDelete.hpp
//  C++Test
//
//  Created by Pradnyesh Gore on 1/8/17.
//  Copyright © 2017 Adobe. All rights reserved.
//

#ifndef ScopedDelete_hpp
#define ScopedDelete_hpp

#include <stdio.h>
#include <iostream>
#include <memory>

namespace ScopedDelete
{

	class ScopedDelete
	{
	public:
		ScopedDelete()
		{
			std::cout << "Scoped Delete Constructed" << std::endl;
		}
		
		~ScopedDelete()
		{
			std::cout << "Scoped Delete Destructed " << std::endl;
		}
	};

	
	void TestScopedDelete()
	{
		std::shared_ptr<ScopedDelete> sharedToDelete1(new ScopedDelete());
		{
			std::shared_ptr<ScopedDelete> sharedToDelete2 = sharedToDelete1;
		}
		std::cout << " --- Trace1 ---" << std::endl;
	}
	
}


#endif /* ScopedDelete_hpp */
