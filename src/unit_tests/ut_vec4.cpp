#define VEC4_FLOATS_GLOBAL

#include "catch2.hpp"
#include "ut_utility.h"
using namespace sml;

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
}

TEST_CASE("Contructors, Assignment, and Set for sml::vec4f", "[vec4f], [operator=], [Set]") {
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

		//Float4 constructor test
		float arrayf[4];
		for (uint32_t i = 0; i < 4; ++i)
			arrayf[i] = rand_num();
		vec4 floatPParam(arrayf);
		CHECK(!memcmp(arrayf, &floatPParam, sizeof(vec4)));

		//Vec4 constructor test
		vec4 vec4Param(comp);
		CHECK(!memcmp(&comp, &vec4Param, sizeof(vec4)));

		//m128 constructor test
		x *= 2; y *= 4; z *= 6; w *= 8;
		__m128 sse = _mm_set_ps(x, y, z, w);
		vec4 sseParam(sse);
		CHECK(!memcmp(&sse, &sseParam, sizeof(vec4)));

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

		//Assignment Operator Check (float* -> vec4)
		vec4f as2 = fp;
		CHECK(!memcmp(&as2, fp, sizeof(vec4)));

		//Assignment Operator Check (__m128 -> vec4)
		vec4f as3 = s;
		CHECK(!memcmp(&as3, &s, sizeof(vec4)));
	}

	SECTION("Set Tests") {
		float x = rand_num();
		float y = rand_num();
		float z = rand_num();
		float w = rand_num();
		float t[4] = { x, y, z, w };
		
		vec4 v(y, z, w, x);
		float fp[4] = { w, y, z, x };
		__m128 s = _mm_set_ps(z, w, x, y);

		//Static Set: 
		vec4 set1 = sml::VectorSet(x, y, z, w);
		CHECK(!memcmp(t, &set1, sizeof(vec4)));

		vec4 set2 = sml::VectorSet(v);
		CHECK(!memcmp(&set2, &v, sizeof(vec4)));

		vec4 set3 = sml::VectorSet(fp);
		CHECK(!memcmp(fp, &set3, sizeof(vec4)));

		vec4 set4 = sml::VectorSet(s);
		CHECK(!memcmp(&set4, &s, sizeof(vec4)));
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
		CHECK(sml::VectorIsZero(ImZero));
		
		//Static IsZero Function Check (Float*)
		float fp[4] = {};
		CHECK(sml::VectorIsZero(fp));

		//Static IsZero Function Check (m128)
		__m128 sse = _mm_setzero_ps();
		CHECK(sml::VectorIsZero(sse));

		//IsZero False Checks
		CHECK_FALSE(ImNotZero.IsZero());
		CHECK_FALSE(sml::VectorIsZero(randVecA));
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
		CHECK(sml::VectorIsEqual(NotZeroV2, ImNotZero));

		//Static Check: Vector vs Float Pointer
		CHECK(sml::VectorIsEqual(NotZeroV2, fp));
		CHECK(sml::VectorIsEqual(fp, NotZeroV2));

		//Static Check: Vector vs m128
		CHECK(sml::VectorIsEqual(NotZeroV2, m128));
		CHECK(sml::VectorIsEqual(m128, NotZeroV2));

		//Static Check: Float Pointer vs Float Pointer
		CHECK(sml::VectorIsEqual(fp, fp));

		//Static Check: m128 vs m128
		CHECK(sml::VectorIsEqual(m128, m128));

		//Static Check: Float Pointer vs m128
		CHECK(sml::VectorIsEqual(fp, m128));
		CHECK(sml::VectorIsEqual(m128, fp));

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
		CHECK_FALSE(sml::VectorIsEqual(randVecA, randVecB));
		CHECK_FALSE(sml::VectorIsEqual(randVecA, fp));
		CHECK_FALSE(sml::VectorIsEqual(fp, randVecB));
		CHECK_FALSE(sml::VectorIsEqual(randVecA, m128));
		CHECK_FALSE(sml::VectorIsEqual(m128, randVecB));
		CHECK_FALSE(sml::VectorIsEqual(randFPA, randFPB));
		CHECK_FALSE(sml::VectorIsEqual(randM128A, randM128B));
		CHECK_FALSE(sml::VectorIsEqual(randFPA, randM128B));
		CHECK_FALSE(sml::VectorIsEqual(randM128A, randFPB));
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
		answer[0]  = sml::VectorSet( 55457.96164f, 142416.94849f,  69813.91124f,  87456.52660f);
		answer[1]  = sml::VectorSet( 59983.88310f, 206507.27822f, 109854.26467f,  87576.12303f);
		answer[2]  = sml::VectorSet(156150.07383f, 281043.90000f, 142457.57959f, 118755.51654f);
		answer[3]  = sml::VectorSet(175552.92543f, 376006.00349f, 142774.17815f, 205587.84544f);
		answer[4]  = sml::VectorSet(268610.98788f, 447921.34789f, 144796.05915f, 252356.37492f);
		answer[5]  = sml::VectorSet(270183.66426f, 471313.98307f, 242454.77507f, 331910.23373f);
		answer[6]  = sml::VectorSet( 55457.96164f, 142416.94849f,  69813.91124f,  87456.52660f);
		answer[7]  = sml::VectorSet(112460.91405f, 166877.44789f,   2338.47956f, 133600.85838f);
		answer[8]  = sml::VectorSet( 40581.03150f, 111545.17473f, 109537.66611f,    743.79413f);
		answer[9]  = sml::VectorSet(115569.04233f, 169498.72527f,  32919.91348f, 118011.72241f);
		answer[10] = sml::VectorSet( 37627.78642f,  70847.48018f, 167156.02860f,  80178.05651f);
		answer[11] = sml::VectorSet( 97583.98391f, 136005.67413f,  42062.23443f,  46888.12591f);
		answer[12] = sml::VectorSet( 97738.86711f,  97929.25696f, 130262.03084f, 110733.25232f);
		answer[13] = sml::VectorSet(100692.11219f, 138626.95151f, 72643.668350f, 31298.989940f);
		answer[14] = sml::VectorSet( 94630.73883f,  95307.97958f,  99680.59692f, 126322.38829f);
		answer[15] = sml::VectorSet( 55457.96164f, 142416.94849f,  69813.91124f,  87456.52660f);
		answer[16] = sml::VectorSet(112460.91405f, 166877.44789f,   2338.47956f, 133600.85838f);
		answer[17] = sml::VectorSet( 40581.03150f, 111545.17473f, 109537.66611f,    743.79413f);
		answer[18] = sml::VectorSet(115569.04233f, 169498.72527f,  32919.91348f, 118011.72241f);
		answer[19] = sml::VectorSet( 37627.78642f,  70847.48018f, 167156.02860f,  80178.05651f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Member Method Add: Vector vs Vector ----------------------
		myVec.Add(randVecB);
		REQUIRE(myVec == answer[0]);

		//Member Method Add: Vector vs Float Pointer
		myVec.Add(randFPA);
		CHECK(myVec == answer[1]);

		//Member Method Add: Vector vs m128
		myVec.Add(randM128B);
		CHECK(myVec == answer[2]);

		//Member Operator+= sml::VectorAdd: Vector vs Vector ---------------------
		myVec += randVecA;
		CHECK(myVec == answer[3]);

		//Member Operator+= sml::VectorAdd: Vector vs Float Pointer
		myVec += randFPB;
		CHECK(myVec == answer[4]);

		//Member Operator+= sml::VectorAdd: Vector vs m128
		myVec += randM128A;
		CHECK(myVec == answer[5]);

		//Static Add: Vector vs Vector ---------------------------------
		myVec = sml::VectorAdd(randVecA, randVecB);
		CHECK(myVec == answer[6]);

		//Static Add: Vector vs FP
		myVec = sml::VectorAdd(randVecA, randFPB);
		CHECK(myVec == answer[7]);

		//Static Add: FP vs Vector
		myVec = sml::VectorAdd(randFPA, randVecB);
		CHECK(myVec == answer[8]);

		//Static Add: Vector vs m128
		myVec = sml::VectorAdd(randVecA, randM128B);
		CHECK(myVec == answer[9]);

		//Static Add: m128 vs Vector
		myVec = sml::VectorAdd(randM128A, randVecB);
		CHECK(myVec == answer[10]);

		//Static Add: Float Pointer & Float Pointer --------------------
		myVec = sml::VectorAdd(randFPA, randFPB);
		CHECK(myVec == answer[11]);

		//Static Sub: m128 & m128
		myVec = sml::VectorAdd(randM128A, randM128B);
		CHECK(myVec == answer[12]);

		//Static Sub: Float Pointer & m128
		myVec = sml::VectorAdd(randFPA, randM128B);
		CHECK(myVec == answer[13]);

		//Static Sub: m128 & Float Pointer
		myVec = sml::VectorAdd(randM128A, randFPB);
		CHECK(myVec == answer[14]);

		//Operator+ Add: Vector vs Vector ------------------------------
		myVec = randVecA + randVecB;
		CHECK(myVec == answer[15]);

		//Operator+ Add: Vector vs FP
		myVec = randVecA + randFPB;
		CHECK(myVec == answer[16]);

		//Operator+ Add: FP vs Vector
		myVec = randFPA + randVecB;
		CHECK(myVec == answer[17]);

		//Operator+ Add: Vector vs m128
		myVec = randVecA + randM128B;
		CHECK(myVec == answer[18]);

		//Operator+ Add: m128 vs Vector
		myVec = randM128A + randVecB;
		CHECK(myVec == answer[19]);
	}

	SECTION("Subtraction", "[Sub], [operator-], [operator-=]") {
		//Setup Answers for this section
		answer[0]  = sml::VectorSet( -16652.25844f,   47507.25849f,  -69180.71412f,   86208.13120f);
		answer[1]  = sml::VectorSet( -21178.17990f,  -16583.07124f, -109221.06755f,   86088.53477f);
		answer[2]  = sml::VectorSet( -22750.85628f,  -39975.70642f, -206879.78347f,    6534.67596f);
		answer[3]  = sml::VectorSet( -42153.70788f, -134937.80991f, -207196.38203f,  -80297.65294f);
		answer[4]  = sml::VectorSet(-135211.77033f, -206853.15431f, -209218.26303f, -127066.18242f);
		answer[5]  = sml::VectorSet(-231377.96106f, -281389.77609f, -241821.57795f, -158245.57593f);
		answer[6]  = sml::VectorSet( -16652.25844f,   47507.25849f,  -69180.71412f,   86208.13120f);
		answer[7]  = sml::VectorSet( -73655.21085f,   23046.75909f,   -1705.28244f,   40063.79942f);
		answer[8]  = sml::VectorSet( -31529.18858f,   16635.48473f,  -29456.95925f,    -504.60127f);
		answer[9]  = sml::VectorSet( -76763.33913f,   20425.48171f,  -32286.71636f,   55652.93539f);
		answer[10] = sml::VectorSet( -34482.43366f,  -24062.20982f,   28161.40324f,   78929.66111f);
		answer[11] = sml::VectorSet( -88532.14099f,   -7825.01467f,   38018.47243f,  -46648.93305f);
		answer[12] = sml::VectorSet( -94593.51435f,   -51143.9866f,   65055.40100f,   48374.46530f);
		answer[13] = sml::VectorSet( -91640.26927f,  -10446.29205f,   7437.038510f,  -31059.79708f);
		answer[14] = sml::VectorSet( -91485.38607f,  -48522.70922f,  95636.834920f,   32785.32933f);
		answer[15] = sml::VectorSet( -16652.25844f,   47507.25849f,  -69180.71412f,   86208.13120f);
		answer[16] = sml::VectorSet( -73655.21085f,   23046.75909f,   -1705.28244f,   40063.79942f);
		answer[17] = sml::VectorSet( -31529.18858f,   16635.48473f,  -29456.95925f,    -504.60127f);
		answer[18] = sml::VectorSet( -76763.33913f,   20425.48171f,  -32286.71636f,   55652.93539f);
		answer[19] = sml::VectorSet( -34482.43366f,  -24062.20982f,   28161.40324f,   78929.66111f);
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Member Method Sub: Vector vs Vector ----------------------
		myVec.Sub(randVecB);
		REQUIRE(myVec == answer[0]);

		//Member Method Sub: Vector vs Float Pointer
		myVec.Sub(randFPA);
		CHECK(myVec == answer[1]);

		//Member Method Sub: Vector vs m128
		myVec.Sub(randM128A);
		CHECK_FALSE(myVec == answer[2]);

		//Epsilon Change
		CHECK(myVec.IsEqual(answer[2], FLT_EPSILON * 2.50723899f));

		//Member Operator+= sml::VectorSub: Vector vs Vector ---------------------
		myVec -= randVecA;
		CHECK(myVec == answer[3]);

		//Member Operator+= sml::VectorSub: Vector vs Float Pointer
		myVec -= randFPB;
		CHECK(myVec == answer[4]);

		//Member Operator+= sml::VectorSub: Vector vs m128
		myVec -= randM128B;
		CHECK(myVec == answer[5]);

		//Static Sub: Vector vs Vector ---------------------------------
		myVec = sml::VectorSub(randVecA, randVecB);
		CHECK(myVec == answer[6]);

		//Static Sub: Vector vs FP
		myVec = sml::VectorSub(randVecA, randFPB);
		CHECK(myVec == answer[7]);

		//Static Sub: FP vs Vector
		myVec = sml::VectorSub(randFPA, randVecB);
		CHECK(myVec == answer[8]);

		//Static Sub: Vector vs m128
		myVec = sml::VectorSub(randVecA, randM128B);
		CHECK(myVec == answer[9]);

		//Static Sub: m128 vs Vector
		myVec = sml::VectorSub(randM128A, randVecB);
		CHECK(myVec == answer[10]);

		//Static Sub: Float Pointer & Float Pointer --------------------
		myVec = sml::VectorSub(randFPA, randFPB);
		CHECK(myVec == answer[11]);

		//Static Sub: m128 & m128
		myVec = sml::VectorSub(randM128A, randM128B);
		CHECK(myVec == answer[12]);

		//Static Sub: Float Pointer & m128
		myVec = sml::VectorSub(randFPA, randM128B);
		CHECK(myVec == answer[13]);

		//Static Sub: m128 & Float Pointer
		myVec = sml::VectorSub(randM128A, randFPB);
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
		answer[0] = sml::VectorSet(142416.9307440f,  697021.8396166f,   2323.8334304f,  637349.2941260f);
		answer[1] = sml::VectorSet(405888.2526204f, 1986512.2429073f,   6622.9252766f, 1816445.4882591f);
		answer[2] = sml::VectorSet( 55298.1270600f,  270641.9949465f,    902.3058960f,  247472.1373650f);
		answer[3] = sml::VectorSet(264644.5076936f,  348318.5623000f, 510110.2750712f,    4581.6111180f);
		answer[4] = sml::VectorSet( 12898.8761610f,  182657.4397305f, 114115.0072755f,     340.8498255f);
		answer[5] = sml::VectorSet(683046.1783830f,  527858.6278960f,  14840.6065400f,  343281.0063832f);
		answer[6] = sml::VectorSet(  4482.1276830f,   66669.0102630f, 278327.3403720f,  226728.4976085f);
		answer[7] = sml::VectorSet(705859.8399582f,  547098.8038652f, 239308.3315128f,  228856.7483634f);
		answer[8] = sml::VectorSet( 55298.1270600f,  270641.9949465f,    902.3058960f,  247472.1373650f);
		answer[9] = sml::VectorSet(264644.5076936f,  348318.5623000f, 510110.2750712f,    4581.6111180f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Mul Method Test
		myVec.Mul(randScalarA);
		REQUIRE(myVec == answer[0]);

		//Operator*= Test
		myVec *= randScalarB;
		CHECK(myVec == answer[1]);

		//Static Mul Test: Vector & Scalar
		myVec = sml::VectorMul(randVecA, randScalarB);
		CHECK(myVec == answer[2]);

		//Static Mul Test: Scalar & Vector
		myVec = sml::VectorMul(randScalarA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Mul Test: Float Pointer & Scalar
		myVec = sml::VectorMul(randFPA, randScalarB);
		CHECK(myVec == answer[4]);

		//Static Mul Test: Scalar & Float Pointer 
		myVec = sml::VectorMul(randScalarA, randFPB);
		CHECK(myVec == answer[5]);
		
		//Static Mul Test: m128 & Scalar
		myVec = sml::VectorMul(randM128A, randScalarB);
		CHECK(myVec == answer[6]);

		//Static Mul Test: Scalar & m128
		myVec = sml::VectorMul(randScalarA, randM128B);
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
		answer[0] = sml::VectorSet( 2643.4402724f, 12937.6162792f,    43.1333188f, 11830.0175613f);
		answer[1] = sml::VectorSet(  927.5229026f,  4539.5144839f,    15.1344978f,  4150.8833548f);
		answer[2] = sml::VectorSet( 6808.0181052f, 33320.0363122f,   111.0872140f, 30467.4838245f);
		answer[3] = sml::VectorSet( 1588.0426175f, 22487.8349929f, 14049.2468175f,    41.9636596f);
		answer[4] = sml::VectorSet(  551.8162736f,  8207.9421684f, 34266.2161122f, 27913.6346701f);
		answer[5] = sml::VectorSet( 6808.0181052f, 33320.0363122f,   111.0872140f, 30467.4838245f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Div Method Test
		myVec.Div(randScalarA);
		REQUIRE(myVec == answer[0]);

		//Operator/= Test
		myVec /= randScalarB;
		CHECK(myVec == answer[1]);

		//Static Mul Test: Vector & Scalar
		myVec = sml::VectorDiv(randVecA, randScalarB);
		CHECK(myVec == answer[2]);

		//Static Mul Test: Float Pointer & Scalar
		myVec = sml::VectorDiv(randFPA, randScalarB);
		CHECK(myVec == answer[3]);

		//Static Mul Test: m128 & Scalar
		myVec = sml::VectorDiv(randM128A, randScalarB);
		CHECK(myVec == answer[4]);

		//Operator/ Test: vec4 & Scalar
		myVec = randVecA / randScalarB;
		CHECK(myVec == answer[5]);
	}

	SECTION("Negate", "[Negate], [operator-]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet(-19402.85160f, -94962.10349f, -316.59856f, -86832.32890f);
		answer[1] = sml::VectorSet(-36055.11004f, -47454.84500f, -69497.31268f, -624.19770f);
		answer[2] = sml::VectorSet(-4525.92146f, -64090.32973f, -40040.35343f, -119.59643f);
		answer[3] = sml::VectorSet(-1572.67638, -23392.63518f, -97658.71592f, -79553.85881f);
		answer[4] = sml::VectorSet(1572.67638f, 23392.63518f, 97658.71592f, 79553.85881f);
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Negate Method Test
		myVec.Negate();
		REQUIRE(myVec == answer[0]);

		//Static Negate Test: Vector
		myVec = sml::VectorNegate(randVecB);
		CHECK(myVec == answer[1]);

		//Static Negate Test: Float Pointer
		myVec = sml::VectorNegate(randFPA);
		CHECK(myVec == answer[2]);

		//Static Negate Test: m128
		myVec = sml::VectorNegate(randM128A);
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
		answer[0] = sml::VectorSet(19402.85160f, 47454.84500f,   316.59856f,   624.19770f);
		answer[1] = sml::VectorSet(19402.85160f, 47454.84500f,   316.59856f,   624.19770f);
		answer[2] = sml::VectorSet(19402.85160f, 71915.34440f,   316.59856f, 46768.52948f);
		answer[3] = sml::VectorSet( 4525.92146f, 47454.84500f, 40040.35343f,   119.59643f);
		answer[4] = sml::VectorSet(19402.85160f, 74536.62178f,   316.59856f, 31179.39351f);
		answer[5] = sml::VectorSet( 1572.67638f, 23392.63518f, 69497.31268f,   624.19770f);
		answer[6] = sml::VectorSet( 4525.92146f, 64090.32973f,  2021.88100f,   119.59643f);
		answer[7] = sml::VectorSet( 1572.67638f, 23392.63518f, 32603.31492f, 31179.39351f);
		answer[8] = sml::VectorSet( 4525.92146f, 64090.32973f, 32603.31492f,   119.59643f);
		answer[9] = sml::VectorSet( 1572.67638f, 23392.63518f,  2021.88100f, 46768.52948f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Min Method Test
		myVec.Min(randVecB);
		REQUIRE(myVec == answer[0]);

		//Static Min Test: Vector & Vector
		myVec = Min(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Min Test: Vector & Float Pointer
		myVec = Min(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Min Test: Float Pointer & Vector
		myVec = Min(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Min Test: Vector & m128
		myVec = Min(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Min Test: m128 & Vector
		myVec = Min(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Min Test: Float Pointer & Float Pointer
		myVec = Min(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Min Test: m128 & m128
		myVec = Min(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Min Test: Float Pointer & m128
		myVec = Min(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Min Test: m128 & Float Pointer
		myVec = Min(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Maximum Value [Per Component]", "[Max]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet(36055.11004f, 94962.10349f, 69497.31268f, 86832.32890f);
		answer[1] = sml::VectorSet(36055.11004f, 94962.10349f, 69497.31268f, 86832.32890f);
		answer[2] = sml::VectorSet(93058.06245f, 94962.10349f,  2021.88100f, 86832.32890f);
		answer[3] = sml::VectorSet(36055.11004f, 64090.32973f, 69497.31268f,   624.19770f);
		answer[4] = sml::VectorSet(96166.19073f, 94962.10349f, 32603.31492f, 86832.32890f);
		answer[5] = sml::VectorSet(36055.11004f, 47454.84500f, 97658.71592f, 79553.85881f);
		answer[6] = sml::VectorSet(93058.06245f, 71915.34440f, 40040.35343f, 46768.52948f);
		answer[7] = sml::VectorSet(96166.19073f, 74536.62178f, 97658.71592f, 79553.85881f);
		answer[8] = sml::VectorSet(96166.19073f, 74536.62178f, 40040.35343f, 31179.39351f);
		answer[9] = sml::VectorSet(93058.06245f, 71915.34440f, 97658.71592f, 79553.85881f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Max Method Test
		myVec.Max(randVecB);
		REQUIRE(myVec == answer[0]);

		//Static Max Test: Vector & Vector
		myVec = Max(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Max Test: Vector & Float Pointer
		myVec = Max(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Max Test: Float Pointer & Vector
		myVec = Max(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Max Test: Vector & m128
		myVec = Max(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Max Test: m128 & Vector
		myVec = Max(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Max Test: Float Pointer & Float Pointer
		myVec = Max(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Max Test: m128 & m128
		myVec = Max(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Max Test: Float Pointer & m128
		myVec = Max(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Max Test: m128 & Float Pointer
		myVec = Max(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Average Value [Per Component]", "[Avg]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet( 27728.98082f, 71208.474245f, 34906.955620f, 43728.263300f);
		answer[1] = sml::VectorSet( 27728.98082f, 71208.474245f, 34906.955620f, 43728.263300f);
		answer[2] = sml::VectorSet(56230.457025f, 83438.723945f,  1169.239780f, 66800.429190f);
		answer[3] = sml::VectorSet( 20290.51575f, 55772.587365f, 54768.833055f,   371.897065f);
		answer[4] = sml::VectorSet(57784.521165f, 84749.362635f, 16459.956740f, 59005.861205f);
		answer[5] = sml::VectorSet(18813.893210f, 35423.740090f, 83578.014300f, 40089.028255f);
		answer[6] = sml::VectorSet(48791.991955f, 68002.837065f, 21031.117215f, 23444.062955f);
		answer[7] = sml::VectorSet(48869.433555f, 48964.628480f, 65131.015420f, 55366.626160f);
		answer[8] = sml::VectorSet(50346.056095f, 69313.475755f, 36321.834175f, 15649.494970f);
		answer[9] = sml::VectorSet(47315.369415f, 47653.989790f, 49840.298460f, 63161.194145f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Average Method Test
		myVec.Average(randVecB);
		REQUIRE(myVec == answer[0]);

		//Static Average Test: Vector & Vector
		myVec = Average(randVecA, randVecB);
		CHECK(myVec == answer[1]);

		//Static Average Test: Vector & Float Pointer
		myVec = Average(randVecA, randFPB);
		CHECK(myVec == answer[2]);

		//Static Average Test: Float Pointer & Vector
		myVec = Average(randFPA, randVecB);
		CHECK(myVec == answer[3]);

		//Static Average Test: Vector & m128
		myVec = Average(randVecA, randM128B);
		CHECK(myVec == answer[4]);

		//Static Average Test: m128 & Vector
		myVec = Average(randM128A, randVecB);
		CHECK(myVec == answer[5]);

		//Static Average Test: Float Pointer & Float Pointer
		myVec = Average(randFPA, randFPB);
		CHECK(myVec == answer[6]);

		//Static Average Test: m128 & m128
		myVec = Average(randM128A, randM128B);
		CHECK(myVec == answer[7]);

		//Static Average Test: Float Pointer & m128
		myVec = Average(randFPA, randM128B);
		CHECK(myVec == answer[8]);

		//Static Average Test: m128 & Float Pointer
		myVec = Average(randM128A, randFPB);
		CHECK(myVec == answer[9]);
	}

	SECTION("Vector Length Squared", "[LengthSq]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[4] = {
			16934225326.3030620f,
			 8382199366.4809078f,
			 5731298536.0675919f,
			16415729938.3654595f
		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Length Squared Method Test
		vecAns = myVec.LengthSq();
		REQUIRE( near_equal(vecAns, fAnswer[0]) );

		//Static Length Squared Test: Vector
		vecAns = LengthSq(randVecB);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Static Length Squared Test: Float Pointer
		vecAns = LengthSq(randFPA);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Length Squared Test: m128
		vecAns = LengthSq(randM128A);
		CHECK(near_equal(vecAns, fAnswer[3]));
	}
	
	SECTION("Vector Length", "[Length]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[4] = {
			130131.569291632f,
			 91554.351980017f,
			126582.001483696f,
			129764.305374465f
		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Length Squared Method Test
		vecAns = myVec.Length();
		REQUIRE(near_equal(vecAns, fAnswer[0]));

		//Static Length Squared Test: Vector
		vecAns = Length(randVecB);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Static Length Squared Test: Float Pointer
		vecAns = Length(randFPB);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Length Squared Test: m128
		vecAns = Length(randM128B);
		CHECK(near_equal(vecAns, fAnswer[3]));
	}
}

TEST_CASE("Vector Math Functions", "[Dot], [Cross], [Normalize], [Homogenize], [AngleBetween], [Component], [Project], [Reflect]") {
	//PreReq Check
	REQUIRE(chk1 == chk2);
	
	//Answer Array Setup
	vec4 answer[20] = {};

	SECTION("Dot Product Test", "[Dot], [Operator*]") {
		//Setup Answers for this section
		float vecAns = 1.0f;
		float fAnswer[17] = {
			 5282187140.623080384f,
			 6197029861.752973981f,
			 9190693691.568743670f,
			 5282187140.623080384f, 
			12696484611.922471708f,
			 5987350873.567694011f,
			11661754233.656577634f, 
			 8003472548.461516557f,
			 5116801796.106543775f,
			 7559285236.463376027f,
			 6521494489.731612930f,
			 5746710925.383224161f,
			 5282187140.623080384f,
			12696484611.922471708f,
			 5987350873.567694011f,
			11661754233.656577634f,
			 8003472548.461516557f,
		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Dot Product Method Test: Vector
		vecAns = myVec.Dot(randVecB);
		REQUIRE(near_equal(vecAns, fAnswer[0]));

		//Dot Product Method Test: Float Pointer
		vecAns = myVec.Dot(randFPA);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Dot Product Method Test: m128
		vecAns = myVec.Dot(randM128A);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Dot Product Test: Vector & Vector
		vecAns = Dot(randVecA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[3]));
		
		//Static Dot Product Test: Vector & Float Pointer
		vecAns = Dot(randVecA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[4]));

		//Static Dot Product Test: Float Pointer & Vector
		vecAns = Dot(randFPA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[5]));

		//Static Dot Product Test: Vector & m128
		vecAns = Dot(randVecA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[6]));

		//Static Dot Product Test: m128 & Vector
		vecAns = Dot(randM128A, randVecB);
		CHECK(near_equal(vecAns, fAnswer[7]));

		//Static Dot Product Test: Float Pointer & Float Pointer
		vecAns = Dot(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[8]));

		//Static Dot Product Test: m128 & m128
		vecAns = Dot(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[9]));

		//Static Dot Product Test: Float Pointer & m128
		vecAns = Dot(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[10]));

		//Static Dot Product Test: m128 & Float Pointer
		vecAns = Dot(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[11]));

		//Operator* Test: Vector & Vector
		vecAns = randVecA * randVecB;
		CHECK(near_equal(vecAns, fAnswer[12]));
		
		//Operator* Test: Vector & Float Pointer
		vecAns = randVecA * randFPB;
		CHECK(near_equal(vecAns, fAnswer[13]));

		//Operator* Test: Float Pointer & Vector
		vecAns = randFPA * randVecB;
		CHECK(near_equal(vecAns, fAnswer[14]));

		//Operator* Test: Vector & m128
		vecAns = randVecA * randM128B;
		CHECK(near_equal(vecAns, fAnswer[15]));

		//Operator* Test: m128 & Vector
		vecAns = randM128A * randVecB;
		CHECK(near_equal(vecAns, fAnswer[16]));
	}

	SECTION("Cross Product Test", "[Cross], [Operator^]") {
		//Setup Answers for this section
		answer[0]  = sml::VectorSet( 0.742037332f, -0.150674138f, -0.282083134f, 0.0f);
		answer[1]  = sml::VectorSet( 0.159113879f, -0.409325970f,  0.637199657f, 0.0f);
		answer[2]  = sml::VectorSet(-0.546430804f, -0.144739851f,  0.043469805f, 0.0f);
		answer[3]  = sml::VectorSet(-0.043062441f,  0.010486891f, -0.506392274f, 0.0f);
		answer[4]  = sml::VectorSet( 0.309785247f, -0.399886951f, -0.034624698f, 0.0f);
		answer[5]  = sml::VectorSet(-0.083015257f, -0.106616827f,  0.488604282f, 0.0f);
		answer[6]  = sml::VectorSet( 0.742037332f, -0.150674138f, -0.282083134f, 0.0f);
		answer[7]  = sml::VectorSet( 0.014844052f, -0.000856801f, -0.652729601f, 0.0f);
		answer[8]  = sml::VectorSet( 0.368489821f,  0.162909051f, -0.302411187f, 0.0f);
		answer[9]  = sml::VectorSet( 0.251659389f, -0.049320726f, -0.629534898f, 0.0f);
		answer[10] = sml::VectorSet(-0.327208209f,  0.371052520f, -0.083610597f, 0.0f);
		answer[11] = sml::VectorSet(-0.308812887f,  0.417404713f, -0.633209766f, 0.0f);
		answer[12] = sml::VectorSet(-0.515099653f,  0.738302691f, -0.168553930f, 0.0f);
		answer[13] = sml::VectorSet(-0.093845581f,  0.388312880f, -0.610942729f, 0.0f);
		answer[14] = sml::VectorSet(-0.590497562f,  0.769012140f, -0.174695711f, 0.0f);
		answer[15] = sml::VectorSet( 0.742037332f, -0.150674138f, -0.282083134f, 0.0f);
		answer[16] = sml::VectorSet( 0.014844052f, -0.000856801f, -0.652729601f, 0.0f);
		answer[17] = sml::VectorSet( 0.368489821f,  0.162909051f, -0.302411187f, 0.0f);
		answer[18] = sml::VectorSet( 0.251659389f, -0.049320726f, -0.629534898f, 0.0f);
		answer[19] = sml::VectorSet(-0.327208209f,  0.371052520f, -0.083610597f, 0.0f);

		//Another Setup: 3D Vector [x, y, z, 0] Normalized
		vec4 randVecA_3D = randVecA;
		randVecA_3D.w = 0.0f;
		randVecA_3D.Normalize();

		vec4 randVecB_3D = randVecB;
		randVecB_3D.w = 0.0f;
		randVecB_3D.Normalize();

		vec4 randFPAVec_3D = randFPA;
		randFPAVec_3D.w = 0.0f;
		randFPAVec_3D.Normalize();

		vec4 randFPBVec_3D = randFPB;
		randFPBVec_3D.w = 0.0f;
		randFPBVec_3D.Normalize();

		vec4 randM128AVec_3D = randM128A;
		randM128AVec_3D.w = 0.0f;
		randM128AVec_3D.Normalize();

		vec4 randM128BVec_3D = randM128B;
		randM128BVec_3D.w = 0.0f;
		randM128BVec_3D.Normalize();

		//Last Setup: pseudo-names
		float* randFPA_3D = randFPAVec_3D.e;
		float* randFPB_3D = randFPBVec_3D.e;
		__m128 randM128A_3D = randM128AVec_3D.m128;
		__m128 randM128B_3D = randM128BVec_3D.m128;

		//Setup Copy Vector to use
		vec4 myVec = randVecA_3D;

		//Cross Product Method Test: Vector
		myVec.Cross(randVecB_3D);
		REQUIRE(myVec == answer[0]);

		//Cross Product Method Test: Float Pointer
		myVec.Cross(randFPA_3D);
		CHECK(myVec == answer[1]);

		//Cross Product Method Test: m128
		myVec.Cross(randM128A_3D);
		CHECK(myVec == answer[2]);

		//Operator^= Test: Vector
		myVec ^= randVecA_3D;
		CHECK(myVec == answer[3]);

		//Operator^= Test: Float Pointer
		myVec ^= randFPB_3D;
		CHECK(myVec == answer[4]);

		//Operator^= Test: m128
		myVec ^= randM128B_3D;
		CHECK(myVec == answer[5]);

		//Static Cross Product Test: Vector & Vector
		myVec = Cross(randVecA_3D, randVecB_3D);
		CHECK(myVec == answer[6]);
		
		//Static Cross Product Test: Vector & Float Pointer
		myVec = Cross(randVecA_3D, randFPB_3D);
		CHECK(myVec == answer[7]);

		//Static Cross Product Test: Float Pointer & Vector
		myVec = Cross(randFPA_3D, randVecB_3D);
		CHECK(myVec == answer[8]);

		//Static Cross Product Test: Vector & m128
		myVec = Cross(randVecA_3D, randM128B_3D);
		CHECK(myVec == answer[9]);

		//Static Cross Product Test: m128 & Vector
		myVec = Cross(randM128A_3D, randVecB_3D);
		CHECK(myVec == answer[10]);

		//Static Cross Product Test: Float Pointer & Float Pointer
		myVec = Cross(randFPA_3D, randFPB_3D);
		CHECK(myVec == answer[11]);

		//Static Cross Product Test: m128 & m128
		myVec = Cross(randM128A_3D, randM128B_3D);
		CHECK(myVec == answer[12]);

		//Static Cross Product Test: Float Pointer & m128
		myVec = Cross(randFPA_3D, randM128B_3D);
		CHECK(myVec == answer[13]);

		//Static Cross Product Test: m128 & Float Pointer
		myVec = Cross(randM128A_3D, randFPB_3D);
		CHECK(myVec == answer[14]);

		//operator^ Test: Vector & Vector
		myVec = randVecA_3D ^ randVecB_3D;
		CHECK(myVec == answer[15]);
		
		//operator^ Test: Vector & Float Pointer
		myVec = randVecA_3D ^ randFPB_3D;
		CHECK(myVec == answer[16]);

		//operator^ Test: Float Pointer & Vector
		myVec = randFPA_3D ^ randVecB_3D;
		CHECK(myVec == answer[17]);

		//operator^ Test: Vector & m128
		myVec = randVecA_3D ^ randM128B_3D;
		CHECK(myVec == answer[18]);

		//operator^ Test: m128 & Vector
		myVec = randM128A_3D ^ randVecB_3D;
		CHECK(myVec == answer[19]);
	}

	SECTION("Normalize Test", "[Normalize]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet(0.149101802f, 0.729739170f, 0.002432911f, 0.667265670f);
		answer[1] = sml::VectorSet(0.393810990f, 0.518324295f, 0.759082568f, 0.006817782f);
		answer[2] = sml::VectorSet(0.059783384f, 0.846576074f, 0.528897344f, 0.001579762f);
		answer[3] = sml::VectorSet(0.012274654f, 0.182578253f, 0.762221000f, 0.620913569f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Normalize Method Test
		myVec.Normalize();
		REQUIRE(myVec == answer[0]);

		//Static Normalize Function Check: Vector
		myVec = Normalize(randVecB);
		CHECK(myVec == answer[1]);

		//Static Normalize Function Check: Float Pointer
		myVec = Normalize(randFPA);
		CHECK(myVec == answer[2]);

		//Static Normalize Function Check: m128
		myVec = Normalize(randM128A);
		CHECK(myVec == answer[3]);
	}

	SECTION("Homogenize Test", "[Homogenize]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet( 0.223451931f,  1.093626126f,   0.003646090f, 1.0f);
		answer[1] = sml::VectorSet(57.762324404f, 76.025344213f, 111.338623452f, 1.0f);
		answer[2] = sml::VectorSet( 1.989758144f,  1.537686670f,   0.043231656f, 1.0f);
		answer[3] = sml::VectorSet( 3.084286764f,  2.390573176f,   1.045668669f, 1.0f);
		
		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Homogenize Method Test
		myVec.Homogenize();
		REQUIRE(myVec == answer[0]);

		//Static Homogenize Function Check: Vector
		myVec = Homogenize(randVecB);
		CHECK(myVec == answer[1]);

		//Static Homogenize Function Check: Vector
		myVec = Homogenize(randFPB);
		CHECK(myVec == answer[2]);

		//Static Homogenize Function Check: Vector
		myVec = Homogenize(randM128B);
		CHECK(myVec == answer[3]);
	}

	SECTION("Angle Between Vector Test", "[AngleBetween]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[12] = {
			1.111457545f,
			0.890485846f,
			0.986954532f,
			1.111457545f,
			0.690736164f,
			0.527969400f,
			0.808479323f,
			0.819905130f,
			1.007531596f,
			1.098795731f,
			0.844850650f,
			1.208590667f
		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Angle Between Method Test: Vector
		vecAns = myVec.AngleBetween(randVecB);
		REQUIRE(near_equal(vecAns, fAnswer[0]));

		//Angle Between Method Test: Float Pointer
		vecAns = myVec.AngleBetween(randFPA);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Angle Between Method Test: m128
		vecAns = myVec.AngleBetween(randM128A);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Angle Between Test: Vector & Vector
		vecAns = AngleBetween(randVecA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[3]));
		
		//Static Angle Between Test: Vector & Float Pointer
		vecAns = AngleBetween(randVecA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[4]));

		//Static Angle Between Test: Float Pointer & Vector
		vecAns = AngleBetween(randFPA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[5]));

		//Static Angle Between Test: Vector & m128
		vecAns = AngleBetween(randVecA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[6]));

		//Static Angle Between Test: m128 & Vector
		vecAns = AngleBetween(randM128A, randVecB);
		CHECK(near_equal(vecAns, fAnswer[7]));

		//Static Angle Between Test: Float Pointer & Float Pointer
		vecAns = AngleBetween(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[8]));

		//Static Angle Between Test: m128 & m128
		vecAns = AngleBetween(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[9]));

		//Static Angle Between Test: Float Pointer & m128
		vecAns = AngleBetween(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[10]));

		//Static Angle Between Test: m128 & Float Pointer
		vecAns = AngleBetween(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[11]));
	}

	SECTION("Component Test", "[Component]") {
		//Setup Answers for this section
		float vecAns = 1;
		float fAnswer[12] = {
			 57694.550028336f,
			 81857.235496135f,
			 71732.867629845f,
			 57694.550028336f,
			100302.447923908f,
			 65396.682343123f,
			 89868.737015189f,
			 87417.718277426f,
			 40422.822645647f,
			 58253.964483139f,
			 50256.458977006f,
			 45399.115656449f
		};

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Component Method Test: Vector
		vecAns = myVec.Component(randVecB);
		REQUIRE(near_equal(vecAns, fAnswer[0]));

		//Component Method Test: Float Pointer
		vecAns = myVec.Component(randFPA);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Component Method Test: m128
		vecAns = myVec.Component(randM128A);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Component Test: Vector & Vector
		vecAns = Component(randVecA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[3]));
		
		//Static Component Test: Vector & Float Pointer
		vecAns = Component(randVecA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[4]));

		//Static Component Test: Float Pointer & Vector
		vecAns = Component(randFPA, randVecB);
		CHECK(near_equal(vecAns, fAnswer[5]));

		//Static Component Test: Vector & m128
		vecAns = Component(randVecA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[6]));

		//Static Component Test: m128 & Vector
		vecAns = Component(randM128A, randVecB);
		CHECK(near_equal(vecAns, fAnswer[7]));

		//Static Component Test: Float Pointer & Float Pointer
		vecAns = Component(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[8]));

		//Static Component Test: m128 & m128
		vecAns = Component(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[9]));

		//Static Component Test: Float Pointer & m128
		vecAns = Component(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[10]));

		//Static Component Test: m128 & Float Pointer
		vecAns = Component(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[11]));
	}

	SECTION("Project Test", "[Project]") {
		//Setup Answers for this section
		answer[0] = sml::VectorSet(22720.747894474f, 29904.487003928f, 43794.927237608f,   393.348919536f);
		answer[1] = sml::VectorSet( 2979.507544385f, 42191.987342330f, 26359.391381165f,    78.732799191f);
		answer[2] = sml::VectorSet(  342.223246538f,  5090.369295423f, 21251.087153047f, 17311.368176471f);
		answer[3] = sml::VectorSet(22720.747894474f, 29904.487003928f, 43794.927237608f,   393.348919536f);
		answer[4] = sml::VectorSet(73738.377916177f, 56985.076883461f,  1602.120454201f, 37058.965237247f);
		answer[5] = sml::VectorSet(25753.932250504f, 33896.689310678f, 49641.481619864f,   445.860385917f);
		answer[6] = sml::VectorSet(66600.241719226f, 51620.605847018f, 22579.543164151f, 21593.401263600f);
		answer[7] = sml::VectorSet(34426.058224149f, 45310.727249911f, 66357.266143115f,   595.995029268f);
		answer[8] = sml::VectorSet(29717.254507533f, 22965.517831192f, 645.66949578634f, 14935.108865467f);
		answer[9] = sml::VectorSet(43171.054190119f, 33461.079341774f, 14636.323478182f, 13997.094785780f);
		answer[10] = sml::VectorSet(37244.234502319f, 28867.311884893f, 12626.948173945f, 12075.477199538f);
		answer[11] = sml::VectorSet(33375.627580646f, 25792.711440966f, 725.15530080633f, 16773.710749218f);

		//Setup Copy Vector to use
		vec4 myVec = randVecA;

		//Project Method Test: Vector
		myVec.Project(randVecB);
		REQUIRE(myVec == answer[0]);

		//Project Method Test: Float Pointer
		myVec.Project(randFPA);
		CHECK(myVec == answer[1]);

		//Project Method Test: m128
		myVec.Project(randM128A);
		CHECK(myVec == answer[2]);

		//Static Project Test: Vector & Vector
		myVec = Project(randVecA, randVecB);
		CHECK(myVec == answer[3]);
		
		//Static Project Test: Vector & Float Pointer
		myVec = Project(randVecA, randFPB);
		CHECK(myVec == answer[4]);

		//Static Project Test: Float Pointer & Vector
		myVec = Project(randFPA, randVecB);
		CHECK(myVec == answer[5]);

		//Static Project Test: Vector & m128
		myVec = Project(randVecA, randM128B);
		CHECK(myVec == answer[6]);

		//Static Project Test: m128 & Vector
		myVec = Project(randM128A, randVecB);
		CHECK(myVec == answer[7]);

		//Static Project Test: Float Pointer & Float Pointer
		myVec = Project(randFPA, randFPB);
		CHECK(myVec == answer[8]);

		//Static Project Test: m128 & m128
		myVec = Project(randM128A, randM128B);
		CHECK(myVec == answer[9]);

		//Static Project Test: Float Pointer & m128
		myVec = Project(randFPA, randM128B);
		CHECK(myVec == answer[10]);

		//Static Project Test: m128 & Float Pointer
		myVec = Project(randM128A, randFPB);
		CHECK(myVec == answer[11]);
	}

	SECTION("Reflect Test", "[Reflect]") {
		//Setup Answers for this section
		answer[0]  = sml::VectorSet( 0.263859410f, -0.368988776f,  0.891193298f, 0.0f);
		answer[1]  = sml::VectorSet(-0.242965411f,  0.664862956f, -0.706346273f, 0.0f);
		answer[2]  = sml::VectorSet( 0.226186077f, -0.914445657f, -0.335602439f, 0.0f);
		answer[3]  = sml::VectorSet( 0.263859410f, -0.368988776f,  0.891193298f, 0.0f);
		answer[4]  = sml::VectorSet( 0.998304991f, -0.053558586f,  0.022773259f, 0.0f);
		answer[5]  = sml::VectorSet( 0.620613468f,  0.048944493f,  0.782587605f, 0.0f);
		answer[6]  = sml::VectorSet( 0.919689477f, -0.111758769f,  0.376405688f, 0.0f);
		answer[7]  = sml::VectorSet( 0.665667779f,  0.663828928f,  0.340906968f, 0.0f);
		answer[8]  = sml::VectorSet( 0.848413913f, -0.144721481f, -0.509165517f, 0.0f);
		answer[9]  = sml::VectorSet( 0.597331600f,  0.242201118f, -0.764547956f, 0.0f);
		answer[10] = sml::VectorSet( 0.983832565f, -0.037689804f, -0.175079873f, 0.0f);
		answer[11] = sml::VectorSet( 0.255711896f, -0.023200824f, -0.966474597f, 0.0f);

		//Another Setup: 3D Vector [x, y, z, 0] Normalized
		vec4 randVecA_3D = randVecA;
		randVecA_3D.w = 0.0f;
		randVecA_3D.Normalize();

		vec4 randVecB_3D = randVecB;
		randVecB_3D.w = 0.0f;
		randVecB_3D.Normalize();

		vec4 randFPAVec_3D = randFPA;
		randFPAVec_3D.w = 0.0f;
		randFPAVec_3D.Normalize();

		vec4 randFPBVec_3D = randFPB;
		randFPBVec_3D.w = 0.0f;
		randFPBVec_3D.Normalize();

		vec4 randM128AVec_3D = randM128A;
		randM128AVec_3D.w = 0.0f;
		randM128AVec_3D.Normalize();

		vec4 randM128BVec_3D = randM128B;
		randM128BVec_3D.w = 0.0f;
		randM128BVec_3D.Normalize();

		//Last Setup: pseudo-names
		float* randFPA_3D = randFPAVec_3D.e;
		float* randFPB_3D = randFPBVec_3D.e;
		__m128 randM128A_3D = randM128AVec_3D.m128;
		__m128 randM128B_3D = randM128BVec_3D.m128;

		//Setup Copy Vector to use
		vec4 myVec = randVecA_3D;

		//Reflect Method Test: Vector
		myVec.Reflect(randVecB_3D);
		REQUIRE(myVec == answer[0]);

		//Reflect Method Test: Float Pointer
		myVec.Reflect(randFPA_3D);
		CHECK(myVec == answer[1]);

		//Reflect Method Test: m128
		myVec.Reflect(randM128A_3D);
		CHECK(myVec.IsEqual(answer[2], FLT_EPSILON * 2.25f));

		//Static Reflect Test: Vector & Vector
		myVec = Reflect(randVecA_3D, randVecB_3D);
		CHECK(myVec == answer[3]);
		
		//Static Reflect Test: Vector & Float Pointer
		myVec = Reflect(randVecA_3D, randFPB_3D);
		CHECK(myVec == answer[4]);

		//Static Reflect Test: Float Pointer & Vector
		myVec = Reflect(randFPA_3D, randVecB_3D);
		CHECK(myVec == answer[5]);

		//Static Reflect Test: Vector & m128
		myVec = Reflect(randVecA_3D, randM128B_3D);
		CHECK(myVec == answer[6]);

		//Static Reflect Test: m128 & Vector
		myVec = Reflect(randM128A_3D, randVecB_3D);
		CHECK(myVec == answer[7]);

		//Static Reflect Test: Float Pointer & Float Pointer
		myVec = Reflect(randFPA_3D, randFPB_3D);
		CHECK(myVec == answer[8]);

		//Static Reflect Test: m128 & m128
		myVec = Reflect(randM128A_3D, randM128B_3D);
		CHECK(myVec == answer[9]);

		//Static Reflect Test: Float Pointer & m128
		myVec = Reflect(randFPA_3D, randM128B_3D);
		CHECK(myVec == answer[10]);

		//Static Reflect Test: m128 & Float Pointer
		myVec = Reflect(randM128A_3D, randFPB_3D);
		CHECK(myVec == answer[11]);
	}
}
