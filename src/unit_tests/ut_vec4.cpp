#include "catch2.hpp"
#include "../vec4/vec4f.h"
#include <math.h>

#if defined(_WIN32)
	#include <memory>
#else
	#include <string.h>
#endif

TEST_CASE("Data Structure", "[e], [sse], [x,y,z,w]") {
	//Create Constants
	const float _PI = 3.1415927;
	

	SECTION("Constructor Tests", "[vec4()]")
	{	
		//Default Constructor Test
		vec4f zero;
		CHECK(zero.IsZero());
	}

}
