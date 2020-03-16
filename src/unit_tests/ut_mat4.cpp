#include "catch2.hpp"
#include "ut_utility.h"
using namespace sml;

TEST_CASE("Contructors, Assignment, and Set for sml::mat4f", "[mat4f], [operator=], [Set]")
{
	SECTION("Constructor Tests", "[mat4()]")
	{
		SECTION("Default Constructor Test")
		{
			mat4f zero;
			CHECK(zero.IsZero());
		}

		SECTION("Diagonal Constructor Test")
		{
			float floats[16] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			mat4f matrix = sml::MatrixSet(1.0f);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}

		SECTION("__m128 Constructor Test")
		{
			mat4f matrix;
			__m128 sseX, sseY, sseZ, sseW;
			sseX = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
			sseY = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
			sseZ = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
			sseW = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

			matrix.Set(sseX, sseY, sseZ, sseW);

			CHECK(!memcmp(&sseX, &matrix.m128X, sizeof(__m128)));
			CHECK(!memcmp(&sseY, &matrix.m128Y, sizeof(__m128)));
			CHECK(!memcmp(&sseZ, &matrix.m128Z, sizeof(__m128)));
			CHECK(!memcmp(&sseW, &matrix.m128T, sizeof(__m128)));
		}

		SECTION("4 Float Pointers Constructor Test")
		{
			float floats[16];
			for (unsigned int i = 0; i < 16; ++i)
			{
				floats[i] = rand_num();
			}
			mat4f matrix(&floats[0], &floats[4], &floats[8], &floats[12]);
			CHECK(!memcmp(floats, &matrix, sizeof(mat4f)));
		}

		SECTION("Float Pointer Constructor Test")
		{
			float floats[16];
			for (unsigned int i = 0; i < 16; ++i)
			{
				floats[i] = rand_num();
			}
			mat4f matrix(floats);
			CHECK(!memcmp(floats, &matrix, sizeof(mat4f)));
		}

		SECTION("Float Constructor Test")
		{
			float floats[16] =
			{
				0.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 0.0f
			};
			mat4f matrix(floats[0], floats[1], floats[2], floats[3],
				floats[4], floats[5], floats[6], floats[7],
				floats[8], floats[9], floats[10], floats[11],
				floats[12], floats[13], floats[14], floats[15]);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}
	}

	SECTION("Assignment Tests", "[operator=]")
	{
		SECTION("mat4f -> mat4f Test")
		{
			mat4f matrixA(rand_mat4f());
			mat4f matrixB;

			matrixB = matrixA;
			CHECK(&matrixB != &matrixA);
			CHECK(!memcmp(&matrixB, &matrixA, sizeof(mat4f)));
		}

		SECTION("float* -> mat4f Test")
		{
			float floats[16];
			for (unsigned int i = 0; i < 16; ++i)
			{
				floats[i] = rand_num();
			}

			mat4f matrix;
			matrix = floats;
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}
	}

	SECTION("Set Tests", "[Set]")
	{
		SECTION("Static Diagonal Set Test")
		{
			float floats[16] =
			{
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
			mat4f matrix = sml::MatrixSet(1.0f);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}

		SECTION("Static __m128 Set Test")
		{
			__m128 sseX, sseY, sseZ, sseW;
			sseX = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);
			sseY = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);
			sseZ = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);
			sseW = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
			mat4f matrix = sml::MatrixSet(sseX, sseY, sseZ, sseW);

			CHECK(!memcmp(&sseX, &matrix.m128X, sizeof(__m128)));
			CHECK(!memcmp(&sseY, &matrix.m128Y, sizeof(__m128)));
			CHECK(!memcmp(&sseZ, &matrix.m128Z, sizeof(__m128)));
			CHECK(!memcmp(&sseW, &matrix.m128T, sizeof(__m128)));
		}

		SECTION("Static 4 Float Pointers Set Test")
		{
			float floats[16] =
			{
				0.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 0.0f
			};
			mat4f matrix = sml::MatrixSet(&floats[0], &floats[4], &floats[8], &floats[12]);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}

		SECTION("Static Float Pointer Set Test")
		{
			float floats[16];
			for (unsigned int i = 0; i < 16; ++i)
			{
				floats[i] = rand_num();
			}
			mat4f matrix = sml::MatrixSet(floats);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}

		SECTION("Static Float Set Test")
		{
			float floats[16] =
			{
				0.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 0.0f
			};
			mat4f matrix = sml::MatrixSet(floats[0], floats[1], floats[2], floats[3],
											floats[4], floats[5], floats[6], floats[7],
											floats[8], floats[9], floats[10], floats[11],
											floats[12], floats[13], floats[14], floats[15]);
			CHECK(!memcmp(&matrix, floats, sizeof(mat4f)));
		}
	}
}