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

		//Component Constructor Test
		vec4f comp(1, 2, 3, 4);
		CHECK( (comp.x == 1 &&  comp.y == 2 &&
				comp.z == 3 &&  comp.w == 4)  );

		//Float4 constructor test
		float arrayf[4] = {5, 6, 7, 8};
		vec4f floatPParam(arrayf);
		CHECK(!memcmp(arrayf, &floatPParam, sizeof(vec4f)));

		//Vec4 constructor test
		vec4f vec4Param(comp);
		CHECK(!memcmp(&comp, &vec4Param, sizeof(vec4f)));

		//m128 constructor test
		__m128 sse = _mm_set_ps(2, 4, 6, 8);
		vec4f sseParam(sse);
		CHECK(!memcmp(&sse, &sseParam, sizeof(vec4f)));

		//Assignment Operator Check (vec4 -> vec4)
		vec4f as1 = vec4Param;
		CHECK(&as1 != &comp);
		CHECK(!memcmp(&as1, &comp, sizeof(vec4f)));

		//Assignment Operator Check (float* -> vec4)
		vec4f as2 = arrayf;
		CHECK(!memcmp(&as2, arrayf, sizeof(vec4f)));

		//Assignment Operator Check (__m128 -> vec4)
		vec4f as3 = sse;
		CHECK(!memcmp(&as3, &sse, sizeof(vec4f)));
	}

}
