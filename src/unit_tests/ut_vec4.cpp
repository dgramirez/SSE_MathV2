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

namespace {
	//Simple Pre-Req Check
	vec4 chk1(0, 1, 2, 3);
	__m128 chk2 = _mm_set_ps(3, 2, 1, 0);

	//Random Values
	const vec4 randVecA(19402.85160f, 94962.10349f, 316.59856f, 86832.32890f);
	const vec4 randVecB(36055.11004f, 47454.84500f, 69497.31268f, 624.19770f);
	const float randFPA[4] = { 4525.92146f, 64090.32973f, 40040.35343f, 119.59643f };
	const float randFPB[4] = { 93058.06245f, 71915.34440f, 2021.88100f, 46768.52948f };
	const __m128 randM128A = _mm_set_ps(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
	const __m128 randM128B = _mm_set_ps(31179.39351f, 32603.31492f, 74536.62178f, 96166.19073f);
	const float randScalarA = 7.34f;
	const float randScalarB = 2.85f;

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

		//IsZero False Checks
		CHECK_FALSE(ImNotZero.IsZero());
		CHECK_FALSE(vec4::IsZero(randVecA));
		CHECK_FALSE(vec4::IsZero(randFPA));
		CHECK_FALSE(vec4::IsZero(randM128A));
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

		//Static Check: Float Pointer vs Float Pointer
		CHECK(vec4::IsEqual(fp, fp));

		//Static Check: m128 vs m128
		CHECK(vec4::IsEqual(m128, m128));

		//Static Check: Float Pointer vs m128
		CHECK(vec4::IsEqual(fp, m128));
		CHECK(vec4::IsEqual(m128, fp));

		//Equality Operator Test
		CHECK(NotZeroV2 == ImNotZero);
		CHECK(NotZeroV2 == fp);
		CHECK(fp == ImNotZero);
		CHECK(NotZeroV2 == m128);
		CHECK(m128 == ImNotZero);

		//Equality False Checks
		CHECK_FALSE(NotZeroV2.IsEqual(randVecA));
		CHECK_FALSE(NotZeroV2.IsEqual(randFPA));
		CHECK_FALSE(NotZeroV2.IsEqual(randM128A));
		CHECK_FALSE(vec4::IsEqual(randVecA, randVecB));
		CHECK_FALSE(vec4::IsEqual(randVecA, fp));
		CHECK_FALSE(vec4::IsEqual(fp, randVecB));
		CHECK_FALSE(vec4::IsEqual(randVecA, m128));
		CHECK_FALSE(vec4::IsEqual(m128, randVecB));
		CHECK_FALSE(vec4::IsEqual(randFPA, randFPB));
		CHECK_FALSE(vec4::IsEqual(randM128A, randM128B));
		CHECK_FALSE(vec4::IsEqual(randFPA, randM128B));
		CHECK_FALSE(vec4::IsEqual(randM128A, randFPB));
		CHECK_FALSE(NotZeroV2 == randVecB);
		CHECK_FALSE(NotZeroV2 == randFPB);
		CHECK_FALSE(NotZeroV2 == randM128B);
		CHECK_FALSE(randFPA == NotZeroV2);
		CHECK_FALSE(randM128A == NotZeroV2);
	}

	SECTION("Inequality Operator Check", "[operator!=]") {
		//Create Random Vectors
		vec4 RandomVec1(rand_num(), rand_num(), rand_num(), rand_num());
		vec4 RandomVec2(rand_num(), rand_num(), rand_num(), rand_num());
		float RandomFP[4] = { rand_num(), rand_num(), rand_num(), rand_num() };
		__m128 RandomM128 = _mm_set_ps(rand_num(), rand_num(), rand_num(), rand_num());

		//Inequality Operator Test
		CHECK(RandomVec1 != RandomVec2);
		CHECK(RandomVec1 != RandomFP);
		CHECK(RandomFP != RandomVec2);
		CHECK(RandomVec1 != RandomM128);
		CHECK(RandomM128 != RandomVec2);

		//InEquality False Checks
		vec4 eqRandVecA = randVecA;
		vec4 eqFPA = randFPA;
		vec4 eqFPB = randFPB;
		vec4 eqM128A = randM128A;
		vec4 eqM128B = randM128B;

		CHECK_FALSE(eqRandVecA != randVecA);
		CHECK_FALSE(eqFPA != randFPA);
		CHECK_FALSE(randFPB != eqFPB);
		CHECK_FALSE(eqM128A != randM128A);
		CHECK_FALSE(randM128B != eqM128B);
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
		answer[0] = _mm_set_ps(11830.01756f, 43.13332f, 12937.61628f, 2643.44027f);
		answer[1] = _mm_set_ps(927.52290f, 4539.51448f, 15.134498f, 4150.88335f);
		answer[2] = _mm_set_ps(30467.48382f, 111.08721f, 33320.03631f, 6808.01811f);
		answer[3] = _mm_set_ps(41.96366f, 14049.24682f, 22487.83499f, 1588.04262f);
		answer[4] = _mm_set_ps(27913.63467f, 34226.21611f, 8207.94217f, 551.81627f);

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
		CHECK(myVec == answer[2]);
	}

	SECTION("Negate", "[Negate], [operator-]") {
		//Setup Answers for this section
		answer[0].m128 = _mm_set_ps(-86832.32890f, -316.59856f, -94962.10349f, -19402.85160f);
		answer[1].m128 = _mm_set_ps(-624.19770f, -69497.31268f, -47454.84500f, -36055.11004f);
		answer[2].m128 = _mm_set_ps(-119.59643f, -40040.35343f, -64090.32973f, -4525.92146f);
		answer[3].m128 = _mm_set_ps(-79553.85881f, -97658.71592f, -23392.63518f, -1572.67638f);
		answer[4].m128 = _mm_set_ps(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
		
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
	vec4 answer[10] = {};

	SECTION("Minimum Value [Per Component]", "[Min]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Min Method Test
		myVec.Min(randVecB);
		CHECK(myVec == answer[0]);

		//Static Min Test: Vector & Vector
		myVec = vec4::Min(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Min Test: Vector & Float Pointer
		myVec = vec4::Min(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Min Test: Float Pointer & Vector
		myVec = vec4::Min(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Min Test: Vector & m128
		myVec = vec4::Min(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Min Test: m128 & Vector
		myVec = vec4::Min(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Min Test: Float Pointer & Float Pointer
		myVec = vec4::Min(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Min Test: m128 & m128
		myVec = vec4::Min(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Min Test: Float Pointer & m128
		myVec = vec4::Min(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Min Test: m128 & Float Pointer
		myVec = vec4::Min(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Maximum Value [Per Component]", "[Max]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Max Method Test
		myVec.Max(randVecB);
		CHECK(myVec == answer[0]);

		//Static Max Test: Vector & Vector
		myVec = vec4::Max(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Max Test: Vector & Float Pointer
		myVec = vec4::Max(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Max Test: Float Pointer & Vector
		myVec = vec4::Max(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Max Test: Vector & m128
		myVec = vec4::Max(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Max Test: m128 & Vector
		myVec = vec4::Max(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Max Test: Float Pointer & Float Pointer
		myVec = vec4::Max(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Max Test: m128 & m128
		myVec = vec4::Max(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Max Test: Float Pointer & m128
		myVec = vec4::Max(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Max Test: m128 & Float Pointer
		myVec = vec4::Max(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Average Value [Per Component]", "[Avg]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Average Method Test
		myVec.Average(randVecB);
		CHECK(myVec == answer[0]);

		//Static Average Test: Vector & Vector
		myVec = vec4::Average(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Average Test: Vector & Float Pointer
		myVec = vec4::Average(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Average Test: Float Pointer & Vector
		myVec = vec4::Average(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Average Test: Vector & m128
		myVec = vec4::Average(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Average Test: m128 & Vector
		myVec = vec4::Average(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Average Test: Float Pointer & Float Pointer
		myVec = vec4::Average(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Average Test: m128 & m128
		myVec = vec4::Average(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Average Test: Float Pointer & m128
		myVec = vec4::Average(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Average Test: m128 & Float Pointer
		myVec = vec4::Average(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Vector Length Squared", "[LengthSq]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[4] = {

		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Length Squared Method Test
		vecAns = myVec.LengthSq();
		CHECK(vecAns == fAnswer[0]);

		//Static Length Squared Test: Vector
		vecAns = vec4::LengthSq(randVecB);
		CHECK(vecAns == fAnswer[1]);

		//Static Length Squared Test: Float Pointer
		vecAns = vec4::LengthSq(randFPA);
		CHECK(vecAns == fAnswer[2]);

		//Static Length Squared Test: m128
		vecAns = vec4::LengthSq(randM128A);
		CHECK(vecAns == fAnswer[3]);
	}

	SECTION("Vector Length", "[Length]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[4] = {

		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Length Squared Method Test
		vecAns = myVec.Length();
		CHECK(vecAns == fAnswer[0]);

		//Static Length Squared Test: Vector
		vecAns = vec4::Length(randVecB);
		CHECK(vecAns == fAnswer[1]);

		//Static Length Squared Test: Float Pointer
		vecAns = vec4::Length(randFPB);
		CHECK(vecAns == fAnswer[2]);

		//Static Length Squared Test: m128
		vecAns = vec4::Length(randM128B);
		CHECK(vecAns == fAnswer[3]);
	}
}

TEST_CASE("Vector Math Functions", "[Dot], [Cross], [Normalize], [Homogenize], [AngleBetween], [Component], [Project], [Reflect]") {
	//PreReq Check
	REQUIRE(chk1 == chk2);
	
	//Answer Array Setup
	vec4 answer[20] = {};

	SECTION("Dot Product Test", "[Dot], [Operator*]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[17] = {

		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Dot Product Method Test: Vector
		vecAns = myVec.Dot(randVecB);
		CHECK(vecAns == fAnswer[0]);

		//Dot Product Method Test: Float Pointer
		vecAns = myVec.Dot(randFPA);
		CHECK(vecAns == fAnswer[1]);

		//Dot Product Method Test: m128
		vecAns = myVec.Dot(randM128A);
		CHECK(vecAns == fAnswer[2]);

		//Static Dot Product Test: Vector & Vector
		vecAns = vec4::Dot(randVecA, randVecB);
		CHECK(vecAns == fAnswer[3]);
		
		//Static Dot Product Test: Vector & Float Pointer
		vecAns = vec4::Dot(randVecA, randFPB);
		CHECK(vecAns == fAnswer[4]);

		//Static Dot Product Test: Float Pointer & Vector
		vecAns = vec4::Dot(randFPA, randVecB);
		CHECK(vecAns == fAnswer[5]);

		//Static Dot Product Test: Vector & m128
		vecAns = vec4::Dot(randVecA, randM128B);
		CHECK(vecAns == fAnswer[6]);

		//Static Dot Product Test: m128 & Vector
		vecAns = vec4::Dot(randM128A, randVecB);
		CHECK(vecAns == fAnswer[7]);

		//Static Dot Product Test: Float Pointer & Float Pointer
		vecAns = vec4::Dot(randFPA, randFPB);
		CHECK(vecAns == fAnswer[8]);

		//Static Dot Product Test: m128 & m128
		vecAns = vec4::Dot(randM128A, randM128B);
		CHECK(vecAns == fAnswer[9]);

		//Static Dot Product Test: Float Pointer & m128
		vecAns = vec4::Dot(randFPA, randM128B);
		CHECK(vecAns == fAnswer[10]);

		//Static Dot Product Test: m128 & Float Pointer
		vecAns = vec4::Dot(randM128A, randFPB);
		CHECK(vecAns == fAnswer[11]);

		//Operator* Test: Vector & Vector
		vecAns = randVecA * randVecB;
		CHECK(vecAns == fAnswer[12]);
		
		//Operator* Test: Vector & Float Pointer
		vecAns = randVecA * randFPB;
		CHECK(vecAns == fAnswer[13]);

		//Operator* Test: Float Pointer & Vector
		vecAns = randFPA * randVecB;
		CHECK(vecAns == fAnswer[14]);

		//Operator* Test: Vector & m128
		vecAns = randVecA * randM128B;
		CHECK(vecAns == fAnswer[15]);

		//Operator* Test: m128 & Vector
		vecAns = randM128A * randVecB;
		CHECK(vecAns == fAnswer[16]);
	}

	SECTION("Cross Product Test", "[Cross], [Operator^]") {
		//Setup Answers for this section

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Cross Product Method Test: Vector
		myVec.Cross(randVecB);
		CHECK(myVec == answer[0]);

		//Cross Product Method Test: Float Pointer
		myVec.Cross(randFPA);
		CHECK(myVec == answer[1]);

		//Cross Product Method Test: m128
		myVec.Cross(randM128A);
		CHECK(myVec == answer[2]);

		//Operator^= Test: Vector
		myVec ^= randVecA;
		CHECK(myVec == answer[3]);

		//Operator^= Test: Float Pointer
		myVec ^= randFPB;
		CHECK(myVec == answer[4]);

		//Operator^= Test: m128
		myVec ^= randM128B;
		CHECK(myVec == answer[5]);

		//Static Cross Product Test: Vector & Vector
		myVec = vec4::Cross(randVecA, randVecB);
		CHECK(myVec == answer[6]);
		
		//Static Cross Product Test: Vector & Float Pointer
		myVec =vec4::Cross(randVecA, randFPB);
		CHECK(myVec == answer[7]);

		//Static Cross Product Test: Float Pointer & Vector
		myVec =vec4::Cross(randFPA, randVecB);
		CHECK(myVec == answer[8]);

		//Static Cross Product Test: Vector & m128
		myVec =vec4::Cross(randVecA, randM128B);
		CHECK(myVec == answer[9]);

		//Static Cross Product Test: m128 & Vector
		myVec =vec4::Cross(randM128A, randVecB);
		CHECK(myVec == answer[10]);

		//Static Cross Product Test: Float Pointer & Float Pointer
		myVec =vec4::Cross(randFPA, randFPB);
		CHECK(myVec == answer[11]);

		//Static Cross Product Test: m128 & m128
		myVec =vec4::Cross(randM128A, randM128B);
		CHECK(myVec == answer[12]);

		//Static Cross Product Test: Float Pointer & m128
		myVec =vec4::Cross(randFPA, randM128B);
		CHECK(myVec == answer[13]);

		//Static Cross Product Test: m128 & Float Pointer
		myVec =vec4::Cross(randM128A, randFPB);
		CHECK(myVec == answer[14]);

		//operator^ Test: Vector & Vector
		myVec =randVecA ^ randVecB;
		CHECK(myVec == answer[15]);
		
		//operator^ Test: Vector & Float Pointer
		myVec =randVecA ^ randFPB;
		CHECK(myVec == answer[16]);

		//operator^ Test: Float Pointer & Vector
		myVec =randFPA ^ randVecB;
		CHECK(myVec == answer[17]);

		//operator^ Test: Vector & m128
		myVec =randVecA ^ randM128B;
		CHECK(myVec == answer[18]);

		//operator^ Test: m128 & Vector
		myVec =randM128A ^ randVecB;
		CHECK(myVec == answer[19]);
	}

	SECTION("Normalize Test", "[Normalize]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Normalize Method Test
		myVec.Normalize();
		CHECK(myVec == answer[0]);

		//Static Normalize Function Check: Vector
		myVec = vec4::Normalize(randVecB);
		CHECK(myVec == answer[1]);

		//Static Normalize Function Check: Float Pointer
		myVec = vec4::Normalize(randFPA);
		CHECK(myVec == answer[2]);

		//Static Normalize Function Check: m128
		myVec = vec4::Normalize(randM128A);
		CHECK(myVec == answer[3]);
	}

	SECTION("Homogenize Test", "[Homogenize]") {
		//Setup Answers for this section
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Homogenize Method Test
		myVec.Homogenize();
		CHECK(myVec == answer[0]);

		//Static Homogenize Function Check: Vector
		myVec = vec4::Homogenize(randVecB);
		CHECK(myVec == answer[1]);

		//Static Homogenize Function Check: Vector
		myVec = vec4::Homogenize(randFPB);
		CHECK(myVec == answer[2]);

		//Static Homogenize Function Check: Vector
		myVec = vec4::Homogenize(randM128B);
		CHECK(myVec == answer[3]);
	}

	SECTION("Angle Between Vector Test", "[AngleBetween]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[8] = {

		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Angle Between Method Test: Vector
		vecAns = myVec.AngleBetween(randVecB);
		CHECK(vecAns == fAnswer[0]);

		//Angle Between Method Test: Float Pointer
		vecAns = myVec.AngleBetween(randFPA);
		CHECK(vecAns == fAnswer[1]);

		//Angle Between Method Test: m128
		vecAns = myVec.AngleBetween(randM128A);
		CHECK(vecAns == fAnswer[2]);

		//Static Angle Between Test: Vector & Vector
		vecAns = vec4::AngleBetween(randVecA, randVecB);
		CHECK(vecAns == fAnswer[3]);
		
		//Static Angle Between Test: Vector & Float Pointer
		vecAns = vec4::AngleBetween(randVecA, randFPB);
		CHECK(vecAns == fAnswer[4]);

		//Static Angle Between Test: Float Pointer & Vector
		vecAns = vec4::AngleBetween(randFPA, randVecB);
		CHECK(vecAns == fAnswer[5]);

		//Static Angle Between Test: Vector & m128
		vecAns = vec4::AngleBetween(randVecA, randM128B);
		CHECK(vecAns == fAnswer[6]);

		//Static Angle Between Test: m128 & Vector
		vecAns = vec4::AngleBetween(randM128A, randVecB);
		CHECK(vecAns == fAnswer[7]);

		//Static Angle Between Test: Float Pointer & Float Pointer
		vecAns = vec4::AngleBetween(randFPA, randFPB);
		CHECK(vecAns == fAnswer[8]);

		//Static Angle Between Test: m128 & m128
		vecAns = vec4::AngleBetween(randM128A, randM128B);
		CHECK(vecAns == fAnswer[9]);

		//Static Angle Between Test: Float Pointer & m128
		vecAns = vec4::AngleBetween(randFPA, randM128B);
		CHECK(vecAns == fAnswer[10]);

		//Static Angle Between Test: m128 & Float Pointer
		vecAns = vec4::AngleBetween(randM128A, randFPB);
		CHECK(vecAns == fAnswer[11]);
	}

	SECTION("Component Test", "[Component]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[4] = {

		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Component Method Test: Vector
		vecAns = myVec.Component(randVecB);
		CHECK(vecAns == fAnswer[0]);

		//Component Method Test: Float Pointer
		vecAns = myVec.Component(randFPA);
		CHECK(vecAns == fAnswer[1]);

		//Component Method Test: m128
		vecAns = myVec.Component(randM128A);
		CHECK(vecAns == fAnswer[2]);

		//Static Component Test: Vector & Vector
		vecAns = vec4::Component(randVecA, randVecB);
		CHECK(vecAns == fAnswer[3]);
		
		//Static Component Test: Vector & Float Pointer
		vecAns = vec4::Component(randVecA, randFPB);
		CHECK(vecAns == fAnswer[4]);

		//Static Component Test: Float Pointer & Vector
		vecAns = vec4::Component(randFPA, randVecB);
		CHECK(vecAns == fAnswer[5]);

		//Static Component Test: Vector & m128
		vecAns = vec4::Component(randVecA, randM128B);
		CHECK(vecAns == fAnswer[6]);

		//Static Component Test: m128 & Vector
		vecAns = vec4::Component(randM128A, randVecB);
		CHECK(vecAns == fAnswer[7]);

		//Static Component Test: Float Pointer & Float Pointer
		vecAns = vec4::Component(randFPA, randFPB);
		CHECK(vecAns == fAnswer[8]);

		//Static Component Test: m128 & m128
		vecAns = vec4::Component(randM128A, randM128B);
		CHECK(vecAns == fAnswer[9]);

		//Static Component Test: Float Pointer & m128
		vecAns = vec4::Component(randFPA, randM128B);
		CHECK(vecAns == fAnswer[10]);

		//Static Component Test: m128 & Float Pointer
		vecAns = vec4::Component(randM128A, randFPB);
		CHECK(vecAns == fAnswer[11]);
	}

	SECTION("Project Test", "[Project]") {
		//Setup Answers for this section

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Project Method Test: Vector
		myVec.Project(randVecB);
		CHECK(myVec == answer[0]);

		//Project Method Test: Float Pointer
		myVec.Project(randFPA);
		CHECK(myVec == answer[1]);

		//Project Method Test: m128
		myVec.Project(randM128A);
		CHECK(myVec == answer[2]);

		//Static Project Test: Vector & Vector
		myVec = vec4::Project(randVecA, randVecB);
		CHECK(myVec == answer[3]);
		
		//Static Project Test: Vector & Float Pointer
		myVec = vec4::Project(randVecA, randFPB);
		CHECK(myVec == answer[4]);

		//Static Project Test: Float Pointer & Vector
		myVec = vec4::Project(randFPA, randVecB);
		CHECK(myVec == answer[5]);

		//Static Project Test: Vector & m128
		myVec = vec4::Project(randVecA, randM128B);
		CHECK(myVec == answer[6]);

		//Static Project Test: m128 & Vector
		myVec = vec4::Project(randM128A, randVecB);
		CHECK(myVec == answer[7]);

		//Static Project Test: Float Pointer & Float Pointer
		myVec = vec4::Project(randFPA, randFPB);
		CHECK(myVec == answer[8]);

		//Static Project Test: m128 & m128
		myVec = vec4::Project(randM128A, randM128B);
		CHECK(myVec == answer[9]);

		//Static Project Test: Float Pointer & m128
		myVec = vec4::Project(randFPA, randM128B);
		CHECK(myVec == answer[10]);

		//Static Project Test: m128 & Float Pointer
		myVec = vec4::Project(randM128A, randFPB);
		CHECK(myVec == answer[11]);
	}

	SECTION("Reflect Test", "[Reflect]") {
		//Setup Answers for this section

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Reflect Method Test: Vector
		myVec.Reflect(randVecB);
		CHECK(myVec == answer[0]);

		//Reflect Method Test: Float Pointer
		myVec.Reflect(randFPA);
		CHECK(myVec == answer[1]);

		//Reflect Method Test: m128
		myVec.Reflect(randM128A);
		CHECK(myVec == answer[2]);

		//Static Reflect Test: Vector & Vector
		myVec = vec4::Reflect(randVecA, randVecB);
		CHECK(myVec == answer[3]);
		
		//Static Reflect Test: Vector & Float Pointer
		myVec = vec4::Reflect(randVecA, randFPB);
		CHECK(myVec == answer[4]);

		//Static Reflect Test: Float Pointer & Vector
		myVec = vec4::Reflect(randFPA, randVecB);
		CHECK(myVec == answer[5]);

		//Static Reflect Test: Vector & m128
		myVec = vec4::Reflect(randVecA, randM128B);
		CHECK(myVec == answer[6]);

		//Static Reflect Test: m128 & Vector
		myVec = vec4::Reflect(randM128A, randVecB);
		CHECK(myVec == answer[7]);

		//Static Reflect Test: Float Pointer & Float Pointer
		myVec = vec4::Reflect(randFPA, randFPB);
		CHECK(myVec == answer[8]);

		//Static Reflect Test: m128 & m128
		myVec = vec4::Reflect(randM128A, randM128B);
		CHECK(myVec == answer[9]);

		//Static Reflect Test: Float Pointer & m128
		myVec = vec4::Reflect(randFPA, randM128B);
		CHECK(myVec == answer[10]);

		//Static Reflect Test: m128 & Float Pointer
		myVec = vec4::Reflect(randM128A, randFPB);
		CHECK(myVec == answer[11]);
	}
}
