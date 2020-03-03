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

namespace {
	//Simple Pre-Req Check
	vec4 chk1(0, 1, 2, 3);
	__m128 chk2 = _mm_set_ps(3, 2, 1, 0);

	//Random Values
	vec4 randVecA(19402.85160f, 94962.10349f, 316.59856f, 86832.32890f);
	vec4 randVecB(36055.11004f, 47454.84500f, 69497.31268f, 624.19770f);
	float randFPA[4] = { 4525.92146f, 64090.32973f, 40040.35343f, 119.59643f };
	float randFPB[4] = { 4525.92146f, 64090.32973f, 40040.35343f, 119.59643f };
	__m128 randM128A = _mm_set_ps(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
	__m128 randM128B = _mm_set_ps(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
	float randScalarA = 7.34f;
	float randScalarB = 2.85f;
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

TEST_CASE("Equality Checks", "[IsZero], [IsEqual], [operator==] [operator!=]") {

	const vec4 ImZero;
	const vec4 ImNotZero(rand_num(), rand_num(), rand_num(), rand_num());

	SECTION("IsZero Equality Check", "[IsZero]") {
		//IsZero Method Test
		vec4 zero;
		CHECK(zero.IsZero());

		//Static IsZero Function Check (Vector)
		CHECK(vec4::IsZero(ImZero));
		
		//Static IsZero Function Check (Float*)
		float fp[4] = {};
		CHECK(vec4::IsZero(fp));

		//Static IsZero Function Check (m128)
		__m128 sse = _mm_setzero_ps();
		CHECK(vec4::IsZero(sse));
	}

	SECTION("IsEqual Equality Check", "[IsEqual], [operator==]") {
		//IsEqual Method Test: (Vector)
		vec4 NotZeroV2 = ImNotZero;
		CHECK(NotZeroV2.IsEqual(ImNotZero));

		//IsEqual Method Test: (Float Pointer)
		float fp[4] = { ImNotZero.x, ImNotZero.y, ImNotZero.z, ImNotZero.w };
		CHECK(NotZeroV2.IsEqual(fp));

		//IsEqual Method Test: (m128)
		__m128 m128 = _mm_set_ps(ImNotZero.w, ImNotZero.z, ImNotZero.y, ImNotZero.x);
		CHECK(NotZeroV2.IsEqual(m128));

		//Static Check: Vector vs Vector
		CHECK(vec4::IsEqual(NotZeroV2, ImNotZero));

		//Static Check: Vector vs Float Pointer
		CHECK(vec4::IsEqual(NotZeroV2, fp));
		CHECK(vec4::IsEqual(fp, NotZeroV2));

		//Static Check: Vector vs m128
		CHECK(vec4::IsEqual(NotZeroV2, m128));
		CHECK(vec4::IsEqual(m128, NotZeroV2));

		//Equality Operator Test
		CHECK(NotZeroV2 == ImNotZero);
		CHECK(NotZeroV2 == fp);
		CHECK(fp == ImNotZero);
		CHECK(NotZeroV2 == m128);
		CHECK(m128 == ImNotZero);
	}

	SECTION("Inequality Operator Check", "[operator!=]") {
		//Create Random Vectors
		vec4 RandomVec1(rand_num(), rand_num(),rand_num(),rand_num());
		vec4 RandomVec2(rand_num(), rand_num(),rand_num(),rand_num());
		float RandomFP[4] = { rand_num(), rand_num(),rand_num(),rand_num() };
		__m128 RandomM128 = _mm_set_ps(rand_num(), rand_num(),rand_num(),rand_num());

		//Inequality Operator Test
		CHECK(RandomVec1 != RandomVec2);
		CHECK(RandomVec1 != RandomFP);
		CHECK(RandomFP != RandomVec2);
		CHECK(RandomVec1 != RandomM128);
		CHECK(RandomM128 != RandomVec2);
	}

}

TEST_CASE("Basic Vector Math", "[Add], [Sub], [Mul], [Div]") {
	//PreReq Check
	REQUIRE(chk1 == chk2);
	
	//Answer Array Setup
	vec4 answer[20] = {};

	SECTION("Addition", "[Add], [operator+], [operator+=]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Member Method Add: Vector vs Vector ----------------------
		myVec.Add(randVecB);
		CHECK(myVec == answer[0]);

		//Member Method Add: Vector vs Float Pointer
		myVec.Add(randFPA);
		CHECK(myVec == answer[1]);

		//Member Method Add: Vector vs m128
		myVec.Add(randM128B);
		CHECK(myVec == answer[2]);

		//Member Operator+= Add: Vector vs Vector ---------------------
		myVec += randVecA;
		CHECK(myVec == answer[3]);

		//Member Operator+= Add: Vector vs Float Pointer
		myVec += randFPB;
		CHECK(myVec == answer[4]);

		//Member Operator+= Add: Vector vs m128
		myVec += randM128B;
		CHECK(myVec == answer[5]);

		//Static Add: Vector vs Vector ---------------------------------
		myVec = vec4::Add(randVecA, randVecB);
		CHECK(myVec == answer[0]);

		//Static Add: Vector vs FP
		myVec = vec4::Add(randVecA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Add: FP vs Vector
		myVec = vec4::Add(randFPA, randVecB);
		CHECK(myVec == answer[7]);

		//Static Add: Vector vs m128
		myVec = vec4::Add(randVecA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Add: m128 vs Vector
		myVec = vec4::Add(randM128A, randVecB);
		CHECK(myVec == answer[9]);

		//Static Add: Float Pointer & Float Pointer --------------------
		myVec = vec4::Add(randFPA, randFPB);
		CHECK(myVec == answer[10]);

		//Static Sub: m128 & m128
		myVec = vec4::Add(randM128A, randM128B);
		CHECK(myVec == answer[11]);

		//Static Sub: Float Pointer & m128
		myVec = vec4::Add(randFPA, randM128B);
		CHECK(myVec == answer[12]);

		//Static Sub: m128 & Float Pointer
		myVec = vec4::Add(randM128A, randFPB);
		CHECK(myVec == answer[13]);

		//Operator+ Add: Vector vs Vector ------------------------------
		myVec = randVecA + randVecB;
		CHECK(myVec == answer[14]);

		//Operator+ Add: Vector vs FP
		myVec = randVecA + randFPB;
		CHECK(myVec == answer[15]);

		//Operator+ Add: FP vs Vector
		myVec = randFPA + randVecB;
		CHECK(myVec == answer[16]);

		//Operator+ Add: Vector vs m128
		myVec = randVecA + randM128B;
		CHECK(myVec == answer[17]);

		//Operator+ Add: m128 vs Vector
		myVec = randM128A + randVecB;
		CHECK(myVec == answer[18]);
	}

	SECTION("Subtraction", "[Sub], [operator-], [operator-=]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Member Method Sub: Vector vs Vector ----------------------
		myVec.Sub(randVecB);
		CHECK(myVec == answer[0]);

		//Member Method Sub: Vector vs Float Pointer
		myVec.Sub(randFPA);
		CHECK(myVec == answer[1]);

		//Member Method Sub: Vector vs m128
		myVec.Sub(randM128A);
		CHECK(myVec == answer[2]);

		//Member Operator+= Sub: Vector vs Vector ---------------------
		myVec -= randVecA;
		CHECK(myVec == answer[3]);

		//Member Operator+= Sub: Vector vs Float Pointer
		myVec -= randFPB;
		CHECK(myVec == answer[4]);

		//Member Operator+= Sub: Vector vs m128
		myVec -= randM128B;
		CHECK(myVec == answer[5]);

		//Static Sub: Vector vs Vector ---------------------------------
		myVec = vec4::Sub(randVecA, randVecB);
		CHECK(myVec == answer[6]);

		//Static Sub: Vector vs FP
		myVec = vec4::Sub(randVecA, randFPB);
		CHECK(myVec == answer[7]);

		//Static Sub: FP vs Vector
		myVec = vec4::Sub(randFPA, randVecB);
		CHECK(myVec == answer[8]);

		//Static Sub: Vector vs m128
		myVec = vec4::Sub(randVecA, randM128B);
		CHECK(myVec == answer[9]);

		//Static Sub: m128 vs Vector
		myVec = vec4::Sub(randM128A, randVecB);
		CHECK(myVec == answer[10]);

		//Static Sub: Float Pointer & Float Pointer --------------------
		myVec = vec4::Sub(randFPA, randFPB);
		CHECK(myVec == answer[11]);

		//Static Sub: m128 & m128
		myVec = vec4::Sub(randM128A, randM128B);
		CHECK(myVec == answer[12]);

		//Static Sub: Float Pointer & m128
		myVec = vec4::Sub(randFPA, randM128B);
		CHECK(myVec == answer[13]);

		//Static Sub: m128 & Float Pointer
		myVec = vec4::Sub(randM128A, randFPB);
		CHECK(myVec == answer[14]);

		//Operator+ Sub: Vector vs Vector ------------------------------
		myVec = randVecA - randVecB;
		CHECK(myVec == answer[15]);

		//Operator+ Sub: Vector vs FP
		myVec = randVecA - randFPB;
		CHECK(myVec == answer[16]);

		//Operator+ Sub: FP vs Vector
		myVec = randFPA - randVecB;
		CHECK(myVec == answer[17]);

		//Operator+ Sub: Vector vs m128
		myVec = randVecA - randM128B;
		CHECK(myVec == answer[18]);

		//Operator+ Sub: m128 vs Vector
		myVec = randM128A - randVecB;
		CHECK(myVec == answer[19]);
	}

	SECTION("Scalar Multiply", "[Mul], [operator*], [operator*=]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Mul Method Test
		myVec.Mul(randScalarA);
		CHECK(myVec == answer[0]);

		//Operator*= Test
		myVec *= randScalarB;
		CHECK(myVec == answer[1]);

		//Static Mul Test: Vector & Scalar
		myVec = vec4::Mul(randVecA, randScalarB);
		CHECK(myVec == answer[2]);

		//Static Mul Test: Scalar & Vector
		myVec = vec4::Mul(randScalarA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Mul Test: Float Pointer & Scalar
		myVec = vec4::Mul(randFPA, randScalarB);
		CHECK(myVec == answer[4]);

		//Static Mul Test: Scalar & Float Pointer 
		myVec = vec4::Mul(randScalarA, randFPB);
		CHECK(myVec == answer[5]);
		
		//Static Mul Test: m128 & Scalar
		myVec = vec4::Mul(randM128A, randScalarB);
		CHECK(myVec == answer[6]);

		//Static Mul Test: Scalar & m128
		myVec = vec4::Mul(randScalarA, randM128B);
		CHECK(myVec == answer[7]);

		//Operator* Test: vec4 & float
		myVec = randVecA * randScalarB;
		CHECK(myVec == answer[8]);

		//Operator*: float & vec4
		myVec = randScalarA * randVecB;
		CHECK(myVec == answer[9]);
	}

	SECTION("Scalar Divide", "[Div], [operator/=], [operator/]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Div Method Test
		myVec.Div(randScalarA);
		CHECK(myVec == answer[0]);

		//Operator/= Test
		myVec /= randScalarB;
		CHECK(myVec == answer[1]);

		//Static Mul Test: Vector & Scalar
		myVec = vec4::Div(randVecA, randScalarB);
		CHECK(myVec == answer[2]);

		//Static Mul Test: Float Pointer & Scalar
		myVec = vec4::Div(randFPA, randScalarB);
		CHECK(myVec == answer[3]);

		//Static Mul Test: m128 & Scalar
		myVec = vec4::Div(randM128A, randScalarB);
		CHECK(myVec == answer[4]);

		//Operator/ Test: vec4 & Scalar
		myVec = randVecA / randScalarB;
		CHECK(myVec == answer[5]);
	}

	SECTION("Negate", "[Negate], [operator-]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Negate Method Test
		myVec.Negate();
		CHECK(myVec == answer[0]);

		//Static Negate Test: Vector
		myVec = vec4::Negate(randVecB);
		CHECK(myVec == answer[1]);

		//Static Negate Test: Float Pointer
		myVec = vec4::Negate(randFPA);
		CHECK(myVec == answer[2]);

		//Static Negate Test: m128
		myVec = vec4::Negate(randM128A);
		CHECK(myVec == answer[3]);

		//Operator- Test: vector
		myVec = -myVec;
		CHECK(myVec == answer[4]);
	}
}

TEST_CASE("Basic Normal Math Functions ", "[Min], [Max], [Average],[Length], [LengthSq]") {
	//PreReq Check
	REQUIRE(chk1 == chk2);
	
	//Answer Array Setup
	vec4 answer[4] = {};

	SECTION("Minimum Value [Per Component]", "[Min]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Min Method Test
		myVec.Min(randVecB);

		//Static Min Test: Vector & Vector
		myVec = vec4::Min(randVecA, randVecB);

		//Static Min Test: Vector & Float Pointer
		myVec = vec4::Min(randVecA, randFPB);

		//Static Min Test: Float Pointer & Vector
		myVec = vec4::Min(randFPA, randVecB);

		//Static Min Test: Vector & m128
		myVec = vec4::Min(randVecA, randM128B);

		//Static Min Test: m128 & Vector
		myVec = vec4::Min(randM128A, randVecB);

		
	}

	SECTION("Maximum Value [Per Component]", "[Max]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;
	}

	SECTION("Average Value [Per Component]", "[Avg]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;
	}

	SECTION("Vector Length Squared", "[LengthSq]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;
	}

	SECTION("Vector Length", "[Length]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;
	}
}