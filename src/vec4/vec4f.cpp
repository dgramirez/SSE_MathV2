#include "vec4f.h"
#include "../xplat.h"

#define CINT(x) static_cast<int>(x) //Cast to int (unsigned)

//Global Variables (Namespace)
namespace {
	static const vec4f vec4f_zero = {0.0f, 0.0f, 0.0f, 1.0f};
	static const float realZero[4] = {};
	static union { float f; unsigned int i = 0xFFFFFFFF; } MaxBits;
	static union { float f; unsigned int i = 0x80000000; } NegativeZero;
	static const __m128 m128PosNaN = _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f));
	float epsilon = FLT_EPSILON;
	//Getting SSE Values
	static inline float GetSSEValue(const __m128& _vectorSSE, const uint32_t& index) {
		#if defined(_WIN32)
		return _vectorSSE.m128_f32[index];
		#else
		return _vectorSSE[index];
		#endif
}
}

//Epsilon
void vec4f::ChangeEpsilon(const float& _epsilon) {
	epsilon = _epsilon < 0 ? FLT_EPSILON * 2 : _epsilon;
}
float vec4f::GetEpsilon() { return epsilon; }

//Constructor & Assignment
vec4f::vec4f() {
	//Set the m128 value to 0
	m128 = _mm_setzero_ps();
}
vec4f::vec4f(const float& _x, const float& _y, const float& _z, const float& _w) {
	//Set the m128 value to xyzw
	m128 = _mm_set_ps(_w, _z, _y, _x);
}
vec4f::vec4f(const vec4f& _vector) {
	//Set the m128 value to the other vector's m128 value
	m128 = _vector.m128;
}
vec4f::vec4f(const float* _vectorFP) {
	//Load the float pointer to the m128 value
	m128 = _mm_load_ps(_vectorFP);
}
vec4f::vec4f(const __m128& _vectorSSE) {
	//Set the m128 value to the parameter m128 value
	m128 = _vectorSSE;
}
void vec4f::operator=(const vec4f& _vector) {
	//Assign the m128 value to the parameter vector's m128 value
	m128 = _vector.m128;
}
void vec4f::operator=(const float* _vectorFP) {
	//Assign the m128 to the float pointer loaded in as a m128
	m128 = _mm_load_ps(_vectorFP);
}
void vec4f::operator=(const __m128& _vectorSSE) {
	//Assign the m128 value to the m128 parameter value
	m128 = _vectorSSE;
}
vec4f vec4f::Set(const float& _x, const float& _y, const float& _z, const float& _w) {
	//Set the m128 value to xyzw
	return _mm_set_ps(_w, _z, _y, _x);
}
vec4f vec4f::Set(const vec4f& _vector) {
	//Set the m128 value to the other vector's m128 value
	return _vector.m128;
}
vec4f vec4f::Set(const float* _vectorFP) {
	//Load the float pointer to the m128 value
	return _mm_load_ps(_vectorFP);
}
vec4f vec4f::Set(const __m128& _vectorSSE) {
	//Set the m128 value to the parameter m128 value
	return _vectorSSE;
}

//Vec4 Absolute Value
void vec4f::vabs() {
	//Toggle the negative bit
	m128 = _mm_and_ps(m128, m128PosNaN);
}
vec4f vec4f::vabs(const vec4f& _vector) {
	//Toggle the negative bit
	return _mm_and_ps(_vector.m128, _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}
vec4f vec4f::vabs(const float* _vectorFP) {
	//Toggle the negative bit
	return _mm_and_ps(_mm_load_ps(_vectorFP), _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}
vec4f vec4f::vabs(const __m128& _vectorSSE) {
	//Toggle the negative bit
	return _mm_and_ps(_vectorSSE, _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}

//Equality Check (Zero)
bool vec4f::IsZero() const { 
	//Return the Comparison of the 0 vector to itself (0 == same bit value)
	vec4f eq = _mm_cmple_ps(m128, _mm_set1_ps(FLT_EPSILON));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsZero(const vec4f& _vector) {
	//Return the Comparison of the 0 vector to the vector parameter (0 == same bit value)
	vec4f eq = _mm_cmple_ps(_vector.m128, _mm_set1_ps(FLT_EPSILON));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsZero(const float* _vectorFP) {
	//Return the Comparison of the 0 vector to the float pointer parameter (0 == same bit value)
	vec4f eq = _mm_cmple_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(FLT_EPSILON));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsZero(const __m128& _vectorSSE) {
	//Return the Comparison of the 0 vector to the m128 parameter (0 == same bit value)
	vec4f eq = _mm_cmple_ps(_vectorSSE, _mm_set1_ps(FLT_EPSILON));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}

//Equality Check
bool vec4f::IsEqual(const vec4f& _vector) const {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(m128, _vector.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(m128);
	vec4f absV2 = vec4f::vabs(_vector.m128);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector.m128, m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const float* _vectorFP) const {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(m128, fp);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(m128);
	vec4f absV2 = vec4f::vabs(fp);
	vec4f diff = vec4f::vabs(_mm_sub_ps(fp, m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const __m128& _vectorSSE) const {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(m128, _vectorSSE);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(m128);
	vec4f absV2 = vec4f::vabs(_vectorSSE);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vectorSSE, m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const vec4f& _vector1, const vec4f& _vector2) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vector1.m128, _vector2.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector1);
	vec4f absV2 = vec4f::vabs(_vector2);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector2.m128, _vector1.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const vec4f& _vector, const float* _vectorFP) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(_vector.m128, fp);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector);
	vec4f absV2 = vec4f::vabs(fp);
	vec4f diff = vec4f::vabs(_mm_sub_ps(fp, _vector.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const float* _vectorFP, const vec4f& _vector) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(fp, _vector.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(fp);
	vec4f absV2 = vec4f::vabs(_vector);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector.m128, fp));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const vec4f& _vector, const __m128& _vectorSSE) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vector.m128, _vectorSSE);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector);
	vec4f absV2 = vec4f::vabs(_vectorSSE);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vectorSSE, _vector.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const __m128& _vectorSSE, const vec4f& _vector) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vectorSSE, _vector.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vectorSSE);
	vec4f absV2 = vec4f::vabs(_vector);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector.m128, _vectorSSE));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}

//IsEqual Additions
bool vec4f::IsEqual(const float* _vectorFP1, const float* _vectorFP2) {
	//Exact Equality Check
	__m128 fp1 = _mm_load_ps(_vectorFP1);
	__m128 fp2 = _mm_load_ps(_vectorFP2);
	vec4f eq = _mm_cmpeq_ps(fp1, fp2);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(fp1);
	vec4f absV2 = vec4f::vabs(fp2);
	vec4f diff = vec4f::vabs(_mm_sub_ps(fp2, fp1));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const __m128& _vectorSSE1, const __m128& _vectorSSE2) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vectorSSE1, _vectorSSE2);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vectorSSE1);
	vec4f absV2 = vec4f::vabs(_vectorSSE2);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vectorSSE2, _vectorSSE1));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const float* _vectorFP, const __m128& _vectorSSE) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(fp, _vectorSSE);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(fp);
	vec4f absV2 = vec4f::vabs(_vectorSSE);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vectorSSE, fp));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool vec4f::IsEqual(const __m128& _vectorSSE, const float* _vectorFP) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(_vectorSSE, fp);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vectorSSE);
	vec4f absV2 = vec4f::vabs(fp);
	vec4f diff = vec4f::vabs(_mm_sub_ps(fp, _vectorSSE));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}

//Equality Check (Operator Overload)
bool operator==(const vec4f& _vector1, const vec4f& _vector2) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vector1.m128, _vector2.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector1);
	vec4f absV2 = vec4f::vabs(_vector2);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector2.m128, _vector1.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool operator==(const vec4f& _vector, const float* _vectorFP) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(_vector.m128, fp);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector);
	vec4f absV2 = vec4f::vabs(fp);
	vec4f diff = vec4f::vabs(_mm_sub_ps(fp, _vector.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool operator==(const vec4f& _vector, const __m128& _vectorSSE) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vector.m128, _vectorSSE);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vector);
	vec4f absV2 = vec4f::vabs(_vectorSSE);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vectorSSE, _vector.m128));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool operator==(const float* _vectorFP, const vec4f& _vector) {
	//Exact Equality Check
	__m128 fp = _mm_load_ps(_vectorFP);
	vec4f eq = _mm_cmpeq_ps(fp, _vector.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(fp);
	vec4f absV2 = vec4f::vabs(_vector);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector.m128, fp));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}
bool operator==(const __m128& _vectorSSE, const vec4f& _vector) {
	//Exact Equality Check
	vec4f eq = _mm_cmpeq_ps(_vectorSSE, _vector.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_vectorSSE);
	vec4f absV2 = vec4f::vabs(_vector);
	vec4f diff = vec4f::vabs(_mm_sub_ps(_vector.m128, _vectorSSE));
	vec4f relDiv = vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX));

	//Relative Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(_mm_div_ps(diff.m128, relDiv.m128), _mm_set1_ps(epsilon)));
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Near-Zero Equality Check
	eq = _mm_or_ps(eq.m128, _mm_cmple_ps(diff.m128, _mm_set1_ps(epsilon)));
	return (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w));
}

//Inequality Check (Operator Overload)
bool operator!=(const vec4f& _vector1, const vec4f& _vector2)		{ return !(_vector1 == _vector2); }
bool operator!=(const vec4f& _vector, const float* _vectorFP)		{ return !(_vector == _vectorFP); }
bool operator!=(const vec4f& _vector, const __m128& _vectorSSE)	{ return !(_vector == _vectorSSE); }
bool operator!=(const float* _vectorFP, const vec4f& _vector)		{ return !(_vectorFP == _vector); }
bool operator!=(const __m128& _vectorSSE, const vec4f& _vector)	{ return !(_vectorSSE == _vector); }

//Vector-Vector Addition (Self)
void vec4f::Add(const vec4f& _vector)			{ m128 = _mm_add_ps(m128, _vector.m128); }
void vec4f::Add(const float* _vectorFP)			{ m128 = _mm_add_ps(m128, _mm_load_ps(_vectorFP)); }
void vec4f::Add(const __m128& _vectorSSE)			{ m128 = _mm_add_ps(m128, _vectorSSE); }
void vec4f::operator+=(const vec4f& _vector)		{ m128 = _mm_add_ps(m128, _vector.m128); }
void vec4f::operator+=(const float* _vectorFP)	{ m128 = _mm_add_ps(m128, _mm_load_ps(_vectorFP)); }
void vec4f::operator+=(const __m128& _vectorSSE)	{ m128 = _mm_add_ps(m128, _vectorSSE); }

//Vector-Vector Addition (Static & Global Operator Overloads)
vec4f vec4f::Add(const vec4f& _vector1, const vec4f& _vector2)	{ return _mm_add_ps(_vector1.m128, _vector2.m128); }
vec4f vec4f::Add(const vec4f& _vector, const float* _vectorFP)		{ return _mm_add_ps(_vector.m128, _mm_load_ps(_vectorFP)); }
vec4f vec4f::Add(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_add_ps(_vector.m128, _vectorSSE); }
vec4f vec4f::Add(const float* _vectorFP, const vec4f& _vector)		{ return _mm_add_ps(_mm_load_ps(_vectorFP), _vector.m128); }
vec4f vec4f::Add(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_add_ps(_vectorSSE, _vector.m128); }
vec4f operator+(const vec4f& _vector1, const vec4f& _vector2)		{ return _mm_add_ps(_vector1.m128, _vector2.m128); }
vec4f operator+(const vec4f& _vector, const float* _vectorFP)		{ return _mm_add_ps(_vector.m128, _mm_load_ps(_vectorFP)); }
vec4f operator+(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_add_ps(_vector.m128, _vectorSSE); }
vec4f operator+(const float* _vectorFP, const vec4f& _vector)		{ return _mm_add_ps(_mm_load_ps(_vectorFP), _vector.m128); }
vec4f operator+(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_add_ps(_vectorSSE, _vector.m128); }

//Vector-Vector Static Add Additions
vec4f vec4f::Add(const float* _vectorFP1, const float* _vectorFP2)		{ return vec4f(_mm_add_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2))); }
vec4f vec4f::Add(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ return vec4f(_mm_add_ps(_vectorSSE1, _vectorSSE2));; }
vec4f vec4f::Add(const float* _vectorFP, const __m128& _vectorSSE)		{ return vec4f(_mm_add_ps(_mm_load_ps(_vectorFP), _vectorSSE)); }
vec4f vec4f::Add(const __m128& _vectorSSE, const float* _vectorFP)		{ return vec4f(_mm_add_ps(_vectorSSE, _mm_load_ps(_vectorFP))); }

//Vector-Vector Subtraction (Self & Self Operator Overloads)
void vec4f::Sub(const vec4f& _vector)			{ m128 = _mm_sub_ps(m128, _vector.m128); }
void vec4f::Sub(const float* _vectorFP)			{ m128 = _mm_sub_ps(m128, _mm_load_ps(_vectorFP)); }
void vec4f::Sub(const __m128& _vectorSSE)			{ m128 = _mm_sub_ps(m128, _vectorSSE); }
void vec4f::operator-=(const vec4f& _vector)		{ m128 = _mm_sub_ps(m128, _vector.m128); }
void vec4f::operator-=(const float* _vectorFP)	{ m128 = _mm_sub_ps(m128, _mm_load_ps(_vectorFP)); }
void vec4f::operator-=(const __m128& _vectorSSE)	{ m128 = _mm_sub_ps(m128, _vectorSSE); }

//Vector-Vector Subtraction (Static & Global Operator Overloads)
vec4f vec4f::Sub(const vec4f& _vector1, const vec4f& _vector2)	{ return _mm_sub_ps(_vector1.m128, _vector2.m128); }
vec4f vec4f::Sub(const vec4f& _vector, const float* _vectorFP)		{ return _mm_sub_ps(_vector.m128, _mm_load_ps(_vectorFP)); }
vec4f vec4f::Sub(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_sub_ps(_vector.m128, _vectorSSE); }
vec4f vec4f::Sub(const float* _vectorFP, const vec4f& _vector)		{ return _mm_sub_ps(_mm_load_ps(_vectorFP), _vector.m128); }
vec4f vec4f::Sub(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_sub_ps(_vectorSSE, _vector.m128); }
vec4f operator-(const vec4f& _vector1, const vec4f& _vector2)		{ return _mm_sub_ps(_vector1.m128, _vector2.m128); }
vec4f operator-(const vec4f& _vector, const float* _vectorFP)		{ return _mm_sub_ps(_vector.m128, _mm_load_ps(_vectorFP)); }
vec4f operator-(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_sub_ps(_vector.m128, _vectorSSE); }
vec4f operator-(const float* _vectorFP, const vec4f& _vector)		{ return _mm_sub_ps(_mm_load_ps(_vectorFP), _vector.m128); }
vec4f operator-(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_sub_ps(_vectorSSE, _vector.m128); }

//Vector-Vector Static Subtraction Additions
vec4f vec4f::Sub(const float* _vectorFP1, const float* _vectorFP2)		{ return _mm_sub_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2)); }
vec4f vec4f::Sub(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ return _mm_sub_ps(_vectorSSE1, _vectorSSE2);; }
vec4f vec4f::Sub(const float* _vectorFP, const __m128& _vectorSSE)		{ return _mm_sub_ps(_mm_load_ps(_vectorFP), _vectorSSE); }
vec4f vec4f::Sub(const __m128& _vectorSSE, const float* _vectorFP)		{ return _mm_sub_ps(_vectorSSE, _mm_load_ps(_vectorFP)); }

//Vector-Scalar Multiply (Self & Self Operator Overload)
void vec4f::Mul(const float& _s)		{ m128 = _mm_mul_ps(m128, _mm_set1_ps(_s)); }
void vec4f::operator*=(const float& _s) { m128 = _mm_mul_ps(m128, _mm_set1_ps(_s)); }

//Vector-Scalar Multiply (Static & Global Operator Overload)
vec4f vec4f::Mul(const vec4f& _vector, const float& _s)		{ return _mm_mul_ps(_vector.m128, _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const float* _vectorFP, const float& _s)		{ return _mm_mul_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const __m128& _vectorSSE, const float& _s)	{ return _mm_mul_ps(_vectorSSE, _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const float& _s, const vec4f& _vector)		{ return _mm_mul_ps(_mm_set1_ps(_s), _vector.m128); }
vec4f vec4f::Mul(const float& _s, const float* _vectorFP)		{ return _mm_mul_ps(_mm_set1_ps(_s), _mm_load_ps(_vectorFP)); }
vec4f vec4f::Mul(const float& _s, const __m128& _vectorSSE)	{ return _mm_mul_ps(_mm_set1_ps(_s), _vectorSSE); }
vec4f operator*(const vec4f& _vector, const float& _s)		{ return _mm_mul_ps(_vector.m128, _mm_set1_ps(_s)); }
vec4f operator*(const float& _s, const vec4f& _vector)		{ return _mm_mul_ps(_mm_set1_ps(_s), _vector.m128); }

//Vector-Scalar Divide (Self & Self Operator Overload)
void vec4f::Div(const float& _s)		{ m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }
void vec4f::operator/=(const float& _s) { m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }

//Vector-Scalar Divide (Static & Global Operator Overload)
vec4f vec4f::Div(const vec4f& _vector, const float& _s)		{ return _mm_div_ps(_vector.m128, _mm_set1_ps(_s)); }
vec4f vec4f::Div(const float* _vectorFP, const float& _s)		{ return _mm_div_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(_s)); }
vec4f vec4f::Div(const __m128& _vectorSSE, const float& _s)	{ return _mm_div_ps(_vectorSSE, _mm_set1_ps(_s)); }
vec4f operator/(const vec4f& _vector, const float& _s)		{ return _mm_div_ps(_vector.m128, _mm_set1_ps(_s)); }

//Vector Negate
void vec4f::Negate()					{ m128 = _mm_xor_ps(m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::operator-()				{ return _mm_xor_ps(m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const vec4f& _vector)	{ return _mm_xor_ps(_vector.m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const float* _vectorFP)	{ return _mm_xor_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const __m128& _vectorSSE) { return _mm_xor_ps(_vectorSSE, _mm_set1_ps(NegativeZero.f)); }

//Vector Minimum (Per Component)
void vec4f::Min(const vec4f& _vector)						{ m128 = _mm_min_ps(m128, _vector.m128); }
vec4f vec4f::Min(const vec4f& _vector1, const vec4f& _vector2)	{ return _mm_min_ps(_vector1.m128, _vector2.m128); }
vec4f vec4f::Min(const vec4f& _vector, const float* _vectorFP)		{ return _mm_min_ps(_vector.m128, _mm_load_ps(_vectorFP)); }
vec4f vec4f::Min(const float* _vectorFP, const vec4f& _vector)		{ return _mm_min_ps(_mm_load_ps(_vectorFP), _vector.m128); }
vec4f vec4f::Min(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_min_ps(_vector.m128, _vectorSSE); }
vec4f vec4f::Min(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_min_ps(_vectorSSE, _vector.m128); }

//Vector Static Minimum Additions
vec4f vec4f::Min(const float* _vectorFP1, const float* _vectorFP2)		{ return _mm_min_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2)); }
vec4f vec4f::Min(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ return _mm_min_ps(_vectorSSE1, _vectorSSE2); }
vec4f vec4f::Min(const float* _vectorFP, const __m128& _vectorSSE)		{ return _mm_min_ps(_mm_load_ps(_vectorFP), _vectorSSE); }
vec4f vec4f::Min(const __m128& _vectorSSE, const float* _vectorFP)		{ return _mm_min_ps(_vectorSSE, _mm_load_ps(_vectorFP)); }

//Vector Maximum (Per Component)
void vec4f::Max(const vec4f& _vector)						{ m128 = _mm_max_ps(m128, _vector.m128); }
vec4f vec4f::Max(const vec4f& _vector1, const vec4f& _vector2)	{ return _mm_max_ps(_vector1.m128, _vector2.m128); }	
vec4f vec4f::Max(const vec4f& _vector, const float* _vectorFP)		{ return _mm_max_ps(_vector.m128, _mm_load_ps(_vectorFP)); }	
vec4f vec4f::Max(const float* _vectorFP, const vec4f& _vector)		{ return _mm_max_ps(_mm_load_ps(_vectorFP), _vector.m128); }	
vec4f vec4f::Max(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_max_ps(_vector.m128, _vectorSSE); }	
vec4f vec4f::Max(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_max_ps(_vectorSSE, _vector.m128); }	

//Vector Static Maximum Additions
vec4f vec4f::Max(const float* _vectorFP1, const float* _vectorFP2)		{ return _mm_max_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2)); }
vec4f vec4f::Max(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ return _mm_max_ps(_vectorSSE1, _vectorSSE2); }
vec4f vec4f::Max(const float* _vectorFP, const __m128& _vectorSSE)		{ return _mm_max_ps(_mm_load_ps(_vectorFP), _vectorSSE); }
vec4f vec4f::Max(const __m128& _vectorSSE, const float* _vectorFP)		{ return _mm_max_ps(_vectorSSE, _mm_load_ps(_vectorFP)); }

//Vector Average (Per Component)
void vec4f::Average(const vec4f& _vector)						{ m128 = _mm_mul_ps(_mm_add_ps(m128, _vector.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _vector1, const vec4f& _vector2)	{ return _mm_mul_ps(_mm_add_ps(_vector1.m128, _vector2.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _vector, const float* _vectorFP)		{ return _mm_mul_ps(_mm_add_ps(_vector.m128, _mm_load_ps(_vectorFP)), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const float* _vectorFP, const vec4f& _vector)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(_vectorFP), _vector.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _vector, const __m128& _vectorSSE)	{ return _mm_mul_ps(_mm_add_ps(_vector.m128, _vectorSSE), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _vectorSSE, const vec4f& _vector)	{ return _mm_mul_ps(_mm_add_ps(_vectorSSE, _vector.m128), _mm_set1_ps(0.5f)); }

//Vector Static Average Additions
vec4f vec4f::Average(const float* _vectorFP1, const float* _vectorFP2)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2)), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ return _mm_mul_ps(_mm_add_ps(_vectorSSE1, _vectorSSE2), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const float* _vectorFP, const __m128& _vectorSSE)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(_vectorFP), _vectorSSE), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _vectorSSE, const float* _vectorFP)		{ return _mm_mul_ps(_mm_add_ps(_vectorSSE, _mm_load_ps(_vectorFP)), _mm_set1_ps(0.5f)); }

//Vector Lengths
float vec4f::Length() const				{ vec4f sq = _mm_mul_ps(m128, m128); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const vec4f& _vector)	{ vec4f sq = _mm_mul_ps(_vector.m128, _vector.m128); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const float* _vectorFP)	{ vec4f sq = _mm_mul_ps(_mm_load_ps(_vectorFP), _mm_load_ps(_vectorFP)); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const __m128& _vectorSSE)	{ vec4f sq = _mm_mul_ps(_vectorSSE, _vectorSSE); return sqrtf(sq.x + sq.y + sq.z + sq.w); }

//Vector Length Squared
float vec4f::LengthSq()	const				{ vec4f sq = _mm_mul_ps(m128, m128); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const vec4f& _vector)		{ vec4f sq = _mm_mul_ps(_vector.m128, _vector.m128); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const float* _vectorFP)		{ vec4f sq = _mm_mul_ps(_mm_load_ps(_vectorFP), _mm_load_ps(_vectorFP)); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const __m128& _vectorSSE)	{ vec4f sq = _mm_mul_ps(_vectorSSE, _vectorSSE); return sq.x + sq.y + sq.z + sq.w; }

//Vector Dot Product
float vec4f::Dot(const vec4f& _vector) const					{ vec4f m = _mm_mul_ps(m128, _vector.m128);	return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* _vectorFP) const				{ vec4f m = _mm_mul_ps(m128, _mm_load_ps(_vectorFP)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _vectorSSE) const				{ vec4f m = _mm_mul_ps(m128, _vectorSSE);	return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _vector1, const vec4f& _vector2)	{ vec4f m = _mm_mul_ps(_vector1.m128, _vector2.m128); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _vector1, const float* _vectorFP)	{ vec4f m = _mm_mul_ps(_vector1.m128, _mm_load_ps(_vectorFP)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _vector1, const __m128& _vectorSSE)	{ vec4f m = _mm_mul_ps(_vector1.m128, _vectorSSE); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* _vectorFP, const vec4f& _vector2)	{ vec4f m = _mm_mul_ps(_mm_load_ps(_vectorFP), _vector2.m128); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _vectorSSE, const vec4f& _vector2)	{ vec4f m = _mm_mul_ps(_vectorSSE, _vector2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _vector1, const vec4f& _vector2)		{ vec4f m = _mm_mul_ps(_vector1.m128, _vector2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _vector1, const float* _vectorFP)		{ vec4f m = _mm_mul_ps(_vector1.m128, _mm_load_ps(_vectorFP)); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _vector1, const __m128& _vectorSSE)	{ vec4f m = _mm_mul_ps(_vector1.m128, _vectorSSE); return m.x + m.y + m.z + m.w; }
float operator*(const float* _vectorFP, const vec4f& _vector2)		{ vec4f m = _mm_mul_ps(_mm_load_ps(_vectorFP), _vector2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const __m128& _vectorSSE, const vec4f& _vector2)	{ vec4f m = _mm_mul_ps(_vectorSSE, _vector2.m128); return m.x + m.y + m.z + m.w; }

//Vector Dot Product Additions
float vec4f::Dot(const float* _vectorFP1, const float* _vectorFP2)		{ vec4f m = _mm_mul_ps(_mm_load_ps(_vectorFP1), _mm_load_ps(_vectorFP2)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ vec4f m = _mm_mul_ps(_vectorSSE1, _vectorSSE2); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* _vectorFP, const __m128& _vectorSSE)		{ vec4f m = _mm_mul_ps(_mm_load_ps(_vectorFP), _vectorSSE); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _vectorSSE, const float* _vectorFP)		{ vec4f m = _mm_mul_ps(_vectorSSE, _mm_load_ps(_vectorFP)); return m.x + m.y + m.z + m.w; }

//Vector Cross Product (Self & Self Operator Overloads)
void vec4f::Cross(const vec4f& _vector) {
	m128 = _mm_set_ps(
		0.0f,
		(x * _vector.y) - (y * _vector.x),
		(z * _vector.x) - (x * _vector.z),
		(y * _vector.z) - (z * _vector.y)
	);
}
void vec4f::Cross(const float* _vectorFP) {
	m128 = _mm_set_ps(
		0.0f,
		(x * _vectorFP[1]) - (y * _vectorFP[0]),
		(z * _vectorFP[0]) - (x * _vectorFP[2]),
		(y * _vectorFP[2]) - (z * _vectorFP[1])
	);
}
void vec4f::Cross(const __m128& _vectorSSE) {
	m128 = _mm_set_ps(
		0.0f,
		(x * GetSSEValue(_vectorSSE, 1)) - (y * GetSSEValue(_vectorSSE, 0)),
		(z * GetSSEValue(_vectorSSE, 0)) - (x * GetSSEValue(_vectorSSE, 2)),
		(y * GetSSEValue(_vectorSSE, 2)) - (z * GetSSEValue(_vectorSSE, 1))
	);
}
void vec4f::operator^=(const vec4f& _vector) {
	m128 = _mm_set_ps(
		0.0f,
		(x * _vector.y) - (y * _vector.x),
		(z * _vector.x) - (x * _vector.z),
		(y * _vector.z) - (z * _vector.y)
	);
}
void vec4f::operator^=(const float* _vectorFP) {
	m128 = _mm_set_ps(
		0.0f,
		(x * _vectorFP[1]) - (y * _vectorFP[0]),
		(z * _vectorFP[0]) - (x * _vectorFP[2]),
		(y * _vectorFP[2]) - (z * _vectorFP[1])
	);
}
void vec4f::operator^=(const __m128& _vectorSSE) {
	m128 = _mm_set_ps(
		0.0f,
		(x * GetSSEValue(_vectorSSE, 1)) - (y * GetSSEValue(_vectorSSE, 0)),
		(z * GetSSEValue(_vectorSSE, 0)) - (x * GetSSEValue(_vectorSSE, 2)),
		(y * GetSSEValue(_vectorSSE, 2)) - (z * GetSSEValue(_vectorSSE, 1))
	);
}

//Vector Cross Product (Static & Global Operator Overloads)
vec4f vec4f::Cross(const vec4f& _vector1, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * _vector2.y) - (_vector1.y * _vector2.x),
		(_vector1.z * _vector2.x) - (_vector1.x * _vector2.z),
		(_vector1.y * _vector2.z) - (_vector1.z * _vector2.y)
	);
}
vec4f vec4f::Cross(const vec4f& _vector1, const float* _vectorFP) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * _vectorFP[1]) - (_vector1.y * _vectorFP[0]),
		(_vector1.z * _vectorFP[0]) - (_vector1.x * _vectorFP[2]),
		(_vector1.y * _vectorFP[2]) - (_vector1.z * _vectorFP[1])
	);
}
vec4f vec4f::Cross(const vec4f& _vector1, const __m128& _vectorSSE) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * GetSSEValue(_vectorSSE, 1)) - (_vector1.y * GetSSEValue(_vectorSSE, 0)),
		(_vector1.z * GetSSEValue(_vectorSSE, 0)) - (_vector1.x * GetSSEValue(_vectorSSE, 2)),
		(_vector1.y * GetSSEValue(_vectorSSE, 2)) - (_vector1.z * GetSSEValue(_vectorSSE, 1))
	);
}
vec4f vec4f::Cross(const float* _vectorFP, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(_vectorFP[0] * _vector2.y) - (_vectorFP[1] * _vector2.x),
		(_vectorFP[2] * _vector2.x) - (_vectorFP[0] * _vector2.z),
		(_vectorFP[1] * _vector2.z) - (_vectorFP[2] * _vector2.y)
	);
}
vec4f vec4f::Cross(const __m128& _vectorSSE, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(GetSSEValue(_vectorSSE, 0) * _vector2.y) - (GetSSEValue(_vectorSSE, 1) * _vector2.x),
		(GetSSEValue(_vectorSSE, 2) * _vector2.x) - (GetSSEValue(_vectorSSE, 0) * _vector2.z),
		(GetSSEValue(_vectorSSE, 1) * _vector2.z) - (GetSSEValue(_vectorSSE, 2) * _vector2.y)
	);
}
vec4f operator^(const vec4f& _vector1, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * _vector2.y) - (_vector1.y * _vector2.x),
		(_vector1.z * _vector2.x) - (_vector1.x * _vector2.z),
		(_vector1.y * _vector2.z) - (_vector1.z * _vector2.y)
	);
}
vec4f operator^(const vec4f& _vector1, const float* _vectorFP) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * _vectorFP[1]) - (_vector1.y * _vectorFP[0]),
		(_vector1.z * _vectorFP[0]) - (_vector1.x * _vectorFP[2]),
		(_vector1.y * _vectorFP[2]) - (_vector1.z * _vectorFP[1])
	);
}
vec4f operator^(const vec4f& _vector1, const __m128& _vectorSSE) {
	return _mm_set_ps(
		0.0f,
		(_vector1.x * GetSSEValue(_vectorSSE, 1)) - (_vector1.y * GetSSEValue(_vectorSSE, 0)),
		(_vector1.z * GetSSEValue(_vectorSSE, 0)) - (_vector1.x * GetSSEValue(_vectorSSE, 2)),
		(_vector1.y * GetSSEValue(_vectorSSE, 2)) - (_vector1.z * GetSSEValue(_vectorSSE, 1))
	);
}
vec4f operator^(const float* _vectorFP, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(_vectorFP[0] * _vector2.y) - (_vectorFP[1] * _vector2.x),
		(_vectorFP[2] * _vector2.x) - (_vectorFP[0] * _vector2.z),
		(_vectorFP[1] * _vector2.z) - (_vectorFP[2] * _vector2.y)
	);
}
vec4f operator^(const __m128& _vectorSSE, const vec4f& _vector2) {
	return _mm_set_ps(
		0.0f,
		(GetSSEValue(_vectorSSE, 0) * _vector2.y) - (GetSSEValue(_vectorSSE, 1) * _vector2.x),
		(GetSSEValue(_vectorSSE, 2) * _vector2.x) - (GetSSEValue(_vectorSSE, 0) * _vector2.z),
		(GetSSEValue(_vectorSSE, 1) * _vector2.z) - (GetSSEValue(_vectorSSE, 2) * _vector2.y)
	);
}

//Vector Cross Product Additions
vec4f vec4f::Cross(const float* _vectorFP1, const float* _vectorFP2) {
	return _mm_set_ps(
		0.0f,
		(_vectorFP1[0] * _vectorFP2[1]) - (_vectorFP1[1] * _vectorFP2[0]),
		(_vectorFP1[2] * _vectorFP2[0]) - (_vectorFP1[0] * _vectorFP2[2]),
		(_vectorFP1[1] * _vectorFP2[2]) - (_vectorFP1[2] * _vectorFP2[1])
	);
}
vec4f vec4f::Cross(const __m128& _vectorSSE1, const __m128& _vectorSSE2) {
	return _mm_set_ps(
		0.0f,
		(GetSSEValue(_vectorSSE1, 0) * GetSSEValue(_vectorSSE2, 1)) - (GetSSEValue(_vectorSSE1, 1) * GetSSEValue(_vectorSSE2, 0)),
		(GetSSEValue(_vectorSSE1, 2) * GetSSEValue(_vectorSSE2, 0)) - (GetSSEValue(_vectorSSE1, 0) * GetSSEValue(_vectorSSE2, 2)),
		(GetSSEValue(_vectorSSE1, 1) * GetSSEValue(_vectorSSE2, 2)) - (GetSSEValue(_vectorSSE1, 2) * GetSSEValue(_vectorSSE2, 1))
	);
}
vec4f vec4f::Cross(const float* _vectorFP, const __m128& _vectorSSE) {
	return _mm_set_ps(
		0.0f,
		(_vectorFP[0] * GetSSEValue(_vectorSSE, 1)) - (_vectorFP[1] * GetSSEValue(_vectorSSE, 0)),
		(_vectorFP[2] * GetSSEValue(_vectorSSE, 0)) - (_vectorFP[0] * GetSSEValue(_vectorSSE, 2)),
		(_vectorFP[1] * GetSSEValue(_vectorSSE, 2)) - (_vectorFP[2] * GetSSEValue(_vectorSSE, 1))
	);
}
vec4f vec4f::Cross(const __m128& _vectorSSE, const float* _vectorFP) {
	return _mm_set_ps(
		0.0f,
		(GetSSEValue(_vectorSSE, 0) * _vectorFP[1]) - (GetSSEValue(_vectorSSE, 1) * _vectorFP[0]),
		(GetSSEValue(_vectorSSE, 2) * _vectorFP[0]) - (GetSSEValue(_vectorSSE, 0) * _vectorFP[2]),
		(GetSSEValue(_vectorSSE, 1) * _vectorFP[2]) - (GetSSEValue(_vectorSSE, 2) * _vectorFP[1])
	);
}

//Vector Normalize
void vec4f::Normalize() {
	//Get Length Squared
	float l = LengthSq();
	if (l == 0.0f)
		m128 = _mm_setzero_ps();
	else {
		l = 1 / sqrtf(l);
		m128 = _mm_mul_ps(m128, _mm_set1_ps(l));
	}
}
vec4f vec4f::Normalize(const vec4f& _vector) {
	//Get Length Squared
	float l = vec4f::LengthSq(_vector);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else {
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_vector.m128, _mm_set1_ps(l));
	}
}
vec4f vec4f::Normalize(const float* _vectorFP) {
	//Get Length Squared
	float l = vec4f::LengthSq(_vectorFP);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else {
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(l));
	}
}
vec4f vec4f::Normalize(const __m128& _vectorSSE) {
	//Get Length Squared
	float l = vec4f::LengthSq(_vectorSSE);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else {
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_vectorSSE, _mm_set1_ps(l));
	}
}

//Vector Homogenize (Perspective Divide)
void vec4f::Homogenize() {
	if (IsZero())
		m128 = _mm_setzero_ps();
	else
		m128 = _mm_div_ps(m128, _mm_set1_ps(w));
}
vec4f vec4f::Homogenize(const vec4f& _vector) { 
	if (vec4f::IsZero(_vector))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_vector.m128, _mm_set1_ps(_vector.w));
}
vec4f vec4f::Homogenize(const float* _vectorFP) {
	if (vec4f::IsZero(_vectorFP))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_mm_load_ps(_vectorFP), _mm_set1_ps(_vectorFP[3]));
}
vec4f vec4f::Homogenize(const __m128& _vectorSSE) {
	if (vec4f::IsZero(_vectorSSE))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_vectorSSE, _mm_set1_ps(GetSSEValue(_vectorSSE, 3)));
}

//Vector Angle Between
float vec4f::AngleBetween(const vec4f& _vector) const { 
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = Length() * _vector.Length();
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(Dot(_vector) / bot);
}
float vec4f::AngleBetween(const float* _vectorFP) const {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = Length() * vec4f::Length(_vectorFP);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(Dot(_vectorFP) / bot);
}
float vec4f::AngleBetween(const __m128& _vectorSSE) const {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = Length() * vec4f::Length(_vectorSSE);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(Dot(_vectorSSE) / bot);
}
float vec4f::AngleBetween(const vec4f& _vector1, const vec4f& _vector2) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vector1) * vec4f::Length(_vector2);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vector1, _vector2) / bot);
}
float vec4f::AngleBetween(const vec4f& _vector1, const float* _vectorFP) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vector1) * vec4f::Length(_vectorFP);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vector1, _vectorFP) / bot);
}
float vec4f::AngleBetween(const vec4f& _vector1, const __m128& _vectorSSE) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vector1) * vec4f::Length(_vectorSSE);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vector1, _vectorSSE) / bot);
}
float vec4f::AngleBetween(const float* _vectorFP, const vec4f& _vector2) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorFP) * vec4f::Length(_vector2);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorFP, _vector2) / bot);
}
float vec4f::AngleBetween(const __m128& _vectorSSE, const vec4f& _vector2) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorSSE) * vec4f::Length(_vector2);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorSSE, _vector2) / bot);
}

//Vector Angle Between Additions
float vec4f::AngleBetween(const float* _vectorFP1, const float* _vectorFP2) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorFP1) * vec4f::Length(_vectorFP2);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorFP1, _vectorFP2) / bot);
}
float vec4f::AngleBetween(const __m128& _vectorSSE1, const __m128& _vectorSSE2) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorSSE1) * vec4f::Length(_vectorSSE2);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorSSE1, _vectorSSE2) / bot);
}
float vec4f::AngleBetween(const float* _vectorFP, const __m128& _vectorSSE) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorFP) * vec4f::Length(_vectorSSE);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorFP, _vectorSSE) / bot);
}
float vec4f::AngleBetween(const __m128& _vectorSSE, const float* _vectorFP) {
	//Get the Two Lengths Multiplied (Zero Check)
	float bot = vec4f::Length(_vectorSSE) * vec4f::Length(_vectorFP);
	if (bot < FLT_EPSILON)
		return 0;
	return acosf(vec4f::Dot(_vectorSSE, _vectorFP) / bot);
}

//Vector Component
float vec4f::Component(const vec4f& _vector) const				 { return Dot(vec4f::Normalize(_vector)); }
float vec4f::Component(const float* _vectorFP) const				 { return Dot(vec4f::Normalize(_vectorFP)); }
float vec4f::Component(const __m128& _vectorSSE) const			 { return Dot(vec4f::Normalize(_vectorSSE)); }
float vec4f::Component(const vec4f& _vector1, const vec4f& _vector2)	 { return vec4f::Dot(_vector1, vec4f::Normalize(_vector2)); }
float vec4f::Component(const vec4f& _vector1, const float* _vectorFP)	 { return vec4f::Dot(_vector1, vec4f::Normalize(_vectorFP)); }
float vec4f::Component(const vec4f& _vector1, const __m128& _vectorSSE) { return vec4f::Dot(_vector1, vec4f::Normalize(_vectorSSE)); }
float vec4f::Component(const float* _vectorFP, const vec4f& _vector2)	 { return vec4f::Dot(_vectorFP, vec4f::Normalize(_vector2)); }
float vec4f::Component(const __m128& _vectorSSE, const vec4f& _vector2) { return vec4f::Dot(_vectorSSE, vec4f::Normalize(_vector2)); }

//Vector Component Additions
float vec4f::Component(const float* _vectorFP1, const float* _vectorFP2)		 { return vec4f::Dot(_vectorFP1, vec4f::Normalize(_vectorFP2)); }
float vec4f::Component(const __m128& _vectorSSE1, const __m128& _vectorSSE2) { return vec4f::Dot(_vectorSSE1, vec4f::Normalize(_vectorSSE2)); }
float vec4f::Component(const float* _vectorFP, const __m128& _vectorSSE)		 { return vec4f::Dot(_vectorFP, vec4f::Normalize(_vectorSSE)); }
float vec4f::Component(const __m128& _vectorSSE, const float* _vectorFP)		 { return vec4f::Dot(_vectorSSE, vec4f::Normalize(_vectorFP)); }

//Vector Project
void vec4f::Project(const vec4f& _vector)						{ vec4f norm = vec4f::Normalize(_vector);   m128 = vec4f::Mul(norm, Dot(norm)).m128; }
void vec4f::Project(const float* _vectorFP)						{ vec4f norm = vec4f::Normalize(_vectorFP);  m128 = vec4f::Mul(norm, Dot(norm)).m128; }
void vec4f::Project(const __m128& _vectorSSE)						{ vec4f norm = vec4f::Normalize(_vectorSSE); m128 = vec4f::Mul(norm, Dot(norm)).m128; }
vec4f vec4f::Project(const vec4f& _vector1, const vec4f& _vector2)	{ vec4f norm = vec4f::Normalize(_vector2);  return vec4f::Mul(norm, vec4f::Dot(_vector1, norm)); }
vec4f vec4f::Project(const vec4f& _vector1, const float* _vectorFP)	{ vec4f norm = vec4f::Normalize(_vectorFP);  return vec4f::Mul(norm, vec4f::Dot(_vector1, norm)); }
vec4f vec4f::Project(const vec4f& _vector1, const __m128& _vectorSSE)	{ vec4f norm = vec4f::Normalize(_vectorSSE); return vec4f::Mul(norm, vec4f::Dot(_vector1, norm)); }
vec4f vec4f::Project(const float* _vectorFP, const vec4f& _vector2)	{ vec4f norm = vec4f::Normalize(_vector2);  return vec4f::Mul(norm, vec4f::Dot(_vectorFP, norm)); }
vec4f vec4f::Project(const __m128& _vectorSSE, const vec4f& _vector2)	{ vec4f norm = vec4f::Normalize(_vector2);  return vec4f::Mul(norm, vec4f::Dot(_vectorSSE, norm)); }

//Vector Project Additions
vec4f vec4f::Project(const float* _vectorFP1, const float* _vectorFP2)		{ vec4f norm = vec4f::Normalize(_vectorFP2);  return vec4f::Mul(norm, vec4f::Dot(_vectorFP1, norm)); }
vec4f vec4f::Project(const __m128& _vectorSSE1, const __m128& _vectorSSE2)	{ vec4f norm = vec4f::Normalize(_vectorSSE2);  return vec4f::Mul(norm, vec4f::Dot(_vectorSSE1, norm)); }
vec4f vec4f::Project(const float* _vectorFP, const __m128& _vectorSSE)		{ vec4f norm = vec4f::Normalize(_vectorSSE); return vec4f::Mul(norm, vec4f::Dot(_vectorFP, norm)); }
vec4f vec4f::Project(const __m128& _vectorSSE, const float* _vectorFP)		{ vec4f norm = vec4f::Normalize(_vectorFP);  return vec4f::Mul(norm, vec4f::Dot(_vectorSSE, norm)); }

//Vector Reflect
void vec4f::Reflect(const vec4f& _vector) {
	if (_vector.IsZero()) {
		Negate();
		return;
	}
	m128 = _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(m128, _vector.m128).m128, _mm_set1_ps(-2.0f)), m128), _mm_set1_ps(NegativeZero.f));
}
void vec4f::Reflect(const float* _vectorFP) {
	if (vec4f::IsZero(_vectorFP)) {
		Negate();
		return;
	}
	m128 = _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(m128, _mm_load_ps(_vectorFP)).m128, _mm_set1_ps(-2.0f)), m128), _mm_set1_ps(NegativeZero.f));
}
void vec4f::Reflect(const __m128& _vectorSSE) {
	if (vec4f::IsZero(_vectorSSE)) {
		Negate();
		return;
	}
	*this = m128 = _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(m128, _vectorSSE).m128, _mm_set1_ps(-2.0f)), m128), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const vec4f& _vector1, const vec4f& _vector2) {
	if (vec4f::IsZero(_vector2))
		return vec4f::Negate(_vector1);
	return  _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vector1, _vector2).m128, _mm_set1_ps(-2.0f)), _vector1.m128), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const vec4f& _vector1, const float* _vectorFP) {
	if (vec4f::IsZero(_vectorFP))
		return vec4f::Negate(_vector1);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vector1, _vectorFP).m128, _mm_set1_ps(-2.0f)), _vector1.m128), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const vec4f& _vector1, const __m128& _vectorSSE) {
	if (vec4f::IsZero(_vectorSSE))
		return vec4f::Negate(_vector1);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vector1, _vectorSSE).m128, _mm_set1_ps(-2.0f)), _vector1.m128), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const float* _vectorFP, const vec4f& _vector2) {
	if (vec4f::IsZero(_vector2))
		return vec4f::Negate(_vectorFP);
	return  _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorFP, _vector2).m128, _mm_set1_ps(-2.0f)), _mm_load_ps(_vectorFP)), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const __m128& _vectorSSE, const vec4f& _vector2) {
	if (vec4f::IsZero(_vector2))
		return vec4f::Negate(_vectorSSE);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorSSE, _vector2).m128, _mm_set1_ps(-2.0f)), _vectorSSE), _mm_set1_ps(NegativeZero.f));
}

//Vector Reflect Additions
vec4f vec4f::Reflect(const float* _vectorFP1, const float* _vectorFP2) {
	if (vec4f::IsZero(_vectorFP2))
		return vec4f::Negate(_vectorFP1);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorFP1, _vectorFP2).m128, _mm_set1_ps(-2.0f)), _mm_load_ps(_vectorFP1)), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const __m128& _vectorSSE1, const __m128& _vectorSSE2) {
	if (vec4f::IsZero(_vectorSSE2))
		return vec4f::Negate(_vectorSSE1);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorSSE1, _vectorSSE2).m128, _mm_set1_ps(-2.0f)), _vectorSSE1), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const float* _vectorFP, const __m128& _vectorSSE) {
	if (vec4f::IsZero(_vectorSSE))
		return vec4f::Negate(_vectorFP);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorFP, _vectorSSE).m128, _mm_set1_ps(-2.0f)), _mm_load_ps(_vectorFP)), _mm_set1_ps(NegativeZero.f));
}
vec4f vec4f::Reflect(const __m128& _vectorSSE, const float* _vectorFP) {
	if (vec4f::IsZero(_vectorFP))
		return vec4f::Negate(_vectorSSE);
	return _mm_xor_ps(_mm_add_ps(_mm_mul_ps(vec4f::Project(_vectorSSE, _vectorFP).m128, _mm_set1_ps(-2.0f)), _vectorSSE), _mm_set1_ps(NegativeZero.f));
}

#undef CINT
