#define VEC4_FLOATS_GLOBAL
#define MAT4_FLOATS_GLOBAL
#include "../xplat.h"
#include "catch2.hpp"
#include "../vec4/vec4f.h"
#include "../mat4/mat4f.h"

namespace {
	vec4 randVecArrayA[4] = {
		{8.85465f, 9.79409f, 4.75434f, 8.06544f},
		{4.63649f, 9.99391f, 3.37818f, 1.44557f},
		{8.67830f, 9.51128f, 1.40010f, 7.02192f},
		{5.00668f, 4.14069f, 8.60563f, 9.01100f}
	};
	vec4 randVecArrayB[4] = {
		{9.67274f, 1.82071f, 9.68675f, 3.80261f},
		{4.98939f, 1.69798f, 8.95786f, 5.59849f},
		{9.25028f, 6.96418f, 7.51654f, 9.32101f},
		{4.49080f, 6.34379f, 6.89205f, 8.11064f}
	};
	float randMatFP[16] = {
		3.08933f, 8.45437f, 7.38294f, 6.09458f,
		2.75164f, 1.90594f, 4.82559f, 1.85289f,
		6.86626f, 7.97092f, 4.48941f, 3.83587f,
		6.59058f, 3.55364f, 4.76198f, 9.83926f
	};

	mat4 zero;
	mat4 identity(1.0f);
	mat4 matFPM(randMatFP);
	mat4 matSSE(randVecArrayA[0].m128, randVecArrayA[1].m128, randVecArrayA[2].m128, randVecArrayA[3].m128);
	mat4 matFPV(randVecArrayB[0].e, randVecArrayB[1].e, randVecArrayB[2].e, randVecArrayB[3].e);
	mat4 matMAN(0.0f, 1.0f, 2.0f, 3.0f, 0.0f, 2.0f, 4.0f, 6.0f, 0.0f, 3.0f, 6.0f, 9.0f, 0.0f, 4.0f, 8.0f, 12.0f);
}

TEST_CASE("Constructors, Assignment, and Set", "[mat4f] [operator=] [Set]")
{
	SECTION("Constructor", "[mat4f]") {
		float zeroFP[16] = {};
		float identityFP[16] = { 
			1, 0, 0, 0,
			0, 1, 0, 0, 
			0, 0, 1, 0, 
			0, 0, 0, 1 };

		CHECK(!memcmp(zero.e, zeroFP, sizeof(mat4)));
		CHECK(!memcmp(identity.e, identityFP, sizeof(mat4)));
		CHECK(!memcmp(matFPM.e, randMatFP, sizeof(mat4)));
		CHECK(!memcmp(matSSE.e, &randVecArrayA[0].m128, sizeof(mat4)));
		CHECK(!memcmp(matFPV.e, randVecArrayB[0].e, sizeof(mat4)));
	}
}