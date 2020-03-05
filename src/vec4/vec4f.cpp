#include "vec4f.h"
#include "../xplat.h"

#define CINT(x) static_cast<int>(x) //Cast to int (unsigned)

//Global Variables (Namespace)
namespace {
	static const vec4f vec4f_zero = {0.0f, 0.0f, 0.0f, 1.0f};
	static const float realZero[4] = {};
}

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
	//Create an "Equal" vector and do a parallel comparison with the vector parameter and itself
	vec4f eq = _mm_cmpeq_ps(_v1.m128, _v2.m128); 

	//return true if there is no 0 in any of the components.
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
void vec4f::Add(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::Add(const float* _fp) { *this = vec4f_zero; }
void vec4f::Add(const __m128& _sse) { *this = vec4f_zero; }
void vec4f::operator+=(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::operator+=(const float* _fp) { *this = vec4f_zero; }
void vec4f::operator+=(const __m128& _sse) { *this = vec4f_zero; }

//Vector-Vector Addition (Static & Global Operator Overloads)
vec4f vec4f::Add(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Add(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Add(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Add(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Add(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }
vec4f operator+(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f operator+(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f operator+(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f operator+(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f operator+(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }

//Vector-Vector Static Add Additions
vec4f vec4f::Add(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Add(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Add(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Add(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector-Vector Subtraction (Self & Self Operator Overloads)
void vec4f::Sub(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::Sub(const float* _fp) { *this = vec4f_zero; }
void vec4f::Sub(const __m128& _sse) { *this = vec4f_zero; }
void vec4f::operator-=(const vec4f& _v) { *this = vec4f_zero; }
void vec4f::operator-=(const float* _fp) { *this = vec4f_zero; }
void vec4f::operator-=(const __m128& _sse) { *this = vec4f_zero; }

//Vector-Vector Subtraction (Static & Global Operator Overloads)
vec4f vec4f::Sub(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Sub(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Sub(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Sub(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Sub(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }
vec4f operator-(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f operator-(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f operator-(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f operator-(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f operator-(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }

//Vector-Vector Static Subtraction Additions
vec4f vec4f::Sub(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Sub(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Sub(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Sub(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector-Scalar Multiply (Self & Self Operator Overload)
void vec4f::Mul(const float& _s) { *this = vec4f_zero; }
void vec4f::operator*=(const float& _s) { *this = vec4f_zero; }

//Vector-Scalar Multiply (Static & Global Operator Overload)
vec4f vec4f::Mul(const vec4f& _v, const float& _s) { return vec4f_zero; }
vec4f vec4f::Mul(const float* _fp, const float& _s) { return vec4f_zero; }
vec4f vec4f::Mul(const __m128& _sse, const float& _s) { return vec4f_zero; }
vec4f vec4f::Mul(const float& _s, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Mul(const float& _s, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Mul(const float& _s, const __m128& _sse) { return vec4f_zero; }
vec4f operator*(const vec4f& _v, const float& _s) { return vec4f_zero; }
vec4f operator*(const float& _s, const vec4f& _v) { return vec4f_zero; }

//Vector-Scalar Divide (Self & Self Operator Overload)
void vec4f::Div(const float& _s) { m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }
void vec4f::operator/=(const float& _s) { m128 = _mm_div_ps(m128, _mm_set1_ps(_s)); }

//Vector-Scalar Divide (Static & Global Operator Overload)
vec4f vec4f::Div(const vec4f& _v, const float& _s) { return _mm_div_ps(_v.m128, _mm_set1_ps(_s)); }
vec4f vec4f::Div(const float* _fp, const float& _s) { return _mm_div_ps(_mm_load_ps(_fp), _mm_set1_ps(_s)); }
vec4f vec4f::Div(const __m128& _sse, const float& _s) { return _mm_div_ps(_sse, _mm_set1_ps(_s)); }
vec4f operator/(const vec4f& _v, const float& _s) { return _mm_div_ps(_v.m128, _mm_set1_ps(_s)); }

//Vector Negate
void vec4f::Negate() { m128 = _mm_xor_ps(m128, _mm_set1_ps(-0.0f)); }
vec4f vec4f::operator-() { return _mm_xor_ps(m128, _mm_set1_ps(-0.0f)); }
vec4f vec4f::Negate(const vec4f& _v) { return _mm_xor_ps(_v.m128, _mm_set1_ps(-0.0f)); }
vec4f vec4f::Negate(const float* _fp) { return _mm_xor_ps(_mm_load_ps(_fp), _mm_set1_ps(-0.0f)); }
vec4f vec4f::Negate(const __m128& _sse) { return _mm_xor_ps(_sse, _mm_set1_ps(-0.0f)); }

//Vector Minimum (Per Component)
void vec4f::Min(const vec4f& _v) { *this = vec4f_zero; }
vec4f vec4f::Min(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Min(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Min(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Min(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Min(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }

//Vector Static Minimum Additions
vec4f vec4f::Min(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Min(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Min(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Min(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector Maximum (Per Component)
void vec4f::Max(const vec4f& _v) { *this = vec4f_zero; }
vec4f vec4f::Max(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Max(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Max(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Max(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Max(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }

//Vector Static Maximum Additions
vec4f vec4f::Max(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Max(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Max(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Max(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector Average (Per Component)
void vec4f::Average(const vec4f& _v) { *this = vec4f_zero; }
vec4f vec4f::Average(const vec4f& _v1, const vec4f& _v2) { return vec4f_zero; }
vec4f vec4f::Average(const vec4f& _v, const float* _fp) { return vec4f_zero; }
vec4f vec4f::Average(const float* _fp, const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Average(const vec4f& _v, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Average(const __m128& _sse, const vec4f& _v) { return vec4f_zero; }

//Vector Static Average Additions
vec4f vec4f::Average(const float* fp1, const float* fp2) { return vec4f_zero; }
vec4f vec4f::Average(const __m128& _sse1, const __m128& _sse2) { return vec4f_zero; }
vec4f vec4f::Average(const float* fp, const __m128& _sse) { return vec4f_zero; }
vec4f vec4f::Average(const __m128& _sse, const float* fp) { return vec4f_zero; }

//Vector Lengths
float vec4f::Length() { return 0.0f; }
float vec4f::Length(const vec4f& _v)  { return 0.0f; }
float vec4f::Length(const float* _fp)  { return 0.0f; }
float vec4f::Length(const __m128& _sse)  { return 0.0f; }

//Vector Length Squared
float vec4f::LengthSq() { return 0.0f; }
float vec4f::LengthSq(const vec4f& _v)  { return 0.0f; }
float vec4f::LengthSq(const float* _fp)  { return 0.0f; }
float vec4f::LengthSq(const __m128& _sse)  { return 0.0f; }

//Vector Dot Product
float vec4f::Dot(const vec4f& _v) { return 0.0f; }
float vec4f::Dot(const float* _fp) { return 0.0f; }
float vec4f::Dot(const __m128& _sse) { return 0.0f; }
float vec4f::Dot(const vec4f& _v1, const vec4f& _v2) { return 0.0f; }
float vec4f::Dot(const vec4f& _v1, const float* _fp) { return 0.0f; }
float vec4f::Dot(const vec4f& _v1, const __m128& _sse) { return 0.0f; }
float vec4f::Dot(const float* _fp, const vec4f& _v2) { return 0.0f; }
float vec4f::Dot(const __m128& _sse, const vec4f& _v2) { return 0.0f; }
float operator*(const vec4f& _v1, const vec4f& _v2) { return 0.0f; }
float operator*(const vec4f& _v1, const float* _fp) { return 0.0f; }
float operator*(const vec4f& _v1, const __m128& _sse) { return 0.0f; }
float operator*(const float* _fp, const vec4f& _v2) { return 0.0f; }
float operator*(const __m128& _sse, const vec4f& _v2) { return 0.0f; }

//Vector Dot Product Additions
float vec4f::Dot(const float* fp1, const float* fp2) { return 0.0f; }
float vec4f::Dot(const __m128& _sse1, const __m128& _sse2) { return 0.0f; }
float vec4f::Dot(const float* fp, const __m128& _sse) { return 0.0f; }
float vec4f::Dot(const __m128& _sse, const float* fp) { return 0.0f; }

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
void vec4f::Normalize() { *this = vec4f_zero; }
vec4f vec4f::Normalize(const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Normalize(const float* _fp) { return vec4f_zero; }
vec4f vec4f::Normalize(const __m128& _sse) { return vec4f_zero; }

//Vector Homogenize (Perspective Divide)
void vec4f::Homogenize() { *this = vec4f_zero; }
vec4f vec4f::Homogenize(const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Homogenize(const float* _fp) { return vec4f_zero; }
vec4f vec4f::Homogenize(const __m128& _sse) { return vec4f_zero; }

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
