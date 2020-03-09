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
	float epsilon = FLT_EPSILON * 2;
	static inline float GetSSEValue(const __m128& _sse, const uint32_t& index) {
		#if defined(_WIN32)
		return _sse.m128_f32[index];
		#else
		return _sse[index];
		#endif
}
}

//Epsilon
void vec4f::ChangeEpsilon(const float& _epsilon) {
	epsilon = _epsilon < 0 ? FLT_EPSILON * 2 : _epsilon;
}
float vec4f::GetEpsilon() { return epsilon; }

//Getting SSE Values


//Constructor & Assignment
vec4f::vec4f() {
	//Set the m128 value to 0
	m128 = _mm_setzero_ps();
}
vec4f::vec4f(const float& _x, const float& _y, const float& _z, const float& _w) {
	//Set the m128 value to xyzw
	m128 = _mm_set_ps(_w, _z, _y, _x);
}
vec4f::vec4f(const vec4f& _v) {
	//Set the m128 value to the other vector's m128 value
	m128 = _v.m128;
}
vec4f::vec4f(const float* _fp) {
	//Load the float pointer to the m128 value
	m128 = _mm_load_ps(_fp);
}
vec4f::vec4f(const __m128& _sse) {
	//Set the m128 value to the parameter m128 value
	m128 = _sse;
}
void vec4f::operator=(const vec4f& _v) {
	//Assign the m128 value to the parameter vector's m128 value
	m128 = _v.m128;
}
void vec4f::operator=(const float* _fp) {
	//Assign the m128 to the float pointer loaded in as a m128
	m128 = _mm_load_ps(_fp);
}
void vec4f::operator=(const __m128& _sse) {
	//Assign the m128 value to the m128 parameter value
	m128 = _sse;
}
vec4f vec4f::Set(const float& _x, const float& _y, const float& _z, const float& _w) {
	//Set the m128 value to xyzw
	return _mm_set_ps(_w, _z, _y, _x);
}
vec4f vec4f::Set(const vec4f& _v) {
	//Set the m128 value to the other vector's m128 value
	return _v.m128;
}
vec4f vec4f::Set(const float* _fp) {
	//Load the float pointer to the m128 value
	return _mm_load_ps(_fp);
}
vec4f vec4f::Set(const __m128& _sse) {
	//Set the m128 value to the parameter m128 value
	return _sse;
}

//Vec4 Absolute Value
void vec4f::vabs() {
	//Toggle the negative bit
	m128 = _mm_and_ps(m128, m128PosNaN);
}
vec4f vec4f::vabs(const vec4f& _v) {
	//Toggle the negative bit
	return _mm_and_ps(_v.m128, _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}
vec4f vec4f::vabs(const float* _fp) {
	//Toggle the negative bit
	return _mm_and_ps(_mm_load_ps(_fp), _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}
vec4f vec4f::vabs(const __m128& _sse) {
	//Toggle the negative bit
	return _mm_and_ps(_sse, _mm_xor_ps(_mm_set1_ps(NegativeZero.f), _mm_set1_ps(MaxBits.f)));
}

//Equality Check (Zero)
bool vec4f::IsZero() const { 
	//Return the Comparison of the 0 vector to itself (0 == same bit value)
	return !memcmp(realZero, e, sizeof(vec4f));
}
bool vec4f::IsZero(const vec4f& _v) {
	//Return the Comparison of the 0 vector to the vector parameter (0 == same bit value)
	return !memcmp(realZero, _v.e, sizeof(vec4f));
}
bool vec4f::IsZero(const float* _fp) {
	//Return the Comparison of the 0 vector to the float pointer parameter (0 == same bit value)
	return !memcmp(realZero, _fp, sizeof(vec4f));
}
bool vec4f::IsZero(const __m128& _sse) {
	//Return the Comparison of the 0 vector to the m128 parameter (0 == same bit value)
	return !memcmp(realZero, &_sse, sizeof(vec4f));
}

//Equality Check
bool vec4f::IsEqual(const vec4f& _v) const {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps(m128, _v.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const float* _fp) const {
	//Create an "Equal" vector and do a parallel comparison with the float pointer parameter and itself
	vec4f eq = _mm_cmpeq_ps(m128, _mm_load_ps(_fp));

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const __m128& _sse) const { 
	//Create an "Equal" vector and do a parallel comparison with the m128 parameter and itself
	vec4f eq = _mm_cmpeq_ps(m128, _sse);

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const vec4f& _v1, const vec4f& _v2) {
	//Create an "Equal" vector and do a parallel comparison with the two vector parameters
	vec4f eq = _mm_cmpeq_ps(_v1.m128, _v2.m128);

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const vec4f& _v, const float* _fp) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and Float Pointer Parameter
	vec4f eq = _mm_cmpeq_ps(_v.m128, _mm_load_ps(_fp));
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const float* _fp, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the Float Pointer Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps( _mm_load_ps(_fp), _v.m128);

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const vec4f& _v, const __m128& _sse) {
	//Create an "Equal" vector and do a parallel comparison with the Vector Parameter and m128 Parameter
	vec4f eq = _mm_cmpeq_ps(_v.m128, _sse);
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const __m128& _sse, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the m128 Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps(_sse, _v.m128);
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}

//IsEqual Additions
bool vec4f::IsEqual(const float* _fp1, const float* _fp2) {
	//Create an "Equal" vector and do a parallel comparison with the m128 Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps(_mm_load_ps(_fp1), _mm_load_ps(_fp2));
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const __m128& _sse1, const __m128& _sse2) {
	//Create an "Equal" vector and do a parallel comparison with the m128 Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps(_sse1, _sse2);
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const float* _fp, const __m128& _sse) {
	//Create an "Equal" vector and do a parallel comparison with the m128 Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps(_mm_load_ps(_fp), _sse);
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool vec4f::IsEqual(const __m128& _sse, const float* _fp) {
	//Create an "Equal" vector and do a parallel comparison with the m128 Parameter and Vector Parameter
	vec4f eq = _mm_cmpeq_ps(_sse, _mm_load_ps(_fp));
	
	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}

//Equality Check (Operator Overload)
bool operator==(const vec4f& _v1, const vec4f& _v2) {
	//First Equality Check, Handles Infinities
	vec4f eq = _mm_cmpeq_ps(_v1.m128, _v2.m128);
	if (CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w))
		return true;

	//Absolute Value the vectors
	vec4f absV1 = vec4f::vabs(_v1);
	vec4f absV2 = vec4f::vabs(_v2);
	vec4f diff = vec4f::vabs(_v2 - _v1);

	//Second Equality Check: Near Zero
	vec4f minChk = _mm_cmplt_ps((absV1 + absV2).m128, _mm_set1_ps(FLT_MIN));
	if (_v1.IsZero() || _v2.IsZero() || (CINT(minChk.x) & CINT(minChk.y) & CINT(minChk.z) & CINT(minChk.w))) {
		eq = _mm_cmplt_ps(diff.m128, _mm_mul_ps(_mm_set1_ps(epsilon), _mm_set1_ps(FLT_MIN)));
		return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}

	//Final Equality Check: Relative
	eq = _mm_cmplt_ps(_mm_div_ps(diff.m128, vec4f::Min((absV1 + absV2), _mm_set1_ps(FLT_MAX)).m128), _mm_set1_ps(epsilon));
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator==(const vec4f& _v, const float* _fp) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps(_v.m128, _mm_load_ps(_fp)); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator==(const vec4f& _v, const __m128& _sse) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps(_v.m128, _sse); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator==(const float* _fp, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps(_mm_load_ps(_fp), _v.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator==(const __m128& _sse, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps( _sse, _v.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}

//Inequality Check (Operator Overload)
bool operator!=(const vec4f& _v1, const vec4f& _v2) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpneq_ps(_v1.m128, _v2.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator!=(const vec4f& _v, const float* _fp) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpneq_ps(_v.m128, _mm_load_ps(_fp)); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator!=(const vec4f& _v, const __m128& _sse) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpneq_ps(_v.m128, _sse); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator!=(const float* _fp, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpneq_ps(_mm_load_ps(_fp), _v.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}
bool operator!=(const __m128& _sse, const vec4f& _v) {
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpneq_ps( _sse, _v.m128); 

	//return true if there is no 0 in any of the components.
	return CINT(eq.x) & CINT(eq.y) & CINT(eq.z) & CINT(eq.w);
}

//Vector-Vector Addition (Self)
void vec4f::Add(const vec4f& _v)			{ m128 = _mm_add_ps(m128, _v.m128); }
void vec4f::Add(const float* _fp)			{ m128 = _mm_add_ps(m128, _mm_load_ps(_fp)); }
void vec4f::Add(const __m128& _sse)			{ m128 = _mm_add_ps(m128, _sse); }
void vec4f::operator+=(const vec4f& _v)		{ m128 = _mm_add_ps(m128, _v.m128); }
void vec4f::operator+=(const float* _fp)	{ m128 = _mm_add_ps(m128, _mm_load_ps(_fp)); }
void vec4f::operator+=(const __m128& _sse)	{ m128 = _mm_add_ps(m128, _sse); }

//Vector-Vector Addition (Static & Global Operator Overloads)
vec4f vec4f::Add(const vec4f& _v1, const vec4f& _v2)	{ return _mm_add_ps(_v1.m128, _v2.m128); }
vec4f vec4f::Add(const vec4f& _v, const float* _fp)		{ return _mm_add_ps(_v.m128, _mm_load_ps(_fp)); }
vec4f vec4f::Add(const vec4f& _v, const __m128& _sse)	{ return _mm_add_ps(_v.m128, _sse); }
vec4f vec4f::Add(const float* _fp, const vec4f& _v)		{ return _mm_add_ps(_mm_load_ps(_fp), _v.m128); }
vec4f vec4f::Add(const __m128& _sse, const vec4f& _v)	{ return _mm_add_ps(_sse, _v.m128); }
vec4f operator+(const vec4f& _v1, const vec4f& _v2)		{ return _mm_add_ps(_v1.m128, _v2.m128); }
vec4f operator+(const vec4f& _v, const float* _fp)		{ return _mm_add_ps(_v.m128, _mm_load_ps(_fp)); }
vec4f operator+(const vec4f& _v, const __m128& _sse)	{ return _mm_add_ps(_v.m128, _sse); }
vec4f operator+(const float* _fp, const vec4f& _v)		{ return _mm_add_ps(_mm_load_ps(_fp), _v.m128); }
vec4f operator+(const __m128& _sse, const vec4f& _v)	{ return _mm_add_ps(_sse, _v.m128); }

//Vector-Vector Static Add Additions
vec4f vec4f::Add(const float* fp1, const float* fp2)		{ return vec4f(_mm_add_ps(_mm_load_ps(fp1), _mm_load_ps(fp2))); }
vec4f vec4f::Add(const __m128& _sse1, const __m128& _sse2)	{ return vec4f(_mm_add_ps(_sse1, _sse2));; }
vec4f vec4f::Add(const float* fp, const __m128& _sse)		{ return vec4f(_mm_add_ps(_mm_load_ps(fp), _sse)); }
vec4f vec4f::Add(const __m128& _sse, const float* fp)		{ return vec4f(_mm_add_ps(_sse, _mm_load_ps(fp))); }

//Vector-Vector Subtraction (Self & Self Operator Overloads)
void vec4f::Sub(const vec4f& _v)			{ m128 = _mm_sub_ps(m128, _v.m128); }
void vec4f::Sub(const float* _fp)			{ m128 = _mm_sub_ps(m128, _mm_load_ps(_fp)); }
void vec4f::Sub(const __m128& _sse)			{ m128 = _mm_sub_ps(m128, _sse); }
void vec4f::operator-=(const vec4f& _v)		{ m128 = _mm_sub_ps(m128, _v.m128); }
void vec4f::operator-=(const float* _fp)	{ m128 = _mm_sub_ps(m128, _mm_load_ps(_fp)); }
void vec4f::operator-=(const __m128& _sse)	{ m128 = _mm_sub_ps(m128, _sse); }

//Vector-Vector Subtraction (Static & Global Operator Overloads)
vec4f vec4f::Sub(const vec4f& _v1, const vec4f& _v2)	{ return _mm_sub_ps(_v1.m128, _v2.m128); }
vec4f vec4f::Sub(const vec4f& _v, const float* _fp)		{ return _mm_sub_ps(_v.m128, _mm_load_ps(_fp)); }
vec4f vec4f::Sub(const vec4f& _v, const __m128& _sse)	{ return _mm_sub_ps(_v.m128, _sse); }
vec4f vec4f::Sub(const float* _fp, const vec4f& _v)		{ return _mm_sub_ps(_mm_load_ps(_fp), _v.m128); }
vec4f vec4f::Sub(const __m128& _sse, const vec4f& _v)	{ return _mm_sub_ps(_sse, _v.m128); }
vec4f operator-(const vec4f& _v1, const vec4f& _v2)		{ return _mm_sub_ps(_v1.m128, _v2.m128); }
vec4f operator-(const vec4f& _v, const float* _fp)		{ return _mm_sub_ps(_v.m128, _mm_load_ps(_fp)); }
vec4f operator-(const vec4f& _v, const __m128& _sse)	{ return _mm_sub_ps(_v.m128, _sse); }
vec4f operator-(const float* _fp, const vec4f& _v)		{ return _mm_sub_ps(_mm_load_ps(_fp), _v.m128); }
vec4f operator-(const __m128& _sse, const vec4f& _v)	{ return _mm_sub_ps(_sse, _v.m128); }

//Vector-Vector Static Subtraction Additions
vec4f vec4f::Sub(const float* fp1, const float* fp2)		{ return _mm_sub_ps(_mm_load_ps(fp1), _mm_load_ps(fp2)); }
vec4f vec4f::Sub(const __m128& _sse1, const __m128& _sse2)	{ return _mm_sub_ps(_sse1, _sse2);; }
vec4f vec4f::Sub(const float* fp, const __m128& _sse)		{ return _mm_sub_ps(_mm_load_ps(fp), _sse); }
vec4f vec4f::Sub(const __m128& _sse, const float* fp)		{ return _mm_sub_ps(_sse, _mm_load_ps(fp)); }

//Vector-Scalar Multiply (Self & Self Operator Overload)
void vec4f::Mul(const float& _s)		{ m128 = _mm_mul_ps(m128, _mm_set1_ps(_s)); }
void vec4f::operator*=(const float& _s) { m128 = _mm_mul_ps(m128, _mm_set1_ps(_s)); }

//Vector-Scalar Multiply (Static & Global Operator Overload)
vec4f vec4f::Mul(const vec4f& _v, const float& _s)		{ return _mm_mul_ps(_v.m128, _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const float* _fp, const float& _s)		{ return _mm_mul_ps(_mm_load_ps(_fp), _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const __m128& _sse, const float& _s)	{ return _mm_mul_ps(_sse, _mm_set1_ps(_s)); }
vec4f vec4f::Mul(const float& _s, const vec4f& _v)		{ return _mm_mul_ps(_mm_set1_ps(_s), _v.m128); }
vec4f vec4f::Mul(const float& _s, const float* _fp)		{ return _mm_mul_ps(_mm_set1_ps(_s), _mm_load_ps(_fp)); }
vec4f vec4f::Mul(const float& _s, const __m128& _sse)	{ return _mm_mul_ps(_mm_set1_ps(_s), _sse); }
vec4f operator*(const vec4f& _v, const float& _s)		{ return _mm_mul_ps(_v.m128, _mm_set1_ps(_s)); }
vec4f operator*(const float& _s, const vec4f& _v)		{ return _mm_mul_ps(_mm_set1_ps(_s), _v.m128); }

//Vector-Scalar Divide (Self & Self Operator Overload)
void vec4f::Div(const float& _s)		{ m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }
void vec4f::operator/=(const float& _s) { m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }

//Vector-Scalar Divide (Static & Global Operator Overload)
vec4f vec4f::Div(const vec4f& _v, const float& _s)		{ return _mm_div_ps(_v.m128, _mm_set1_ps(_s)); }
vec4f vec4f::Div(const float* _fp, const float& _s)		{ return _mm_div_ps(_mm_load_ps(_fp), _mm_set1_ps(_s)); }
vec4f vec4f::Div(const __m128& _sse, const float& _s)	{ return _mm_div_ps(_sse, _mm_set1_ps(_s)); }
vec4f operator/(const vec4f& _v, const float& _s)		{ return _mm_div_ps(_v.m128, _mm_set1_ps(_s)); }

//Vector Negate
void vec4f::Negate()					{ m128 = _mm_xor_ps(m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::operator-()				{ return _mm_xor_ps(m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const vec4f& _v)	{ return _mm_xor_ps(_v.m128, _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const float* _fp)	{ return _mm_xor_ps(_mm_load_ps(_fp), _mm_set1_ps(NegativeZero.f)); }
vec4f vec4f::Negate(const __m128& _sse) { return _mm_xor_ps(_sse, _mm_set1_ps(NegativeZero.f)); }

//Vector Minimum (Per Component)
void vec4f::Min(const vec4f& _v)						{ m128 = _mm_min_ps(m128, _v.m128); }
vec4f vec4f::Min(const vec4f& _v1, const vec4f& _v2)	{ return _mm_min_ps(_v1.m128, _v2.m128); }
vec4f vec4f::Min(const vec4f& _v, const float* _fp)		{ return _mm_min_ps(_v.m128, _mm_load_ps(_fp)); }
vec4f vec4f::Min(const float* _fp, const vec4f& _v)		{ return _mm_min_ps(_mm_load_ps(_fp), _v.m128); }
vec4f vec4f::Min(const vec4f& _v, const __m128& _sse)	{ return _mm_min_ps(_v.m128, _sse); }
vec4f vec4f::Min(const __m128& _sse, const vec4f& _v)	{ return _mm_min_ps(_sse, _v.m128); }

//Vector Static Minimum Additions
vec4f vec4f::Min(const float* fp1, const float* fp2)		{ return _mm_min_ps(_mm_load_ps(fp1), _mm_load_ps(fp2)); }
vec4f vec4f::Min(const __m128& _sse1, const __m128& _sse2)	{ return _mm_min_ps(_sse1, _sse2); }
vec4f vec4f::Min(const float* fp, const __m128& _sse)		{ return _mm_min_ps(_mm_load_ps(fp), _sse); }
vec4f vec4f::Min(const __m128& _sse, const float* fp)		{ return _mm_min_ps(_sse, _mm_load_ps(fp)); }

//Vector Maximum (Per Component)
void vec4f::Max(const vec4f& _v)						{ m128 = _mm_max_ps(m128, _v.m128); }
vec4f vec4f::Max(const vec4f& _v1, const vec4f& _v2)	{ return _mm_max_ps(_v1.m128, _v2.m128); }	
vec4f vec4f::Max(const vec4f& _v, const float* _fp)		{ return _mm_max_ps(_v.m128, _mm_load_ps(_fp)); }	
vec4f vec4f::Max(const float* _fp, const vec4f& _v)		{ return _mm_max_ps(_mm_load_ps(_fp), _v.m128); }	
vec4f vec4f::Max(const vec4f& _v, const __m128& _sse)	{ return _mm_max_ps(_v.m128, _sse); }	
vec4f vec4f::Max(const __m128& _sse, const vec4f& _v)	{ return _mm_max_ps(_sse, _v.m128); }	

//Vector Static Maximum Additions
vec4f vec4f::Max(const float* fp1, const float* fp2)		{ return _mm_max_ps(_mm_load_ps(fp1), _mm_load_ps(fp2)); }
vec4f vec4f::Max(const __m128& _sse1, const __m128& _sse2)	{ return _mm_max_ps(_sse1, _sse2); }
vec4f vec4f::Max(const float* fp, const __m128& _sse)		{ return _mm_max_ps(_mm_load_ps(fp), _sse); }
vec4f vec4f::Max(const __m128& _sse, const float* fp)		{ return _mm_max_ps(_sse, _mm_load_ps(fp)); }

//Vector Average (Per Component)
void vec4f::Average(const vec4f& _v)						{ m128 = _mm_mul_ps(_mm_add_ps(m128, _v.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _v1, const vec4f& _v2)	{ return _mm_mul_ps(_mm_add_ps(_v1.m128, _v2.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _v, const float* _fp)		{ return _mm_mul_ps(_mm_add_ps(_v.m128, _mm_load_ps(_fp)), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const float* _fp, const vec4f& _v)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(_fp), _v.m128), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const vec4f& _v, const __m128& _sse)	{ return _mm_mul_ps(_mm_add_ps(_v.m128, _sse), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _sse, const vec4f& _v)	{ return _mm_mul_ps(_mm_add_ps(_sse, _v.m128), _mm_set1_ps(0.5f)); }

//Vector Static Average Additions
vec4f vec4f::Average(const float* fp1, const float* fp2)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(fp1), _mm_load_ps(fp2)), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _sse1, const __m128& _sse2)	{ return _mm_mul_ps(_mm_add_ps(_sse1, _sse2), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const float* fp, const __m128& _sse)		{ return _mm_mul_ps(_mm_add_ps(_mm_load_ps(fp), _sse), _mm_set1_ps(0.5f)); }
vec4f vec4f::Average(const __m128& _sse, const float* fp)		{ return _mm_mul_ps(_mm_add_ps(_sse, _mm_load_ps(fp)), _mm_set1_ps(0.5f)); }

//Vector Lengths
float vec4f::Length()					{ vec4f sq = _mm_mul_ps(m128, m128); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const vec4f& _v)	{ vec4f sq = _mm_mul_ps(_v.m128, _v.m128); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const float* _fp)	{ vec4f sq = _mm_mul_ps(_mm_load_ps(_fp), _mm_load_ps(_fp)); return sqrtf(sq.x + sq.y + sq.z + sq.w); }
float vec4f::Length(const __m128& _sse)	{ vec4f sq = _mm_mul_ps(_sse, _sse); return sqrtf(sq.x + sq.y + sq.z + sq.w); }

//Vector Length Squared
float vec4f::LengthSq()						{ vec4f sq = _mm_mul_ps(m128, m128); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const vec4f& _v)		{ vec4f sq = _mm_mul_ps(_v.m128, _v.m128); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const float* _fp)		{ vec4f sq = _mm_mul_ps(_mm_load_ps(_fp), _mm_load_ps(_fp)); return sq.x + sq.y + sq.z + sq.w; }
float vec4f::LengthSq(const __m128& _sse)	{ vec4f sq = _mm_mul_ps(_sse, _sse); return sq.x + sq.y + sq.z + sq.w; }

//Vector Dot Product
float vec4f::Dot(const vec4f& _v)						{ vec4f m = _mm_mul_ps(m128, _v.m128);	return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* _fp)						{ vec4f m = _mm_mul_ps(m128, _mm_load_ps(_fp)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _sse)					{ vec4f m = _mm_mul_ps(m128, _sse);	return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _v1, const vec4f& _v2)	{ vec4f m = _mm_mul_ps(_v1.m128, _v2.m128); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _v1, const float* _fp)	{ vec4f m = _mm_mul_ps(_v1.m128, _mm_load_ps(_fp)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const vec4f& _v1, const __m128& _sse)	{ vec4f m = _mm_mul_ps(_v1.m128, _sse); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* _fp, const vec4f& _v2)	{ vec4f m = _mm_mul_ps(_mm_load_ps(_fp), _v2.m128); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _sse, const vec4f& _v2)	{ vec4f m = _mm_mul_ps(_sse, _v2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _v1, const vec4f& _v2)		{ vec4f m = _mm_mul_ps(_v1.m128, _v2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _v1, const float* _fp)		{ vec4f m = _mm_mul_ps(_v1.m128, _mm_load_ps(_fp)); return m.x + m.y + m.z + m.w; }
float operator*(const vec4f& _v1, const __m128& _sse)	{ vec4f m = _mm_mul_ps(_v1.m128, _sse); return m.x + m.y + m.z + m.w; }
float operator*(const float* _fp, const vec4f& _v2)		{ vec4f m = _mm_mul_ps(_mm_load_ps(_fp), _v2.m128); return m.x + m.y + m.z + m.w; }
float operator*(const __m128& _sse, const vec4f& _v2)	{ vec4f m = _mm_mul_ps(_sse, _v2.m128); return m.x + m.y + m.z + m.w; }

//Vector Dot Product Additions
float vec4f::Dot(const float* fp1, const float* fp2)		{ vec4f m = _mm_mul_ps(_mm_load_ps(fp1), _mm_load_ps(fp2)); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _sse1, const __m128& _sse2)	{ vec4f m = _mm_mul_ps(_sse1, _sse2); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const float* fp, const __m128& _sse)		{ vec4f m = _mm_mul_ps(_mm_load_ps(fp), _sse); return m.x + m.y + m.z + m.w; }
float vec4f::Dot(const __m128& _sse, const float* fp)		{ vec4f m = _mm_mul_ps(_sse, _mm_load_ps(fp)); return m.x + m.y + m.z + m.w; }

//Vector Cross Product (Self & Self Operator Overloads)
void vec4f::Cross(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::Cross(const float* _fp) { *this = vec4f_zero; }
void vec4f::Cross(const __m128& _sse) { *this = vec4f_zero; }
void vec4f::operator^=(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::operator^=(const float* _fp) { *this = vec4f_zero; }
void vec4f::operator^=(const __m128& _sse) { *this = vec4f_zero; }

//Vector Cross Product (Static & Global Operator Overloads)
vec4f vec4f::Cross(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Cross(const vec4f& _v1, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Cross(const vec4f& _v1, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Cross(const float* _fp, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Cross(const __m128& _sse, const vec4f& _v2) { return vec4f_zero; }
vec4f operator^(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f operator^(const vec4f& _v1, const float* _fp) { return vec4f_zero; }
vec4f operator^(const vec4f& _v1, const __m128& _sse) { return vec4f_zero; }
vec4f operator^(const float* _fp, const vec4f& _v2) { return vec4f_zero; }
vec4f operator^(const __m128& _sse, const vec4f& _v2) { return vec4f_zero; }

//Vector Cross Product Additions
vec4f vec4f::Cross(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Cross(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Cross(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Cross(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector Normalize
void vec4f::Normalize() {
	//Get Length Squared
	float l = LengthSq();
	if (l == 0.0f)
		m128 = _mm_setzero_ps();
	else
	{
		l = 1 / sqrtf(l);
		m128 = _mm_mul_ps(m128, _mm_set1_ps(l));
}
}
vec4f vec4f::Normalize(const vec4f& _v) {
	//Get Length Squared
	float l = vec4f::LengthSq(_v);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else
	{
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_v.m128, _mm_set1_ps(l));
}
}
vec4f vec4f::Normalize(const float* _fp) {
	//Get Length Squared
	float l = vec4f::LengthSq(_fp);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else
	{
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_mm_load_ps(_fp), _mm_set1_ps(l));
}
}
vec4f vec4f::Normalize(const __m128& _sse) {
	//Get Length Squared
	float l = vec4f::LengthSq(_sse);
	if (l == 0.0f)
		return _mm_setzero_ps();
	else
	{
		l = 1 / sqrtf(l);
		return _mm_mul_ps(_sse, _mm_set1_ps(l));
}
}

//Vector Homogenize (Perspective Divide)
void vec4f::Homogenize() {
	if (IsZero())
		m128 = _mm_setzero_ps();
	else
		m128 = _mm_div_ps(m128, _mm_set1_ps(w));
}
vec4f vec4f::Homogenize(const vec4f& _v) { 
	if (vec4f::IsZero(_v))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_v.m128, _mm_set1_ps(_v.w));
}
vec4f vec4f::Homogenize(const float* _fp) {
	if (vec4f::IsZero(_fp))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_mm_load_ps(_fp), _mm_set1_ps(_fp[3]));
}
vec4f vec4f::Homogenize(const __m128& _sse) {
	if (vec4f::IsZero(_sse))
		return _mm_setzero_ps();
	else
		return _mm_div_ps(_sse, _mm_set1_ps(GetSSEValue(_sse, 3)));
}

//Vector Angle Between
float vec4f::AngleBetween(const vec4f& _v) { return 0.0f; }
float vec4f::AngleBetween(const float* _fp) { return 0.0f; }
float vec4f::AngleBetween(const __m128& _sse) { return 0.0f; }
float vec4f::AngleBetween(const vec4f& _v1, const vec4f& _v2) { return 0.0f; }
float vec4f::AngleBetween(const vec4f& _v1, const float* _fp) { return 0.0f; }
float vec4f::AngleBetween(const vec4f& _v1, const __m128& _sse) { return 0.0f; }
float vec4f::AngleBetween(const float* _fp, const vec4f& _v2) { return 0.0f; }
float vec4f::AngleBetween(const __m128& _sse, const vec4f& _v2) { return 0.0f; }

//Vector Angle Between Additions
float vec4f::AngleBetween(const float* fp1, const float* fp2) { return 0.0f; }
float vec4f::AngleBetween(const __m128& _sse1, const __m128& _sse2) { return 0.0f; }
float vec4f::AngleBetween(const float* fp, const __m128& _sse) { return 0.0f; }
float vec4f::AngleBetween(const __m128& _sse, const float* fp) { return 0.0f; }

//Vector Component
float vec4f::Component(const vec4f& _v) { return 0.0f; }
float vec4f::Component(const float* _fp) { return 0.0f; }
float vec4f::Component(const __m128& _sse) { return 0.0f; }
float vec4f::Component(const vec4f& _v1, const vec4f& _v2) { return 0.0f; }
float vec4f::Component(const vec4f& _v1, const float* _fp) { return 0.0f; }
float vec4f::Component(const vec4f& _v1, const __m128& _sse) { return 0.0f; }
float vec4f::Component(const float* _fp, const vec4f& _v2) { return 0.0f; }
float vec4f::Component(const __m128& _sse, const vec4f& _v2) { return 0.0f; }

//Vector Component Additions
float vec4f::Component(const float* fp1, const float* fp2) { return 0.0f; }
float vec4f::Component(const __m128& _sse1, const __m128& _sse2) { return 0.0f; }
float vec4f::Component(const float* fp, const __m128& _sse) { return 0.0f; }
float vec4f::Component(const __m128& _sse, const float* fp) { return 0.0f; }

//Vector Project
void vec4f::Project(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::Project(const float* _fp) { *this = vec4f_zero; }
void vec4f::Project(const __m128& _sse) { *this = vec4f_zero; }
vec4f vec4f::Project(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Project(const vec4f& _v1, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Project(const vec4f& _v1, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Project(const float* _fp, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Project(const __m128& _sse, const vec4f& _v2) { return vec4f_zero; }

//Vector Project Additions
vec4f vec4f::Project(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Project(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Project(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Project(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector Reflect
void vec4f::Reflect(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::Reflect(const float* _fp) { *this = vec4f_zero; }
void vec4f::Reflect(const __m128& _sse) { *this = vec4f_zero; }
vec4f vec4f::Reflect(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Reflect(const vec4f& _v1, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Reflect(const vec4f& _v1, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Reflect(const float* _fp, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Reflect(const __m128& _sse, const vec4f& _v2) { return vec4f_zero; }

//Vector Reflect Additions
vec4f vec4f::Reflect(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Reflect(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Reflect(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Reflect(const __m128& _sse, const float* fp) { return vec4f_zero; }

#undef CINT
