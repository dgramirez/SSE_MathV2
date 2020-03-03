#include "vec4f.h"

//Global Variables (Namespace)
namespace {
	static const vec4f vec4f_zero = {};
}

//Constructor & Assignment
vec4f::vec4f() { m128 = _mm_setzero_ps(); }
vec4f::vec4f(const float& _x, const float& _y, const float& _z, const float& _w) { m128 = _mm_set_ps(_w, _z, _y, _x); }
vec4f::vec4f(const vec4f& _v) { m128 = _v.m128; }
vec4f::vec4f(const float* _fp) { m128 = _mm_load_ps(_fp); }
vec4f::vec4f(const __m128& _sse) { m128 = _sse; }
void vec4f::operator=(const vec4f& _v) { m128 = _v.m128; }
void vec4f::operator=(const float* _fp) { m128 = _mm_load_ps(_fp); }
void vec4f::operator=(const __m128& _sse) { m128 = _sse; }

//Equality Check (Zero)
bool vec4f::IsZero() { return false; }
bool vec4f::IsZero(const vec4f& _v) { return false; }
bool vec4f::IsZero(const float* _fp) { return false; }
bool vec4f::IsZero(const __m128& _sse) { return false; }

//Equality Check
bool vec4f::IsEqual(const vec4f& _v) { return false; }
bool vec4f::IsEqual(const float* _fp) { return false; }
bool vec4f::IsEqual(const __m128& _sse) { return false; }
bool vec4f::IsEqual(const vec4f& _v1, const vec4f& _v2) { return false; }
bool vec4f::IsEqual(const vec4f& _v, const float* _fp) { return false; }
bool vec4f::IsEqual(const vec4f& _v, const __m128& _sse) { return false; }
bool vec4f::IsEqual(const float* _fp, const vec4f& _v) { return false; }
bool vec4f::IsEqual(const __m128& _sse, const vec4f& _v) { return false; }

//Equality Check (Operator Overload)
bool operator==(const vec4f& _v1, const vec4f& _v2) { return false; }
bool operator==(const vec4f& _v, const float* _fp) { return false; }
bool operator==(const vec4f& _v, const __m128& _sse) { return false; }
bool operator==(const float* _fp, const vec4f& _v) { return false; }
bool operator==(const __m128& _sse, const vec4f& _v) { return false; }

//Inequality Check (Operator Overload)
bool operator!=(const vec4f& _v1, const vec4f& _v2) { return false; }
bool operator!=(const vec4f& _v, const float* _fp) { return false; }
bool operator!=(const vec4f& _v, const __m128& _sse) { return false; }
bool operator!=(const float* _fp, const vec4f& _v) { return false; }
bool operator!=(const __m128& _sse, const vec4f& _v) { return false; }

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
void vec4f::Div(const float& _s) { *this = vec4f_zero; }
void vec4f::operator/=(const float& _s) { *this = vec4f_zero; }

//Vector-Scalar Divide (Static & Global Operator Overload)
vec4f vec4f::Div(const vec4f& _v, const float& _s) { return vec4f_zero; }
vec4f vec4f::Div(const float* _fp, const float& _s) { return vec4f_zero; }
vec4f vec4f::Div(const __m128& _sse, const float& _s) { return vec4f_zero; }
vec4f operator/(const vec4f& _v, const float& _s) { return vec4f_zero; }

//Vector Negate
void vec4f::Negate() { *this = vec4f_zero; }
vec4f vec4f::operator-() { return vec4f_zero; }
vec4f vec4f::Negate(const vec4f& _v) { return vec4f_zero; }
vec4f vec4f::Negate(const float* _fp) { return vec4f_zero; }
vec4f vec4f::Negate(const __m128& _sse) { return vec4f_zero; }

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
