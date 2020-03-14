#include "catch2.hpp"
#include "../include/ssemath.h"

namespace {
	const float randFPA[4] = { 4525.92146f, 64090.32973f, 40040.35343f, 119.59643f };
	const float randFPB[4] = { 93058.06245f, 71915.34440f, 2021.88100f, 46768.52948f };
	const __m128 randM128A = _mm_set_ps(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
	const __m128 randM128B = _mm_set_ps(31179.39351f, 32603.31492f, 74536.62178f, 96166.19073f);
	const float randScalarA = 7.34f;
	const float randScalarB = 2.85f;

	float rand_num() {
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 100.0f);
	}

	bool near_equal(float x, float y, float relValue = 0.00001f) {
		float diff = fabs(x - y);
		float A = fabs(x); float B = fabs(y);
		float length = (A > B ? A : B)* relValue;
		return diff <= length;
	}
}

TEST_CASE("SSE Base: Set & Equality Check", "[Set] [IsZero] [IsEqual]") {
	//Using the namespace sml (SSE Math Library)
	using namespace sml;
	
	SECTION("Set & IsEqual", "[Set] [Equal]") {
		float trueRandA[4] = { rand_num(), rand_num(), rand_num(), rand_num() };
		__m128 trueRandM128 = Set(trueRandA);
		__m128 randM128Set = Set(79553.85881f, 97658.71592f, 23392.63518f, 1572.67638f);
		__m128 trueM128Set = _mm_shuffle_ps(randM128A, randM128A, 0x1B); //0x1B = 00 01 10 11, or 0 1 2 3.

		__m128 Dupe = Set(randFPB);
		const float* DupeFP = randFPA;

		CHECK(IsEqual(trueRandA, trueRandM128));
		CHECK_FALSE(IsEqual(randM128Set, randM128A));
		CHECK(IsEqual(randM128Set, trueM128Set));
		CHECK_FALSE(IsEqual(randM128A, randM128B));
		CHECK(IsEqual(randFPB, Dupe));
		CHECK(IsEqual(DupeFP, randFPA));
	}
}

TEST_CASE("SSE Base: Basic Vector Math", "[Add], [Sub], [Mul], [Div]") {
	//Using the namespace sml (SSE Math Library)
	using namespace sml;

	//Answer Array
	__m128 answer[4];

	SECTION("Addition", "[Add]") {
		answer[0] = Set(97583.98391f, 136005.67413f, 42062.23443f, 46888.12591f);
		answer[1] = Set(97738.86711f, 97929.25696f, 130262.03084f, 110733.25232f);
		answer[2] = Set(100692.11219f, 138626.95151f, 72643.668350f, 31298.989940f);
		answer[3] = Set(94630.73883f, 95307.97958f, 99680.59692f, 126322.38829f);

		__m128 myVec;
		myVec = Add(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Add(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Add(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Add(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Subtraction", "[Sub]") {
		answer[0] = Set(-88532.14099f, -7825.01467f, 38018.47243f, -46648.93305f);
		answer[1] = Set(-94593.51435f, -51143.9866f, 65055.40100f, 48374.46530f);
		answer[2] = Set(-91640.26927f, -10446.29205f, 7437.038510f, -31059.79708f);
		answer[3] = Set(-91485.38607f, -48522.70922f, 95636.834920f, 32785.32933f);

		__m128 myVec;
		myVec = Sub(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Sub(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Sub(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Sub(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Scalar Multiply", "[Sub]") {
		answer[0] = Set(12898.8761610f, 182657.4397305f, 114115.0072755f, 340.8498255f);
		answer[1] = Set(683046.1783830f, 527858.6278960f, 14840.6065400f, 343281.0063832f);
		answer[2] = Set(4482.1276830f, 66669.0102630f, 278327.3403720f, 226728.4976085f);
		answer[3] = Set(705859.8399582f, 547098.8038652f, 239308.3315128f, 228856.7483634f);

		__m128 myVec;
		myVec = Mul(randFPA, randScalarB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Mul(randScalarA, randFPB);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Mul(randM128A, randScalarB);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Mul(randScalarA, randM128B);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Scalar Divide", "[Div]") {
		answer[0] = Set(1588.0426175f, 22487.8349929f, 14049.2468175f, 41.9636596f);
		answer[1] = Set(551.8162736f, 8207.9421684f, 34266.2161122f, 27913.6346701f);

		__m128 myVec;
		myVec = Div(randFPA, randScalarB);
		CHECK(IsEqual(myVec, answer[0]));

		myVec = Div(randM128A, randScalarB);
		CHECK(IsEqual(myVec, answer[1]));
	}

	SECTION("Negate", "[Negate]") {
		answer[0] = Set(-4525.92146f, -64090.32973f, -40040.35343f, -119.59643f);
		answer[1] = Set(-1572.67638, -23392.63518f, -97658.71592f, -79553.85881f);

		__m128 myVec;
		myVec = Negate(randFPA);
		CHECK(IsEqual(myVec, answer[0]));

		myVec = Negate(randM128A);
		CHECK(IsEqual(myVec, answer[1]));
	}

}

TEST_CASE("SSE Base: Basic Normal Math Functions", "[Min] [Max] [Average] [Length] [LengthSq]") {
	//Using the namespace sml (SSE Math Library)
	using namespace sml;

	//Answer Array
	__m128 answer[4];

	SECTION("Minimum Value (Per Component)", "[Min]") {
		answer[0] = Set(4525.92146f, 64090.32973f, 2021.88100f, 119.59643f);
		answer[1] = Set(1572.67638f, 23392.63518f, 32603.31492f, 31179.39351f);
		answer[2] = Set(4525.92146f, 64090.32973f, 32603.31492f, 119.59643f);
		answer[3] = Set(1572.67638f, 23392.63518f, 2021.88100f, 46768.52948f);

		__m128 myVec;
		myVec = Min(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Min(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Min(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Min(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Maximum Value (Per Component)", "[Max]") {
		answer[0] = Set(93058.06245f, 71915.34440f, 40040.35343f, 46768.52948f);
		answer[1] = Set(96166.19073f, 74536.62178f, 97658.71592f, 79553.85881f);
		answer[2] = Set(96166.19073f, 74536.62178f, 40040.35343f, 31179.39351f);
		answer[3] = Set(93058.06245f, 71915.34440f, 97658.71592f, 79553.85881f);

		__m128 myVec;
		myVec = Max(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Max(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Max(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Max(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Maximum Value (Per Component)", "[Max]") {
		answer[0] = Set(48791.991955f, 68002.837065f, 21031.117215f, 23444.062955f);
		answer[1] = Set(48869.433555f, 48964.628480f, 65131.015420f, 55366.626160f);
		answer[2] = Set(50346.056095f, 69313.475755f, 36321.834175f, 15649.494970f);
		answer[3] = Set(47315.369415f, 47653.989790f, 49840.298460f, 63161.194145f);

		__m128 myVec;
		myVec = Average(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Average(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Average(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Average(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Vector Length Squared", "[LengthSq]") {
		//Setup Answers for this section
		float fAnswer[2] = {
			 5731298536.0675919f,
			16415729938.3654595f
		};

		float vecAns;
		vecAns = LengthSq(randFPA);
		CHECK(near_equal(vecAns, fAnswer[0]));

		//Static Length Squared Test: m128
		vecAns = LengthSq(randM128A);
		CHECK(near_equal(vecAns, fAnswer[1]));
	}

	SECTION("Vector Length Squared", "[LengthSq]") {
		//Setup Answers for this section
		float fAnswer[2] = {
			126582.001483696f,
			129764.305374465f
		};

		float vecAns;
		vecAns = Length(randFPB);
		CHECK(near_equal(vecAns, fAnswer[0]));

		//Static Length Squared Test: m128
		vecAns = Length(randM128B);
		CHECK(near_equal(vecAns, fAnswer[1]));
	}

}

TEST_CASE("SSE Base: Vector Math Functions", "[Dot], [Cross], [Normalize], [Homogenize], [AngleBetween], [Component], [Project], [Reflect]") {
	//Using the namespace sml (SSE Math Library)
	using namespace sml;
	
	//Answer Array Setup
	__m128 answer[4] = {};

	SECTION("Dot Product Test", "[Dot]") {
		float fAnswer[4] = {
			5116801796.106543775f,
			 7559285236.463376027f,
			 6521494489.731612930f,
			 5746710925.383224161f
		};

		//Static Dot Product Test: Float Pointer & Float Pointer
		float vecAns = 1.0f;
		vecAns = Dot(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[0]));

		//Static Dot Product Test: m128 & m128
		vecAns = Dot(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Static Dot Product Test: Float Pointer & m128
		vecAns = Dot(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Dot Product Test: m128 & Float Pointer
		vecAns = Dot(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[3]));
	}

	SECTION("Cross Product Test", "[Cross]") {
		answer[0] = Set(-0.308812887f, 0.417404713f, -0.633209766f, 0.0f);
		answer[1] = Set(-0.515099653f, 0.738302691f, -0.168553930f, 0.0f);
		answer[2] = Set(-0.093845581f, 0.388312880f, -0.610942729f, 0.0f);
		answer[3] = Set(-0.590497562f, 0.769012140f, -0.174695711f, 0.0f);

		union { float f; unsigned int i = 0xFFFFFFFF; } ufi;

		__m128 randFPA_3D = Set(randFPA);
		randFPA_3D = _mm_and_ps(randFPA_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randFPA_3D = Normalize(randFPA_3D);

		__m128 randFPB_3D = Set(randFPB);
		randFPB_3D = _mm_and_ps(randFPB_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randFPB_3D = Normalize(randFPB_3D);

		__m128 randM128A_3D = randM128A;
		randM128A_3D = _mm_and_ps(randM128A_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randM128A_3D = Normalize(randM128A_3D);

		__m128 randM128B_3D = randM128B;
		randM128B_3D = _mm_and_ps(randM128B_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randM128B_3D = Normalize(randM128B_3D);

		__m128 myVec;
		myVec = Cross(randFPA_3D, randFPB_3D);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Cross(randM128A_3D, randM128B_3D);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Cross(randFPA_3D, randM128B_3D);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Cross(randM128A_3D, randFPB_3D);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Normalize Test", "[Normalize]") {
		answer[0] = Set(0.059783384f, 0.846576074f, 0.528897344f, 0.001579762f);
		answer[1] = Set(0.012274654f, 0.182578253f, 0.762221000f, 0.620913569f);

		//Static Normalize Function Check: Float Pointer
		__m128 myVec;
		myVec = Normalize(randFPA);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Normalize Function Check: m128
		myVec = Normalize(randM128A);
		CHECK(IsEqual(myVec, answer[1]));
	}

	SECTION("Homogenize Test", "[Homogenize]") {
		answer[0] = Set(1.989758144f, 1.537686670f, 0.043231656f, 1.0f);
		answer[1] = Set(3.084286764f, 2.390573176f, 1.045668669f, 1.0f);

		//Static Normalize Function Check: Float Pointer
		__m128 myVec;
		myVec = Homogenize(randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Normalize Function Check: m128
		myVec = Homogenize(randM128B);
		CHECK(IsEqual(myVec, answer[1]));
	}

	SECTION("Angle Between Vector Test", "[AngleBetween]") {
		//Setup Answers for this section
		float fAnswer[4] = {
			1.007531596f,
			1.098795731f,
			0.844850650f,
			1.208590667f
		};

		//Static Angle Between Test: Float Pointer & Float Pointer
		float vecAns = AngleBetween(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[0]));

		//Static Angle Between Test: m128 & m128
		vecAns = AngleBetween(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Static Angle Between Test: Float Pointer & m128
		vecAns = AngleBetween(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Angle Between Test: m128 & Float Pointer
		vecAns = AngleBetween(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[3]));
	}

	SECTION("Component Test", "[Component]") {
		//Setup Answers for this section
		float fAnswer[4] = {
			 40422.822645647f,
			 58253.964483139f,
			 50256.458977006f,
			 45399.115656449f
		};

		//Static Component Test: Float Pointer & Float Pointer
		float vecAns = Component(randFPA, randFPB);
		CHECK(near_equal(vecAns, fAnswer[0]));

		//Static Component Test: m128 & m128
		vecAns = Component(randM128A, randM128B);
		CHECK(near_equal(vecAns, fAnswer[1]));

		//Static Component Test: Float Pointer & m128
		vecAns = Component(randFPA, randM128B);
		CHECK(near_equal(vecAns, fAnswer[2]));

		//Static Component Test: m128 & Float Pointer
		vecAns = Component(randM128A, randFPB);
		CHECK(near_equal(vecAns, fAnswer[3]));
	}

	SECTION("Project Test", "[Project]") {
		answer[0] = Set(29717.254507533f, 22965.517831192f, 645.66949578634f, 14935.108865467f);
		answer[1] = Set(43171.054190119f, 33461.079341774f, 14636.323478182f, 13997.094785780f);
		answer[2] = Set(37244.234502319f, 28867.311884893f, 12626.948173945f, 12075.477199538f);
		answer[3] = Set(33375.627580646f, 25792.711440966f, 725.15530080633f, 16773.710749218f);

		__m128 myVec;
		myVec = Project(randFPA, randFPB);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Project(randM128A, randM128B);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Project(randFPA, randM128B);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Project(randM128A, randFPB);
		CHECK(IsEqual(myVec, answer[3]));
	}

	SECTION("Reflect Test", "[Reflect]") {
		answer[0] = Set(0.848413913f, -0.144721481f, -0.509165517f, 0.0f);
		answer[1] = Set(0.597331600f, 0.242201118f, -0.764547956f, 0.0f);
		answer[2] = Set(0.983832565f, -0.037689804f, -0.175079873f, 0.0f);
		answer[3] = Set(0.255711896f, -0.023200824f, -0.966474597f, 0.0f);

		union { float f; unsigned int i = 0xFFFFFFFF; } ufi;

		__m128 randFPA_3D = Set(randFPA);
		randFPA_3D = _mm_and_ps(randFPA_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randFPA_3D = Normalize(randFPA_3D);

		__m128 randFPB_3D = Set(randFPB);
		randFPB_3D = _mm_and_ps(randFPB_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randFPB_3D = Normalize(randFPB_3D);

		__m128 randM128A_3D = randM128A;
		randM128A_3D = _mm_and_ps(randM128A_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randM128A_3D = Normalize(randM128A_3D);

		__m128 randM128B_3D = randM128B;
		randM128B_3D = _mm_and_ps(randM128B_3D, _mm_set_ps(0.0f, ufi.f, ufi.f, ufi.f));
		randM128B_3D = Normalize(randM128B_3D);

		__m128 myVec;
		myVec = Reflect(randFPA_3D, randFPB_3D);
		CHECK(IsEqual(myVec, answer[0]));

		//Static Sub: m128 & m128
		myVec = Reflect(randM128A_3D, randM128B_3D);
		CHECK(IsEqual(myVec, answer[1]));

		//Static Sub: Float Pointer & m128
		myVec = Reflect(randFPA_3D, randM128B_3D);
		CHECK(IsEqual(myVec, answer[2]));

		//Static Sub: m128 & Float Pointer
		myVec = Reflect(randM128A_3D, randFPB_3D);
		CHECK(IsEqual(myVec, answer[3]));
	}
}