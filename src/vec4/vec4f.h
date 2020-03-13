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
	vec4f(const vec4f& _vector);
	vec4f(const float* _vectorFP);
	vec4f(const __m128& _vectorSSE);
	void operator=(const vec4f& _vector);
	void operator=(const float* _vectorFP);
	void operator=(const __m128& _vectorSSE);
	static vec4f Set(const float& _x, const float& _y, const float& _z, const float& _w);
	static vec4f Set(const vec4f& _vector);
	static vec4f Set(const float* _vectorFP);
	static vec4f Set(const __m128& _vectorSSE);

	//Vec4 Absolute Value
	void vabs();
	static vec4f vabs(const vec4f& _vector);
	static vec4f vabs(const float* _vectorFP);
	static vec4f vabs(const __m128& _vectorSSE);

	//Equality Check (Zero)
	bool IsZero() const;
	static bool IsZero(const vec4f& _vector);
	static bool IsZero(const float* _vectorFP);
	static bool IsZero(const __m128& _vectorSSE);

	//Equality Check
	bool IsEqual(const vec4f& _vector) const;
	bool IsEqual(const float* _vectorFP) const;
	bool IsEqual(const __m128& _vectorSSE) const;
	static bool IsEqual(const vec4f& _vector1, const vec4f& _vector2);
	static bool IsEqual(const vec4f& _vector, const float* _vectorFP);
	static bool IsEqual(const vec4f& _vector, const __m128& _vectorSSE);
	static bool IsEqual(const float* _vectorFP, const vec4f& _vector);
	static bool IsEqual(const __m128& _vectorSSE, const vec4f& _vector);

	//IsEqual Additions
	static bool IsEqual(const float* _vectorFP1, const float* _vectorFP2);
	static bool IsEqual(const __m128& _sse1, const __m128& _sse2);
	static bool IsEqual(const float* _vectorFP, const __m128& _vectorSSE);
	static bool IsEqual(const __m128& _vectorSSE, const float* _vectorFP);

	//Equality Check (Operator Overload)
	friend bool operator==(const vec4f& _vector1, const vec4f& _vector2);
	friend bool operator==(const vec4f& _vector, const float* _vectorFP);
	friend bool operator==(const vec4f& _vector, const __m128& _vectorSSE);
	friend bool operator==(const float* _vectorFP, const vec4f& _vector);
	friend bool operator==(const __m128& _vectorSSE, const vec4f& _vector);

	//Inequality Check (Operator Overload)
	friend bool operator!=(const vec4f& _vector1, const vec4f& _vector2);
	friend bool operator!=(const vec4f& _vector, const float* _vectorFP);
	friend bool operator!=(const vec4f& _vector, const __m128& _vectorSSE);
	friend bool operator!=(const float* _vectorFP, const vec4f& _vector);
	friend bool operator!=(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector-Vector Addition (Self & Self Operator Overloads)
	void Add(const vec4f& _vector);
	void Add(const float* _vectorFP);
	void Add(const __m128& _vectorSSE);
	void operator+=(const vec4f& _vector);
	void operator+=(const float* _vectorFP);
	void operator+=(const __m128& _vectorSSE);

	//Vector-Vector Addition (Static & Global Operator Overloads)
	static vec4f Add(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Add(const vec4f& _vector, const float* _vectorFP);
	static vec4f Add(const vec4f& _vector, const __m128& _vectorSSE);
	static vec4f Add(const float* _vectorFP, const vec4f& _vector);
	static vec4f Add(const __m128& _vectorSSE, const vec4f& _vector);
	friend vec4f operator+(const vec4f& _vector1, const vec4f& _vector2);
	friend vec4f operator+(const vec4f& _vector, const float* _vectorFP);
	friend vec4f operator+(const vec4f& _vector, const __m128& _vectorSSE);
	friend vec4f operator+(const float* _vectorFP, const vec4f& _vector);
	friend vec4f operator+(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector-Vector Static Add Additions
	static vec4f Add(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Add(const __m128& _sse1, const __m128& _sse2);
	static vec4f Add(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Add(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector-Vector Subtraction (Self & Self Operator Overloads)
	void Sub(const vec4f& _vector);
	void Sub(const float* _vectorFP);
	void Sub(const __m128& _vectorSSE);
	void operator-=(const vec4f& _vector);
	void operator-=(const float* _vectorFP);
	void operator-=(const __m128& _vectorSSE);

	//Vector-Vector Subtraction (Static & Global Operator Overloads)
	static vec4f Sub(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Sub(const vec4f& _vector, const float* _vectorFP);
	static vec4f Sub(const vec4f& _vector, const __m128& _vectorSSE);
	static vec4f Sub(const float* _vectorFP, const vec4f& _vector);
	static vec4f Sub(const __m128& _vectorSSE, const vec4f& _vector);
	friend vec4f operator-(const vec4f& _vector1, const vec4f& _vector2);
	friend vec4f operator-(const vec4f& _vector, const float* _vectorFP);
	friend vec4f operator-(const vec4f& _vector, const __m128& _vectorSSE);
	friend vec4f operator-(const float* _vectorFP, const vec4f& _vector);
	friend vec4f operator-(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector-Vector Static Subtraction Additions
	static vec4f Sub(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Sub(const __m128& _sse1, const __m128& _sse2);
	static vec4f Sub(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Sub(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector-Scalar Multiply (Self & Self Operator Overload)
	void Mul(const float& _scalar);
	void operator*=(const float& _scalar);

	//Vector-Scalar Multiply (Static & Global Operator Overload)
	static vec4f Mul(const vec4f& _vector, const float& _scalar);
	static vec4f Mul(const float& _scalar, const vec4f& _vector);
	static vec4f Mul(const float* _vectorFP, const float& _scalar);
	static vec4f Mul(const float& _scalar, const float* _vectorFP);
	static vec4f Mul(const __m128& _vectorSSE, const float& _scalar);
	static vec4f Mul(const float& _scalar, const __m128& _vectorSSE);
	friend vec4f operator*(const vec4f& _vector, const float& _scalar);
	friend vec4f operator*(const float& _scalar, const vec4f& _vector);

	//Vector-Scalar Divide (Self & Self Operator Overload)
	void Div(const float& _scalar);
	void operator/=(const float& _scalar);

	//Vector-Scalar Divide (Static & Global Operator Overload)
	static vec4f Div(const vec4f& _vector, const float& _scalar);
	static vec4f Div(const float* _vectorFP, const float& _scalar);
	static vec4f Div(const __m128& _vectorSSE, const float& _scalar);
	friend vec4f operator/(const vec4f& _vector, const float& _scalar);

	//Vector Negate
	void Negate();
	vec4f operator-();
	static vec4f Negate(const vec4f& _vector);
	static vec4f Negate(const float* _vectorFP);
	static vec4f Negate(const __m128& _vectorSSE);

	//Vector Minimum (Per Component)
	void Min(const vec4f& _vector);
	static vec4f Min(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Min(const vec4f& _vector, const float* _vectorFP);
	static vec4f Min(const float* _vectorFP, const vec4f& _vector);
	static vec4f Min(const vec4f& _vector, const __m128& _vectorSSE);
	static vec4f Min(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector Static Minimum Additions
	static vec4f Min(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Min(const __m128& _sse1, const __m128& _sse2);
	static vec4f Min(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Min(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Maximum (Per Component)
	void Max(const vec4f& _vector);
	static vec4f Max(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Max(const vec4f& _vector, const float* _vectorFP);
	static vec4f Max(const float* _vectorFP, const vec4f& _vector);
	static vec4f Max(const vec4f& _vector, const __m128& _vectorSSE);
	static vec4f Max(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector Static Maximum Additions
	static vec4f Max(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Max(const __m128& _sse1, const __m128& _sse2);
	static vec4f Max(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Max(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Average (Per Component)
	void Average(const vec4f& _vector);
	static vec4f Average(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Average(const vec4f& _vector, const float* _vectorFP);
	static vec4f Average(const float* _vectorFP, const vec4f& _vector);
	static vec4f Average(const vec4f& _vector, const __m128& _vectorSSE);
	static vec4f Average(const __m128& _vectorSSE, const vec4f& _vector);

	//Vector Static Average Additions
	static vec4f Average(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Average(const __m128& _sse1, const __m128& _sse2);
	static vec4f Average(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Average(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Length
	float Length() const;
	static float Length(const vec4f& _vector);
	static float Length(const float* _vectorFP);
	static float Length(const __m128& _vectorSSE);

	//Vector Length Squared
	float LengthSq() const;
	static float LengthSq(const vec4f& _vector);
	static float LengthSq(const float* _vectorFP);
	static float LengthSq(const __m128& _vectorSSE);

	//Vector Dot Product
	float Dot(const vec4f& _vector) const;
	float Dot(const float* _vectorFP) const;
	float Dot(const __m128& _vectorSSE) const;
	static float Dot(const vec4f& _vector1, const vec4f& _vector2);
	static float Dot(const vec4f& _vector1, const float* _vectorFP);
	static float Dot(const vec4f& _vector1, const __m128& _vectorSSE);
	static float Dot(const float* _vectorFP, const vec4f& _vector2);
	static float Dot(const __m128& _vectorSSE, const vec4f& _vector2);
	friend float operator*(const vec4f& _vector1, const vec4f& _vector2);
	friend float operator*(const vec4f& _vector1, const float* _vectorFP);
	friend float operator*(const vec4f& _vector1, const __m128& _vectorSSE);
	friend float operator*(const float* _vectorFP, const vec4f& _vector2);
	friend float operator*(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Dot Product Additions
	static float Dot(const float* _vectorFP1, const float* _vectorFP2);
	static float Dot(const __m128& _sse1, const __m128& _sse2);
	static float Dot(const float* _vectorFP, const __m128& _vectorSSE);
	static float Dot(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Cross Product (Self & Self Operator Overloads)
	void Cross(const vec4f& _vector);
	void Cross(const float* _vectorFP);
	void Cross(const __m128& _vectorSSE);
	void operator^=(const vec4f& _vector);
	void operator^=(const float* _vectorFP);
	void operator^=(const __m128& _vectorSSE);

	//Vector Cross Product (Static & Global Operator Overloads)
	static vec4f Cross(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Cross(const vec4f& _vector1, const float* _vectorFP);
	static vec4f Cross(const vec4f& _vector1, const __m128& _vectorSSE);
	static vec4f Cross(const float* _vectorFP, const vec4f& _vector2);
	static vec4f Cross(const __m128& _vectorSSE, const vec4f& _vector2);
	friend vec4f operator^(const vec4f& _vector1, const vec4f& _vector2);
	friend vec4f operator^(const vec4f& _vector1, const float* _vectorFP);
	friend vec4f operator^(const vec4f& _vector1, const __m128& _vectorSSE);
	friend vec4f operator^(const float* _vectorFP, const vec4f& _vector2);
	friend vec4f operator^(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Cross Product Additions
	static vec4f Cross(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Cross(const __m128& _sse1, const __m128& _sse2);
	static vec4f Cross(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Cross(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Normalize
	void Normalize();
	static vec4f Normalize(const vec4f& _vector);
	static vec4f Normalize(const float* _vectorFP);
	static vec4f Normalize(const __m128& _vectorSSE);

	//Vector Homogenize (Perspective Divide)
	void Homogenize();
	static vec4f Homogenize(const vec4f& _vector);
	static vec4f Homogenize(const float* _vectorFP);
	static vec4f Homogenize(const __m128& _vectorSSE);

	//Vector Angle Between
	float AngleBetween(const vec4f& _vector) const;
	float AngleBetween(const float* _vectorFP) const;
	float AngleBetween(const __m128& _vectorSSE) const;
	static float AngleBetween(const vec4f& _vector1, const vec4f& _vector2);
	static float AngleBetween(const vec4f& _vector1, const float* _vectorFP);
	static float AngleBetween(const vec4f& _vector1, const __m128& _vectorSSE);
	static float AngleBetween(const float* _vectorFP, const vec4f& _vector2);
	static float AngleBetween(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Angle Between Additions
	static float AngleBetween(const float* _vectorFP1, const float* _vectorFP2);
	static float AngleBetween(const __m128& _sse1, const __m128& _sse2);
	static float AngleBetween(const float* _vectorFP, const __m128& _vectorSSE);
	static float AngleBetween(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Component
	float Component(const vec4f& _vector) const;
	float Component(const float* _vectorFP) const;
	float Component(const __m128& _vectorSSE) const;
	static float Component(const vec4f& _vector1, const vec4f& _vector2);
	static float Component(const vec4f& _vector1, const float* _vectorFP);
	static float Component(const vec4f& _vector1, const __m128& _vectorSSE);
	static float Component(const float* _vectorFP, const vec4f& _vector2);
	static float Component(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Component Additions
	static float Component(const float* _vectorFP1, const float* _vectorFP2);
	static float Component(const __m128& _sse1, const __m128& _sse2);
	static float Component(const float* _vectorFP, const __m128& _vectorSSE);
	static float Component(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Project
	void Project(const vec4f& _vector);
	void Project(const float* _vectorFP);
	void Project(const __m128& _vectorSSE);
	static vec4f Project(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Project(const vec4f& _vector1, const float* _vectorFP);
	static vec4f Project(const vec4f& _vector1, const __m128& _vectorSSE);
	static vec4f Project(const float* _vectorFP, const vec4f& _vector2);
	static vec4f Project(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Project Additions
	static vec4f Project(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Project(const __m128& _sse1, const __m128& _sse2);
	static vec4f Project(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Project(const __m128& _vectorSSE, const float* _vectorFP);

	//Vector Reflect
	void Reflect(const vec4f& _vector);
	void Reflect(const float* _vectorFP);
	void Reflect(const __m128& _vectorSSE);
	static vec4f Reflect(const vec4f& _vector1, const vec4f& _vector2);
	static vec4f Reflect(const vec4f& _vector1, const float* _vectorFP);
	static vec4f Reflect(const vec4f& _vector1, const __m128& _vectorSSE);
	static vec4f Reflect(const float* _vectorFP, const vec4f& _vector2);
	static vec4f Reflect(const __m128& _vectorSSE, const vec4f& _vector2);

	//Vector Reflect Additions
	static vec4f Reflect(const float* _vectorFP1, const float* _vectorFP2);
	static vec4f Reflect(const __m128& _sse1, const __m128& _sse2);
	static vec4f Reflect(const float* _vectorFP, const __m128& _vectorSSE);
	static vec4f Reflect(const __m128& _vectorSSE, const float* _vectorFP);

	//Addition: Epsilon Change
	static void ChangeEpsilon(const float& _epsilon = -1.0f);
	static float GetEpsilon();
};
#endif //VEC4F_H

#ifdef VEC4_FLOATS_GLOBAL
typedef vec4f vec4;
#endif