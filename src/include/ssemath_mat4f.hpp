#ifndef SSE_MATH_LIBRARY_MAT4F
#define SSE_MATH_LIBRARY_MAT4F

namespace sml {
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
		void Set(const float& _diagonal);
		void Set(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
		void Set(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt);
		void Set(const float* _matrixFP);
		void Set(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
			const float& _e21, const float& _e22, const float& _e23, const float& _e24,
			const float& _e31, const float& _e32, const float& _e33, const float& _e34,
			const float& _e41, const float& _e42, const float& _e43, const float& _e44);

		//Absolute Value
		void Abs();

		//Equality Check
		bool IsZero() const;
		bool IsEqual(const mat4f& _matrix) const;
		bool IsEqual(const float* _matrixFP) const;

		//Addition
		void Add(const mat4f& _matrix);
		void Add(const float* _matrixFP);
		void operator+=(const mat4f& _matrix);
		void operator+=(const float* _matrixFP);
		friend mat4f operator+(const mat4f& _matrix1, const mat4f& _matrix2);
		friend mat4f operator+(const mat4f& _matrix, const float* _matrixFP);
		friend mat4f operator+(const float* _matrixFP, const mat4f& _matrix);

		//Subtraction
		void Sub(const mat4f& _matrix);
		void Sub(const float* _matrixFP);
		void operator-=(const mat4f& _matrix);
		void operator-=(const float* _matrixFP);
		friend mat4f operator-(const mat4f& _matrix1, const mat4f& _matrix2);
		friend mat4f operator-(const mat4f& _matrix, const float* _matrixFP);
		friend mat4f operator-(const float* _matrixFP, const mat4f& _matrix);

		//Matrix Scalar Division
		void Div(const float& _scalar);
		void operator/=(const float& _scalar);
		friend mat4f operator/(const mat4f& _matrix, const float& _scalar);

		//Matrix Scalar Multiplication
		void MulS(const float& _scalar);
		void operator*=(const float& _scalar);
		friend mat4f operator*(const mat4f& _matrix, const float& _scalar);
		friend mat4f operator*(const float& _scalar, const mat4f& _matrix);

		//Matrix-Matrix Multiplication
		void MulM(const mat4f& _matrix);
		void MulM(const float* _matrixFP);
		void operator*=(const mat4f& _matrix);
		void operator*=(const float* _matrixFP);
		friend mat4f operator*(const mat4f& _matrix1, const mat4f& _matrix2);

		//Matrix-Vector Multiplication
		__m128 MulMV(const __m128& _vectorSSE);
		__m128 MulMV(const float* _vectorFP);

		//Vector-Matrix Multiplication
		__m128 MulVM(const __m128& _vectorSSE);
		__m128 MulVM(const float* _vectorFP);

		// Negate
		void Negate();
		mat4f operator-();

		//Translation
		void Translate(const float& _x, const float& _y, const float& _z, const float& _w);
		void Translate(const __m128& _vectorSSE);
		void Translate(const float* _vectorFP);

		//Scaling
		void Scale(const float& diagonal);
		void Scale(const float& _x, const float& _y, const float& _z);
		void Scale(const __m128& _vectorSSE);
		void Scale(const float* _vectorFP);

		//Rotation
		void Rotate(const float& _radians, const float& _x, const float& _y, const float& _z);
		void Rotate(const float& _radians, const __m128& _vectorSSE);
		void Rotate(const float& _radians, const float* _vectorFP);

		//Axis Rotation
		void RotateX(const float& _radians);
		void RotateY(const float& _radians);
		void RotateZ(const float& _radians);

		//Transpose
		void Transpose();
		mat4f operator~();

		//Determinant
		float Determinant3D() const;
		float Determinant() const;

		//Invserse
		void Inverse();
		void InverseFast();
	};

	//Matrix Absolute Value
	static mat4f MatrixAbs(const mat4f& _matrix);
	static mat4f MatrixAbs(const float* _matrixFP);

	//Set
	static mat4f MatrixSet(const float& _diagonal);
	static mat4f MatrixSet(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
	static mat4f MatrixSet(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt);
	static mat4f MatrixSet(const float* _matrixFP);
	static mat4f MatrixSet(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
		const float& _e21, const float& _e22, const float& _e23, const float& _e24,
		const float& _e31, const float& _e32, const float& _e33, const float& _e34,
		const float& _e41, const float& _e42, const float& _e43, const float& _e44);

	//Get Common Matrices
	static mat4f MatrixIdentity() { return mat4f(1.0f); }
	static mat4f MatrixZero() { return mat4f(0.0f); }

	//Matrix-Matrix Addition
	static mat4f MatrixAdd(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f MatrixAdd(const mat4f& _matrix, const float* _matrixFP);
	static mat4f MatrixAdd(const float* _matrixFP, const mat4f& _matrix);
	static mat4f MatrixAdd(const float* _matrixFP1, const float* _matrixFP2);

	//Matrix-Matrix Subtraction
	static mat4f MatrixSub(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f MatrixSub(const mat4f& _matrix, const float* _matrixFP);
	static mat4f MatrixSub(const float* _matrixFP, const mat4f& _matrix);
	static mat4f MatrixSub(const float* _matrixFP1, const float* _matrixFP2);

	//Matrix-Scalar Multiply
	static mat4f MatrixMulS(const mat4f& _matrix, const float& _scalar);
	static mat4f MatrixMulS(const float& _scalar, const mat4f& _matrix);
	static mat4f MatrixMulS(const float* _matrix, const float& _scalar);
	static mat4f MatrixMulS(const float& _scalar, const float* _matrix);

	//Matrix-Scalar Divide
	static mat4f MatrixDiv(const mat4f& _matrix, const float& _scalar);
	static mat4f MatrixDiv(const float* _matrix, const float& _scalar);

	//Matrix-Matrix Multiply
	static mat4f MatrixMulM(const mat4f& _matrix1, const mat4f& _matrix2);
	static mat4f MatrixMulM(const mat4f& _matrix, const float* _matrixFP);
	static mat4f MatrixMulM(const float* _matrixFP, const mat4f& _matrix);
	static mat4f MatrixMulM(const float* _matrixFP1, const float* _matrixFP2);

	//Matrix-Vector Multiply
	static __m128 MatrixMulV(const mat4f& _matrix, const __m128& _vectorSSE);
	static __m128 MatrixMulV(const mat4f& _matrix, const float* _vectorFP);
	static __m128 MatrixMulV(const float* _matrixFP, const __m128& _vectorSSE);
	static __m128 MatrixMulV(const float* _matrixFP, const float* _vectorFP);

	//Vector-Matrix Multiply
	static __m128 VectorMulM(const __m128& _vectorSSE, const mat4f& _matrix);
	static __m128 VectorMulM(const __m128& _vectorSSE, const float* _matrixFP);
	static __m128 VectorMulM(const float* _vectorFP, const mat4f& _matrix);
	static __m128 VectorMulM(const float* _vectorFP, const float* _matrixFP);

	//Matrix Negate
	static mat4f MatrixNegate(const mat4f& _matrix);
	static mat4f MatrixNegate(const float* _matrixFP);

	//Translation Matrix
	static mat4f TranslationMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f TranslationMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z);
	static mat4f TranslationMatrix(const mat4f& _matrix, const __m128& _vectorSSE);
	static mat4f TranslationMatrix(const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f TranslationMatrix(const mat4f& _matrix, const float* _vectorFP);
	static mat4f TranslationMatrix(const float* _matrixFP, const __m128& _sse);
	static mat4f TranslationMatrix(const float* _matrixFP, const float* _vectorFP);

	//Scaling Matrix
	static mat4f ScalingMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f ScalingMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z);
	static mat4f ScalingMatrix(const mat4f& _matrix, const __m128& _vectorSSE);
	static mat4f ScalingMatrix(const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f ScalingMatrix(const mat4f& _matrix, const float* _vectorFP);
	static mat4f ScalingMatrix(const float* _matrixFP, const __m128& _sse);
	static mat4f ScalingMatrix(const float* _matrixFP, const float* _vectorFP);

	//Rotation Matrix
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float& _x, const float& _y, const float& _z);
	static mat4f RotationMatrix(const float& _radians, const float& _x, const float& _y, const float& _z, const mat4f& _matrix);
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const __m128& _vectorSSE);
	static mat4f RotationMatrix(const float& _radians, const __m128& _vectorSSE, const mat4f& _matrix);
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float* _vectorFP);
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians, const __m128& _sse);
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians, const float* _vectorFP);

	//X Rotation Matrix
	static mat4f XRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f XRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f XRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f XRotationMatrix(const float& _radians, const float* _matrixFP);

	//Y Rotation Matrix
	static mat4f YRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f YRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f YRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f YRotationMatrix(const float& _radians, const float* _matrixFP);

	//Z Rotation Matrix
	static mat4f ZRotationMatrix(const mat4f& _matrix, const float& _radians);
	static mat4f ZRotationMatrix(const float& _radians, const mat4f& _matrix);
	static mat4f ZRotationMatrix(const float* _matrixFP, const float& _radians);
	static mat4f ZRotationMatrix(const float& _radians, const float* _matrixFP);

	//Transpose Matrix
	static mat4f Transpose(const mat4f& _matrix);
	static mat4f Transpose(const float* _matrixFP);

	//Matrix Determinants
	static float Determinant3D(const mat4f& _matrix);
	static float Determinant3D(const float* _matrixFP);
	static float Determinant(const mat4f& _matrix);
	static float Determinant(const float* _matrixFP);

	//Inverse
	static mat4f Inverse(const mat4f& _matrix);
	static mat4f Inverse(const float* _matrixFP);
	static mat4f InverseFast(const mat4f& _matrix);
	static mat4f InverseFast(const float* _matrixFP);
}

#ifdef MAT4_FLOATS_GLOBAL
typedef mat4f mat4;
#endif

#endif