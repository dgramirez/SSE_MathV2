#ifndef VEC4F_H
#define VEC4F_H

#include <xmmintrin.h>

struct vec4f {
	//Union between SSE, float Array and xyzw component
	union {
		__m128 m128;
		float e[4];
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float s, t, p, q; };
	};

	//Constructors and Assignment
	vec4f();
	vec4f(const float& _x, const float& _y, const float& _z, const float& _w);
	vec4f(const vec4f& _v);
	vec4f(const float* _fp);
	vec4f(const __m128& _sse);
	void operator=(const vec4f& _v);
	void operator=(const float* _fp);
	void operator=(const __m128& _sse);

	//Equality Check (Zero)
	bool IsZero();
	static bool IsZero(const vec4f& _v);
	static bool IsZero(const float* _fp);
	static bool IsZero(const __m128& _sse);

	//Equality Check
	bool IsEqual(const vec4f& _v);
	bool IsEqual(const float* _fp);
	bool IsEqual(const __m128& _sse);
	static bool IsEqual(const vec4f& _v1, const vec4f& _v2);
	static bool IsEqual(const vec4f& _v, const float* _fp);
	static bool IsEqual(const vec4f& _v, const __m128& _sse);
	static bool IsEqual(const float* _fp, const vec4f& _v);
	static bool IsEqual(const __m128& _sse, const vec4f& _v);

	//Equality Check (Operator Overload)
	friend bool operator==(const vec4f& _v1, const vec4f& _v2);
	friend bool operator==(const vec4f& _v, const float* _fp);
	friend bool operator==(const vec4f& _v, const __m128& _sse);
	friend bool operator==(const float* _fp, const vec4f& _v);
	friend bool operator==(const __m128& _sse, const vec4f& _v);

	//Inequality Check (Operator Overload)
	friend bool operator!=(const vec4f& _v1, const vec4f& _v2);
	friend bool operator!=(const vec4f& _v, const float* _fp);
	friend bool operator!=(const vec4f& _v, const __m128& _sse);
	friend bool operator!=(const float* _fp, const vec4f& _v);
	friend bool operator!=(const __m128& _sse, const vec4f& _v);

	//Vector-Vector Addition (Self & Self Operator Overloads)
	void Add(const vec4f& _v);
	void Add(const float* _fp);
	void Add(const __m128& _sse);
	void operator+=(const vec4f& _v);
	void operator+=(const float* _fp);
	void operator+=(const __m128& _sse);

	//Vector-Vector Addition (Static & Global Operator Overloads)
	static vec4f Add(const vec4f& _v1, const vec4f& _v2);
	static vec4f Add(const vec4f& _v, const float* _fp);
	static vec4f Add(const vec4f& _v, const __m128& _sse);
	static vec4f Add(const float* _fp, const vec4f& _v);
	static vec4f Add(const __m128& _sse, const vec4f& _v);
	friend vec4f operator+(const vec4f& _v1, const vec4f& _v2);
	friend vec4f operator+(const vec4f& _v, const float* _fp);
	friend vec4f operator+(const vec4f& _v, const __m128& _sse);
	friend vec4f operator+(const float* _fp, const vec4f& _v);
	friend vec4f operator+(const __m128& _sse, const vec4f& _v);

	//Vector-Vector Static Add Additions
	static vec4f Add(const float* fp1, const float* fp2);
	static vec4f Add(const __m128& _sse1, const __m128& _sse2);
	static vec4f Add(const float* fp, const __m128& _sse);
	static vec4f Add(const __m128& _sse, const float* fp);

	//Vector-Vector Subtraction (Self & Self Operator Overloads)
	void Sub(const vec4f& _v);
	void Sub(const float* _fp);
	void Sub(const __m128& _sse);
	void operator-=(const vec4f& _v);
	void operator-=(const float* _fp);
	void operator-=(const __m128& _sse);

	//Vector-Vector Subtraction (Static & Global Operator Overloads)
	static vec4f Sub(const vec4f& _v1, const vec4f& _v2);
	static vec4f Sub(const vec4f& _v, const float* _fp);
	static vec4f Sub(const vec4f& _v, const __m128& _sse);
	static vec4f Sub(const float* _fp, const vec4f& _v);
	static vec4f Sub(const __m128& _sse, const vec4f& _v);
	friend vec4f operator-(const vec4f& _v1, const vec4f& _v2);
	friend vec4f operator-(const vec4f& _v, const float* _fp);
	friend vec4f operator-(const vec4f& _v, const __m128& _sse);
	friend vec4f operator-(const float* _fp, const vec4f& _v);
	friend vec4f operator-(const __m128& _sse, const vec4f& _v);

	//Vector-Vector Static Subtraction Additions
	static vec4f Sub(const float* fp1, const float* fp2);
	static vec4f Sub(const __m128& _sse1, const __m128& _sse2);
	static vec4f Sub(const float* fp, const __m128& _sse);
	static vec4f Sub(const __m128& _sse, const float* fp);

	//Vector-Scalar Multiply (Self & Self Operator Overload)
	void Mul(const float& _s);
	void operator*=(const float& _s);

	//Vector-Scalar Multiply (Static & Global Operator Overload)
	static vec4f Mul(const vec4f& _v, const float& _s);
	static vec4f Mul(const float& _s, const vec4f& _v);
	static vec4f Mul(const float* _fp, const float& _s);
	static vec4f Mul(const float& _s, const float* _fp);
	static vec4f Mul(const __m128& _sse, const float& _s);
	static vec4f Mul(const float& _s, const __m128& _sse);
	friend vec4f operator*(const vec4f& _v, const float& _s);
	friend vec4f operator*(const float& _s, const vec4f& _v);

	//Vector-Scalar Divide (Self & Self Operator Overload)
	void Div(const float& _s);
	void operator/=(const float& _s);

	//Vector-Scalar Divide (Static & Global Operator Overload)
	static vec4f Div(const vec4f& _v, const float& _s);
	static vec4f Div(const float* _fp, const float& _s);
	static vec4f Div(const __m128& _sse, const float& _s);
	friend vec4f operator/(const vec4f& _v, const float& _s);

	//Vector Negate
	void Negate();
	vec4f operator-();
	static vec4f Negate(const vec4f& _v);
	static vec4f Negate(const float* _fp);
	static vec4f Negate(const __m128& _sse);

	//Vector Minimum (Per Component)
	void Min(const vec4f& _v);
	static vec4f Min(const vec4f& _v1, const vec4f& _v2);
	static vec4f Min(const vec4f& _v, const float* _fp);
	static vec4f Min(const float* _fp, const vec4f& _v);
	static vec4f Min(const vec4f& _v, const __m128& _sse);
	static vec4f Min(const __m128& _sse, const vec4f& _v);

	//Vector Maximum (Per Component)
	void Max(const vec4f& _v);
	static vec4f Max(const vec4f& _v1, const vec4f& _v2);
	static vec4f Max(const vec4f& _v, const float* _fp);
	static vec4f Max(const float* _fp, const vec4f& _v);
	static vec4f Max(const vec4f& _v, const __m128& _sse);
	static vec4f Max(const __m128& _sse, const vec4f& _v);

	//Vector Average (Per Component)
	void Average(const vec4f& _v);
	static vec4f Average(const vec4f& _v1, const vec4f& _v2);
	static vec4f Average(const vec4f& _v, const float* _fp);
	static vec4f Average(const float* _fp, const vec4f& _v);
	static vec4f Average(const vec4f& _v, const __m128& _sse);
	static vec4f Average(const __m128& _sse, const vec4f& _v);

	//Vector Length
	float Length();
	static float Length(const vec4f& _v);
	static float Length(const float* _fp);
	static float Length(const __m128& _sse);

	//Vector Length Squared
	float LengthSq();
	static float LengthSq(const vec4f& _v);
	static float LengthSq(const float* _fp);
	static float LengthSq(const __m128& _sse);

	//Vector Dot Product
	float Dot(const vec4f& _v);
	float Dot(const float* _fp);
	float Dot(const __m128& _sse);
	static float Dot(const vec4f& _v1, const vec4f& _v2);
	static float Dot(const vec4f& _v1, const float* _fp);
	static float Dot(const vec4f& _v1, const __m128& _sse);
	static float Dot(const float* _fp, const vec4f& _v2);
	static float Dot(const __m128& _sse, const vec4f& _v2);
	friend float operator*(const vec4f& _v1, const vec4f& _v2);
	friend float operator*(const vec4f& _v1, const float* _fp);
	friend float operator*(const vec4f& _v1, const __m128& _sse);
	friend float operator*(const float* _fp, const vec4f& _v2);
	friend float operator*(const __m128& _sse, const vec4f& _v2);

	//Vector Cross Product (Self & Self Operator Overloads)
	void Cross(const vec4f& _v);
	void Cross(const float* _fp);
	void Cross(const __m128& _sse);
	void operator^=(const vec4f& _v);
	void operator^=(const float* _fp);
	void operator^=(const __m128& _sse);

	//Vector Cross Product (Static & Global Operator Overloads)
	static vec4f Cross(const vec4f& _v1, const vec4f& _v2);
	static vec4f Cross(const vec4f& _v1, const float* _fp);
	static vec4f Cross(const vec4f& _v1, const __m128& _sse);
	static vec4f Cross(const float* _fp, const vec4f& _v2);
	static vec4f Cross(const __m128& _sse, const vec4f& _v2);
	friend vec4f operator^(const vec4f& _v1, const vec4f& _v2);
	friend vec4f operator^(const vec4f& _v1, const float* _fp);
	friend vec4f operator^(const vec4f& _v1, const __m128& _sse);
	friend vec4f operator^(const float* _fp, const vec4f& _v2);
	friend vec4f operator^(const __m128& _sse, const vec4f& _v2);

	//Vector Normalize
	void Normalize();
	static vec4f Normalize(const vec4f& _v);
	static vec4f Normalize(const float* _fp);
	static vec4f Normalize(const __m128& _sse);

	//Vector Homogenize (Perspective Divide)
	void Homogenize();
	static vec4f Homogenize(const vec4f& _v);
	static vec4f Homogenize(const float* _fp);
	static vec4f Homogenize(const __m128& _sse);

	//Vector Angle Between
	float AngleBetween(const vec4f& _v);
	float AngleBetween(const float* _fp);
	float AngleBetween(const __m128& _sse);
	static float AngleBetween(const vec4f& _v1, const vec4f& _v2);
	static float AngleBetween(const vec4f& _v1, const float* _fp);
	static float AngleBetween(const vec4f& _v1, const __m128& _sse);
	static float AngleBetween(const float* _fp, const vec4f& _v2);
	static float AngleBetween(const __m128& _sse, const vec4f& _v2);

	//Vector Component
	float Component(const vec4f& _v);
	float Component(const float* _fp);
	float Component(const __m128& _sse);
	static float Component(const vec4f& _v1, const vec4f& _v2);
	static float Component(const vec4f& _v1, const float* _fp);
	static float Component(const vec4f& _v1, const __m128& _sse);
	static float Component(const float* _fp, const vec4f& _v2);
	static float Component(const __m128& _sse, const vec4f& _v2);

	//Vector Project
	void Project(const vec4f& _v);
	void Project(const float* _fp);
	void Project(const __m128& _sse);
	static vec4f Project(const vec4f& _v1, const vec4f& _v2);
	static vec4f Project(const vec4f& _v1, const float* _fp);
	static vec4f Project(const vec4f& _v1, const __m128& _sse);
	static vec4f Project(const float* _fp, const vec4f& _v2);
	static vec4f Project(const __m128& _sse, const vec4f& _v2);

	//Vector Reflect
	void Reflect(const vec4f& _v);
	void Reflect(const float* _fp);
	void Reflect(const __m128& _sse);
	static vec4f Reflect(const vec4f& _v1, const vec4f& _v2);
	static vec4f Reflect(const vec4f& _v1, const float* _fp);
	static vec4f Reflect(const vec4f& _v1, const __m128& _sse);
	static vec4f Reflect(const float* _fp, const vec4f& _v2);
	static vec4f Reflect(const __m128& _sse, const vec4f& _v2);
};
#endif //VEC4F_H

#ifdef VEC4_FLOATS_GLOBAL
typedef vec4f vec4;
#endif