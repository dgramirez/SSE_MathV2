#ifndef MAT4F_H
#define MAT4F_H

#include <xmmintrin.h>

struct mat4f {
	//Union between SSE, float Array and Vectors
	union {
		struct { __m128 m128X, m128Y, m128Z, m128T; };
		float e[16];
		struct {
			float
				e11, e12, e13, e14,
				e21, e22, e23, e24,
				e31, e32, e33, e34,
				e41, e42, e43, e44;
		};
	};

	//Constructors and Assignment
	mat4f();
	mat4f(const float& _diagonal);
	mat4f(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
	mat4f(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt);
	mat4f(const float* _matrixFP);
	mat4f(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
			const float& _e21, const float& _e22, const float& _e23, const float& _e24,
			const float& _e31, const float& _e32, const float& _e33, const float& _e34,
			const float& _e41, const float& _e42, const float& _e43, const float& _e44);
	void operator=(const mat4f& _matrix);
	void operator=(const float* _matrixFP);
	static mat4f Set(const float& _diagonal);
	static mat4f Set(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
	static mat4f Set(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt);
	static mat4f Set(const float* _matrixFP);
	static mat4f Set(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
			const float& _e21, const float& _e22, const float& _e23, const float& _e24,
			const float& _e31, const float& _e32, const float& _e33, const float& _e34,
			const float& _e41, const float& _e42, const float& _e43, const float& _e44);

	//Equality Check (Zero)
	bool IsZero() const;
	static bool IsZero(const mat4f& _matrix);
	static bool IsZero(const float* _matrixFP);

	//Equality Check
	bool IsEqual(const mat4f& _matrix) const;
	bool IsEqual(const float* _matrixFP) const;
	static bool IsEqual(const mat4f& _matrix1, const mat4f& _matrix2);
	static bool IsEqual(const mat4f& _matrix, const float* _matrixFP);
	static bool IsEqual(const float* _matrixFP, const mat4f& _matrix);
	static bool IsEqual(const float* _matrixFP1, const float* _matrixFP2);

	//Equality Check (Operator Overload)
	friend bool operator==(const mat4f& _matrix1, const mat4f& _matrix2);
	friend bool operator==(const mat4f& _matrix, const float* _matrixFP);
	friend bool operator==(const float* _matrixFP, const mat4f& _matrix);

	//Inequality Check (Operator Overload)
	friend bool operator!=(const mat4f& _matrix1, const mat4f& _matrix2);
	friend bool operator!=(const mat4f& _matrix, const float* _matrixFP);
	friend bool operator!=(const float* _matrixFP, const mat4f& _matrix);

	//Translation Matrix
	void Translate(const float& _x, const float& _y, const float& _z, const float& _w);
	void Translate(const __m128& _vectorSSE);
	void Translate(const float* _vectorFP);
	static mat4f TranslationMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f TranslationMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z);
	static mat4f TranslationMatrix(const mat4f& _matrix, const __m128& _vectorSSE);
	static mat4f TranslationMatrix(const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f TranslationMatrix(const mat4f& _matrix, const float* _vectorFP);
	static mat4f TranslationMatrix(const float* _matrixFP, const __m128& _sse);
	static mat4f TranslationMatrix(const float* _matrixFP, const float* _vectorFP);

	//Scaling Matrix
	void Scale(const float& diagonal);
	void Scale(const float& _x, const float& _y, const float& _z);
	void Scale(const __m128& _vectorSSE);
	void Scale(const float* _vectorFP);
	static mat4f ScalingMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f ScalingMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z);
	static mat4f ScalingMatrix(const mat4f& _matrix, const __m128& _vectorSSE);
	static mat4f ScalingMatrix(const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f ScalingMatrix(const mat4f& _matrix, const float* _vectorFP);
	static mat4f ScalingMatrix(const float* _matrixFP, const __m128& _sse);
	static mat4f ScalingMatrix(const float* _matrixFP, const float* _vectorFP);

	//Rotation Matrix
	void Rotate(const float& _radians, const float& _x, const float& _y, const float& _z);
	void Rotate(const float& _radians, const __m128& _vectorSSE);
	void Rotate(const float& _radians, const float* _vectorFP);
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float& _x, const float& _y, const float& _z);
	static mat4f RotationMatrix(const float& _radians, const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const __m128& _vectorSSE);
	static mat4f RotationMatrix(const float& _radians, const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float* _vectorFP);
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians,  const __m128& _sse);
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians,  const float* _vectorFP);

	//X Rotation Matrix
	void RotateX(const float& _radians);
	static mat4f XRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f XRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f XRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f XRotationMatrix(const float& _radians, const float* _matrixFP);

	//Y Rotation Matrix
	void RotateY(const float& _radians);
	static mat4f YRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f YRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f YRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f YRotationMatrix(const float& _radians, const float* _matrixFP);

	//Z Rotation Matrix
	void RotateZ(const float& _radians);
	static mat4f ZRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f ZRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f ZRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f ZRotationMatrix(const float& _radians, const float* _matrixFP);

	//Transpose Matrix
	void Transpose();
	mat4f operator~();
	static mat4f Transpose(const mat4f& _matrix);
	static mat4f Transpose(const float* _matrixFP);
	static mat4f Transpose(const __m128& _row0, const __m128& _row1, const __m128& _row2, const __m128& _row3);
	static mat4f Transpose(const float* _row0, const float* _row1, const float* _row2, const float* _row3);

	//Negate Matrix
	void Negate();
	mat4f operator-();
	static mat4f Negate(const mat4f& _matrix);
	static mat4f Negate(const float* _matrixFP);

	//Matrix Addition
	void Add(const mat4f& _matrix);
	void Add(const float* _matrixFP);
	void operator+=(const mat4f& _matrix);
	void operator+=(const float* _matrixFP);
	static mat4f Add(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f Add(const mat4f& _matrix, const float* _matrixFP);
	static mat4f Add(const float* _matrixFP, const mat4f& _matrix);
	static mat4f Add(const float* _matrixFP1, const float* _matrixFP2);
	friend mat4f operator+(const mat4f& _matrix1, const mat4f& _matrix2);
	friend mat4f operator+(const mat4f& _matrix, const float* _matrixFP);
	friend mat4f operator+(const float* _matrixFP, const mat4f& _matrix);

	//Matrix Subtration
	void Sub(const mat4f& _matrix);
	void Sub(const float* _matrixFP);
	void operator-=(const mat4f& _matrix);
	void operator-=(const float* _matrixFP);
	static mat4f Sub(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f Sub(const mat4f& _matrix, const float* _matrixFP);
	static mat4f Sub(const float* _matrixFP, const mat4f& _matrix);
	static mat4f Sub(const float* _matrixFP1, const float* _matrixFP2);
	friend mat4f operator-(const mat4f& _matrix1, const mat4f& _matrix2);
	friend mat4f operator-(const mat4f& _matrix, const float* _matrixFP);
	friend mat4f operator-(const float* _matrixFP, const mat4f& _matrix);

	//Matrix Scalar Division
	void Div(const float& _scalar);
	void operator/=(const float& _scalar);
	static mat4f Div(const mat4f& _matrix, const float& _scalar);
	static mat4f Div(const float* _matrixFP, const float& _scalar);
	friend mat4f operator/(const mat4f& _matrix, const float& _scalar);

	//Matrix Scalar Multiplication
	void Mul(const float& _scalar);
	void operator*=(const float& _scalar);
	static mat4f Mul(const mat4f& _matrix, const float& _scalar);
	static mat4f Mul(const float& _scalar, const mat4f& _matrix);
	static mat4f Mul(const float* _matrixFP, const float& _scalar);
	static mat4f Mul(const float& _scalar, const float* _matrixFP);
	friend mat4f operator*(const mat4f& _matrix, const float& _scalar);
	friend mat4f operator*(const float& _scalar, const mat4f& _matrix);

	//Matrix-Matrix Multiplication
	void Mul(const mat4f& _matrix);
	void Mul(const float* _matrixFP);
	void operator*=(const mat4f& _matrix);
	void operator*=(const float* _matrixFP);
	static mat4f Mul(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f Mul(const float* _matrixFP1, const float* _matrixFP2);
	friend mat4f operator*(const mat4f& _matrix1, const mat4f& _matrix2);

	//Matrix-Vector Multiplication
	void Mul(const __m128& _vectorSSE);
	void operator*=(const __m128& _vectorSSE);
	static __m128 Mul(const mat4f& _matrix, const __m128& _vectorSSE);
	static __m128 Mul(const float* _matrix, const __m128& _vectorSSE);

	//Vector-Matrix Multiplication
	static __m128 Mul(const __m128& _vectorSSE, const mat4f& _matrix);
	static __m128 Mul(const __m128& _vectorSSE, const float* _matrix);

	//Matrix Determinant 3D
	float Determinant3D() const;
	static float Determinant3D(const mat4f& _matrix);
	static float Determinant3D(const float* _matrixFP);

	float Determinant() const;
	static float Determinant(const mat4f& _matrix);
	static float Determinant(const float* _matrixFP);

	//Inverse (Normal)
	void Inverse();
	static mat4f Inverse(const mat4f& _matrix);
	static mat4f Inverse(const float* _matrixFP);

	//Inverse (Fast)
	void InverseFast();
	static mat4f InverseFast(const mat4f& _matrix);
	static mat4f InverseFast(const float* _matrixFP);

	//Addition: Epsilon Change
	static void ChangeEpsilon(const float& _epsilon = -1.0f);
	static float GetEpsilon();
};

#endif //MAT4F_H

#ifdef MAT4_FLOATS_GLOBAL
typedef mat4f mat4;
#endif