#ifndef UT_UTILITY_H
#define UT_UTILITY_H
#include "../include/ssemath.h"
#include "../xplat.h"

namespace
{
	float rand_num() {
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 100.0f);
	}

	sml::vec4f rand_vec4f()
	{
		float x = rand_num();
		float y = rand_num();
		float z = rand_num();
		float w = rand_num();
		return sml::vec4f(x, y, z, w);
	}

	sml::mat4f rand_mat4f()
	{
		float floats[16];
		for (unsigned int i = 0; i < 16; ++i)
		{
			floats[i] = rand_num();
		}
		return sml::mat4f(floats);
	}

	bool near_equal(float x, float y, float relValue = FLT_EPSILON * 2.0f) {
		float diff = fabsf(x - y);
		float A = fabs(x); float B = fabs(y);
		float length = (A > B ? A : B)* relValue;
		return diff <= length;
	}
}
#endif