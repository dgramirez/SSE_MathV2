#define VEC4_FLOATS_GLOBAL
#define PRINT_DEBUG_INFO

#include <stdio.h>
#include <stdlib.h>
#include "catch2.hpp"
#include "../vec4/vec4f.h"

#if defined(_WIN32)
	#include <memory>
#else
	#include <string.h>
#endif

float rand_num() {
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX)/100.0f);
}

void print(const char* _Format, ...) {
#ifdef PRINT_DEBUG_INFO
	#ifdef _WIN32
		va_list v1;
		__va_start(&v1, _Format);
		auto ret = vprintf(_Format, v1);
		__crt_va_end(v1);
	#endif
#endif
}

void print_test(const char* test, const float& gx, const float& gy, const float& gz, const float& gw, const float& vx, const float& vy, const float& vz, const float& vw) {
#ifdef PRINT_DEBUG_INFO
	print("%s\n", test);
	print("\tGiven:  (%f, %f, %f, %f)\n", gx, gy, gz, gw);
	print("\tVector: (%f, %f, %f, %f)\n", vx, vy, vz, vw);
#endif
}

TEST_CASE("Contructors and Assignments", "[vec4], [operator=]") {
	//Create Constants
	const float _PI = 3.1415927;

	SECTION("Constructor Tests", "[vec4()]") {	
		//Default Constructor Test
		vec4 zero;
		CHECK(zero.IsZero());

		//Component Constructor Test
		float x = rand_num();
		float y = rand_num();
		float z = rand_num();
		float w = rand_num();

		vec4 comp(x, y, z, w);
		CHECK( (comp.x == x &&  comp.y == y &&
				comp.z == z &&  comp.w == w)  );
		print_test("Component Constructor Test:", x, y, z, w, comp.x, comp.y, comp.z, comp.w);

		//Float4 constructor test
		float arrayf[4];
		for (uint32_t i = 0; i < 4; ++i)
			arrayf[i] = rand_num();
		vec4 floatPParam(arrayf);
		CHECK(!memcmp(arrayf, &floatPParam, sizeof(vec4)));
		print_test("Float Pointer Constructor Test:", arrayf[0], arrayf[1], arrayf[2], arrayf[3], floatPParam.x, floatPParam.y, floatPParam.z, floatPParam.w);

		//Vec4 constructor test
		vec4 vec4Param(comp);
		CHECK(!memcmp(&comp, &vec4Param, sizeof(vec4)));
		print_test("Vector Constructor Test:", comp.x, comp.y, comp.z, comp.w, vec4Param.x, vec4Param.y, vec4Param.z, vec4Param.w);

		//m128 constructor test
		x *= 2; y *= 4; z *= 6; w *= 8;
		__m128 sse = _mm_set_ps(x, y, z, w);
		vec4 sseParam(sse);
		CHECK(!memcmp(&sse, &sseParam, sizeof(vec4)));
		print_test("__m128 Constructor Test:", w, z, y, x, sseParam.x, sseParam.y, sseParam.z, sseParam.w);

	}

	SECTION("Assignment Tests") {
		float x = rand_num();
		float y = rand_num();
		float z = rand_num();
		float w = rand_num();
		vec4 v(x, y, z, w);
		float fp[4] = { w, y, z, x };
		__m128 s = _mm_set_ps(x, y, z, w);

		//Assignment Operator Check (vec4 -> vec4)
		vec4 as1 = v;
		CHECK(&as1 != &v);
		CHECK(!memcmp(&as1, &v, sizeof(vec4)));
		print_test("Vector Assignment Test: ", v.x, v.y, v.z, v.w, as1.x, as1.y, as1.z, as1.w);

		//Assignment Operator Check (float* -> vec4)
		vec4f as2 = fp;
		CHECK(!memcmp(&as2, fp, sizeof(vec4)));

		//Assignment Operator Check (__m128 -> vec4)
		vec4f as3 = s;
		CHECK(!memcmp(&as3, &s, sizeof(vec4)));
	}

}

TEST_CASE("Equality Checks", "[vec4], [operator=]") {

	const vec4 ImZero;
	const vec4 ImNotZero(rand_num(), rand_num(), rand_num(), rand_num());

	SECTION("IsZero Equality Check", "[IsZero]") {
		//Default Constructor Test
		vec4 zero;
		CHECK(zero.IsZero());

		//Static Check (Vector)
		CHECK(vec4::IsZero(ImZero));
		
		//Static Check (Float*)
		float fp[4] = {};
		CHECK(vec4::IsZero(fp));

		//Static Check (m128)
		__m128 sse = _mm_setzero_ps();
		CHECK(vec4::IsZero(sse));
	}

	SECTION("IsEqual Equality Check", "[IsEqual], [operator==]") {

	}

}