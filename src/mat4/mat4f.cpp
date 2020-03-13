#include "mat4f.h"
#include <math.h>
#include <float.h>

namespace {
	static const mat4f fake_ans(0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f);
}

//Constructors and Assignment
mat4f::mat4f() {
	m128X = _mm_setzero_ps();
	m128Y = _mm_setzero_ps();
	m128Z = _mm_setzero_ps();
	m128T = _mm_setzero_ps();
}
mat4f::mat4f(const float& _diagonal) {
	m128X = _mm_set_ps(0.0f, 0.0f, 0.0f, _diagonal);
	m128Y = _mm_set_ps(0.0f, 0.0f, _diagonal, 0.0f);
	m128Z = _mm_set_ps(0.0f, _diagonal, 0.0f, 0.0f);
	m128T = _mm_set_ps(_diagonal, 0.0f, 0.0f, 0.0f);
}
mat4f::mat4f(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt) {
	m128X = _vectorSSEx;
	m128Y = _vectorSSEy;
	m128Z = _vectorSSEz;
	m128T = _vectorSSEt;
}
mat4f::mat4f(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt) {
	m128X = _mm_load_ps(_vectorFPx);
	m128Y = _mm_load_ps(_vectorFPy);
	m128Z = _mm_load_ps(_vectorFPz);
	m128T = _mm_load_ps(_vectorFPt);
}
mat4f::mat4f(const float* _matrixFP) {
	m128X = _mm_load_ps(_matrixFP);
	m128Y = _mm_load_ps(&_matrixFP[4]);
	m128Z = _mm_load_ps(&_matrixFP[8]);
	m128T = _mm_load_ps(&_matrixFP[12]);
}
mat4f::mat4f(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
	const float& _e21, const float& _e22, const float& _e23, const float& _e24,
	const float& _e31, const float& _e32, const float& _e33, const float& _e34,
	const float& _e41, const float& _e42, const float& _e43, const float& _e44) {
	m128X = _mm_set_ps(_e14, _e13, _e12, _e11);
	m128Y = _mm_set_ps(_e24, _e23, _e22, _e21);
	m128Z = _mm_set_ps(_e34, _e33, _e32, _e31);
	m128T = _mm_set_ps(_e44, _e43, _e42, _e41);
}
void mat4f::operator=(const float& _diagonal) {}
void mat4f::operator=(const mat4f& _matrix) {}
void mat4f::operator=(const float* _matrixFP) {}
mat4f mat4f::Set(const float& _diagonal) { return fake_ans; }
mat4f mat4f::Set(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt) { return fake_ans; }
mat4f mat4f::Set(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt) { return fake_ans; }
mat4f mat4f::Set(const float* _matrixFP) { return fake_ans; }
mat4f mat4f::Set(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
	const float& _e21, const float& _e22, const float& _e23, const float& _e24,
	const float& _e31, const float& _e32, const float& _e33, const float& _e34,
	const float& _e41, const float& _e42, const float& _e43, const float& _e44) { return fake_ans; }
