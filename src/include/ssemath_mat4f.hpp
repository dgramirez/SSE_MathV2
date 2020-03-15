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
		mat4f() {
			m128X = m128Y = m128Z = m128T = _mm_setzero_ps();
		}
		mat4f(const float& _diagonal) {
			m128X = _mm_set_ps(0.0f, 0.0f, 0.0f, _diagonal);
			m128Y = _mm_set_ps(0.0f, 0.0f, _diagonal, 0.0f);
			m128Z = _mm_set_ps(0.0f, _diagonal, 0.0f, 0.0f);
			m128T = _mm_set_ps(_diagonal, 0.0f, 0.0f, 0.0f);
		}
		mat4f(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt) {
			m128X = _vectorSSEx;
			m128Y = _vectorSSEy;
			m128Z = _vectorSSEz;
			m128T = _vectorSSEt;
		}
		mat4f(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt) {
			m128X = _mm_load_ps(_vectorFPx);
			m128Y = _mm_load_ps(_vectorFPy);
			m128Z = _mm_load_ps(_vectorFPz);
			m128T = _mm_load_ps(_vectorFPt);
		}
		mat4f(const float* _matrixFP) {
			m128X = _mm_load_ps(_matrixFP);
			m128Y = _mm_load_ps(&_matrixFP[4]);
			m128Z = _mm_load_ps(&_matrixFP[8]);
			m128T = _mm_load_ps(&_matrixFP[12]);
		}
		mat4f(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
			const float& _e21, const float& _e22, const float& _e23, const float& _e24,
			const float& _e31, const float& _e32, const float& _e33, const float& _e34,
			const float& _e41, const float& _e42, const float& _e43, const float& _e44) {
			m128X = _mm_set_ps(_e14, _e13, _e12, _e11);
			m128Y = _mm_set_ps(_e24, _e23, _e22, _e21);
			m128Z = _mm_set_ps(_e34, _e33, _e32, _e31);
			m128T = _mm_set_ps(_e44, _e43, _e42, _e41);
		}
		void operator=(const mat4f& _matrix) {
			m128X = _matrix.m128X;
			m128Y = _matrix.m128Y;
			m128Z = _matrix.m128Z;
			m128T = _matrix.m128T;
		}
		void operator=(const float* _matrixFP) {
			m128X = _mm_load_ps(_matrixFP);
			m128Y = _mm_load_ps(&_matrixFP[4]);
			m128Z = _mm_load_ps(&_matrixFP[8]);
			m128T = _mm_load_ps(&_matrixFP[12]);
		}
		void Set(const float& _diagonal) {
			m128X = _mm_set_ps(0.0f, 0.0f, 0.0f, _diagonal);
			m128Y = _mm_set_ps(0.0f, 0.0f, _diagonal, 0.0f);
			m128Z = _mm_set_ps(0.0f, _diagonal, 0.0f, 0.0f);
			m128T = _mm_set_ps(_diagonal, 0.0f, 0.0f, 0.0f);
		}
		void Set(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt) {
			m128X = _vectorSSEx;
			m128Y = _vectorSSEy;
			m128Z = _vectorSSEz;
			m128T = _vectorSSEt;
		}
		void Set(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt) {
			m128X = _mm_load_ps(_vectorFPx);
			m128Y = _mm_load_ps(_vectorFPy);
			m128Z = _mm_load_ps(_vectorFPz);
			m128T = _mm_load_ps(_vectorFPt);
		}
		void Set(const float* _matrixFP) {
			m128X = _mm_load_ps(_matrixFP);
			m128Y = _mm_load_ps(&_matrixFP[4]);
			m128Z = _mm_load_ps(&_matrixFP[8]);
			m128T = _mm_load_ps(&_matrixFP[12]);
		}
		void Set(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
			const float& _e21, const float& _e22, const float& _e23, const float& _e24,
			const float& _e31, const float& _e32, const float& _e33, const float& _e34,
			const float& _e41, const float& _e42, const float& _e43, const float& _e44) {
			m128X = _mm_set_ps(_e14, _e13, _e12, _e11);
			m128Y = _mm_set_ps(_e24, _e23, _e22, _e21);
			m128Z = _mm_set_ps(_e34, _e33, _e32, _e31);
			m128T = _mm_set_ps(_e44, _e43, _e42, _e41);
		}

		//Absolute Value
		void Abs() {
			m128X = sml::VectorAbs(m128X);
			m128Y = sml::VectorAbs(m128Y);
			m128Z = sml::VectorAbs(m128Z);
			m128T = sml::VectorAbs(m128T);
		}

		//Equality Check
		bool IsZero() const {
			return sml::VectorIsZero(m128X) & sml::VectorIsZero(m128Y) & sml::VectorIsZero(m128Z) & sml::VectorIsZero(m128T);
		}
		bool IsEqual(const mat4f& _matrix) const {
			return sml::VectorIsEqual(m128X, _matrix.m128X) & sml::VectorIsEqual(m128Y, _matrix.m128Y) & sml::VectorIsEqual(m128Z, _matrix.m128Z) & sml::VectorIsEqual(m128T, _matrix.m128T);
		}
		bool IsEqual(const float* _matrixFP) const {
			return sml::VectorIsEqual(m128X, _mm_load_ps(_matrixFP)) & sml::VectorIsEqual(m128Y, _mm_load_ps(&_matrixFP[4])) & sml::VectorIsEqual(m128Z, _mm_load_ps(&_matrixFP[8])) & sml::VectorIsEqual(m128T, _mm_load_ps(&_matrixFP[12]));
		}

		//Addition
		void Add(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Add(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator+=(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator+=(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		friend mat4f operator+(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}
		friend mat4f operator+(const mat4f& _matrix, const float* _matrixFP) {
			return mat4f(1337.0f);
		}
		friend mat4f operator+(const float* _matrixFP, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}

		//Subtraction
		void Sub(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Sub(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator-=(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator-=(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		friend mat4f operator-(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}
		friend mat4f operator-(const mat4f& _matrix, const float* _matrixFP) {
			return mat4f(1337.0f);
		}
		friend mat4f operator-(const float* _matrixFP, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}

		//Matrix Scalar Division
		void Div(const float& _scalar) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator/=(const float& _scalar) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		friend mat4f operator/(const mat4f& _matrix, const float& _scalar) {
			return mat4f(1.0f);
		}

		//Matrix Scalar Multiplication
		void MulS(const float& _scalar) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator*=(const float& _scalar) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		friend mat4f operator*(const mat4f& _matrix, const float& _scalar) {
			return mat4f(1337.0f);
		}
		friend mat4f operator*(const float& _scalar, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}

		//Matrix-Matrix Multiplication
		void MulM(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void MulM(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator*=(const mat4f& _matrix) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void operator*=(const float* _matrixFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		friend mat4f operator*(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}

		//Matrix-Vector Multiplication
		__m128 MulMV(const __m128& _vectorSSE) {
			return _mm_setzero_ps();
		}
		__m128 MulMV(const float* _vectorFP) {
			return _mm_setzero_ps();
		}

		//Vector-Matrix Multiplication
		__m128 MulVM(const __m128& _vectorSSE) {
			return _mm_setzero_ps();
		}
		__m128 MulVM(const float* _vectorFP) {
			return _mm_setzero_ps();
		}

		// Negate
		void Negate() {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		mat4f operator-() {
			return (mat4f(1337.0f));
		}

		//Translation
		void Translate(const float& _x, const float& _y, const float& _z, const float& _w) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Translate(const __m128& _vectorSSE) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Translate(const float* _vectorFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}

		//Scaling
		void Scale(const float& diagonal) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Scale(const float& _x, const float& _y, const float& _z) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Scale(const __m128& _vectorSSE) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Scale(const float* _vectorFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}

		//Rotation
		void Rotate(const float& _radians, const float& _x, const float& _y, const float& _z) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Rotate(const float& _radians, const __m128& _vectorSSE) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void Rotate(const float& _radians, const float* _vectorFP) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}

		//Axis Rotation
		void RotateX(const float& _radians) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void RotateY(const float& _radians) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void RotateZ(const float& _radians) {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}

		//Transpose
		void Transpose() {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		mat4f operator~() {
			return mat4f(1337.0f);
		}

		//Determinant
		float Determinant3D() const {
			return 1337.0f;
		}
		float Determinant() const {
			return 1337.0f;
		}

		//Invserse
		void Inverse() {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
		void InverseFast() {
			m128X = m128Y = m128Z = m128T = _mm_set1_ps(1337.0f);
		}
	};

	//Matrix Absolute Value
	static mat4f MatrixAbs(const mat4f& _matrix) {
			return mat4f(
				sml::VectorAbs(_matrix.m128X),
				sml::VectorAbs(_matrix.m128Y),
				sml::VectorAbs(_matrix.m128Z),
				sml::VectorAbs(_matrix.m128T)
			);
		}
	static mat4f MatrixAbs(const float* _matrixFP) {
			return mat4f(
				sml::VectorAbs(_matrixFP),
				sml::VectorAbs(&_matrixFP[4]),
				sml::VectorAbs(&_matrixFP[8]),
				sml::VectorAbs(&_matrixFP[12])
			);
		}

	//Set
	static mat4f MatrixSet(const float& _diagonal) {
			return mat4f(_diagonal);
		}
	static mat4f MatrixSet(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt) {
			return mat4f(_vectorSSEx, _vectorSSEy, _vectorSSEz, _vectorSSEt);
		}
	static mat4f MatrixSet(const float* _vectorFPx, const float* _vectorFPy, const float* _vectorFPz, const float* _vectorFPt) {
			return mat4f(_vectorFPx, _vectorFPy, _vectorFPz, _vectorFPt);
		}
	static mat4f MatrixSet(const float* _matrixFP) {
			return mat4f(_matrixFP);
		}
	static mat4f MatrixSet(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
		const float& _e21, const float& _e22, const float& _e23, const float& _e24,
		const float& _e31, const float& _e32, const float& _e33, const float& _e34,
		const float& _e41, const float& _e42, const float& _e43, const float& _e44) {
			return mat4f(_e11, _e12, _e13, _e14,
						 _e21, _e22, _e23, _e24, 
						 _e31, _e32, _e33, _e34, 
						 _e41, _e42, _e43, _e44);
		}

	//Get Common Matrices
	static mat4f MatrixIdentity() {
			return mat4f(1337.0f);
		}
	static mat4f MatrixZero() {
			return mat4f(1337.0f);
		}

	//Matrix-Matrix Addition
	static mat4f MatrixAdd(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixAdd(const mat4f& _matrix, const float* _matrixFP) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixAdd(const float* _matrixFP, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixAdd(const float* _matrixFP1, const float* _matrixFP2) {
			return mat4f(1337.0f);
		}

	//Matrix-Matrix Subtraction
	static mat4f MatrixSub(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixSub(const mat4f& _matrix, const float* _matrixFP) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixSub(const float* _matrixFP, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixSub(const float* _matrixFP1, const float* _matrixFP2) {
			return mat4f(1337.0f);
		}

	//Matrix-Scalar Multiply
	static mat4f MatrixMulS(const mat4f& _matrix, const float& _scalar) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulS(const float& _scalar, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulS(const float* _matrix, const float& _scalar) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulS(const float& _scalar, const float* _matrix) {
			return mat4f(1337.0f);
		}

	//Matrix-Scalar Divide
	static mat4f MatrixDiv(const mat4f& _matrix, const float& _scalar) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixDiv(const float* _matrix, const float& _scalar) {
			return mat4f(1337.0f);
		}

	//Matrix-Matrix Multiply
	static mat4f MatrixMulM(const mat4f& _matrix1, const mat4f& _matrix2) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulM(const mat4f& _matrix, const float* _matrixFP) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulM(const float* _matrixFP, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixMulM(const float* _matrixFP1, const float* _matrixFP2) {
			return mat4f(1337.0f);
		}

	//Matrix-Vector Multiply
	static __m128 MatrixMulV(const mat4f& _matrix, const __m128& _vectorSSE) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 MatrixMulV(const mat4f& _matrix, const float* _vectorFP) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 MatrixMulV(const float* _matrixFP, const __m128& _vectorSSE) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 MatrixMulV(const float* _matrixFP, const float* _vectorFP) {
		return _mm_set1_ps(1337.0f);
	}

	//Vector-Matrix Multiply
	static __m128 VectorMulM(const __m128& _vectorSSE, const mat4f& _matrix) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 VectorMulM(const __m128& _vectorSSE, const float* _matrixFP) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 VectorMulM(const float* _vectorFP, const mat4f& _matrix) {
		return _mm_set1_ps(1337.0f);
	}
	static __m128 VectorMulM(const float* _vectorFP, const float* _matrixFP) {
		return _mm_set1_ps(1337.0f);
	}

	//Matrix Negate
	static mat4f MatrixNegate(const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f MatrixNegate(const float* _matrixFP) {
			return mat4f(1337.0f);
		}

	//Translation Matrix
	static mat4f TranslationMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const mat4f& _matrix, const __m128& _vectorSSE) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const __m128& _vectorSSE, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const mat4f& _matrix, const float* _vectorFP) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const float* _matrixFP, const __m128& _sse) {
			return mat4f(1337.0f);
		}
	static mat4f TranslationMatrix(const float* _matrixFP, const float* _vectorFP) {
			return mat4f(1337.0f);
		}

	//Scaling Matrix
	static mat4f ScalingMatrix(const float& _x, const float& _y, const float& _z, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const mat4f& _matrix, const float& _x, const float& _y, const float& _z) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const mat4f& _matrix, const __m128& _vectorSSE) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const __m128& _vectorSSE, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const mat4f& _matrix, const float* _vectorFP) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const float* _matrixFP, const __m128& _sse) {
			return mat4f(1337.0f);
		}
	static mat4f ScalingMatrix(const float* _matrixFP, const float* _vectorFP) {
			return mat4f(1337.0f);
		}

	//Rotation Matrix
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float& _x, const float& _y, const float& _z) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const float& _radians, const float& _x, const float& _y, const float& _z, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const __m128& _vectorSSE) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const float& _radians, const __m128& _vectorSSE, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const mat4f& _matrix, const float& _radians, const float* _vectorFP) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians, const __m128& _sse) {
			return mat4f(1337.0f);
		}
	static mat4f RotationMatrix(const float* _matrixFP, const float& _radians, const float* _vectorFP) {
			return mat4f(1337.0f);
		}

	//X Rotation Matrix
	static mat4f XRotationMatrix(const mat4f& _matrix, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f XRotationMatrix(const float& _radians, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f XRotationMatrix(const float* _matrixFP, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f XRotationMatrix(const float& _radians, const float* _matrixFP) {
			return mat4f(1337.0f);
		}

	//Y Rotation Matrix
	static mat4f YRotationMatrix(const mat4f& _matrix, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f YRotationMatrix(const float& _radians, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f YRotationMatrix(const float* _matrixFP, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f YRotationMatrix(const float& _radians, const float* _matrixFP) {
			return mat4f(1337.0f);
		}

	//Z Rotation Matrix
	static mat4f ZRotationMatrix(const mat4f& _matrix, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f ZRotationMatrix(const float& _radians, const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f ZRotationMatrix(const float* _matrixFP, const float& _radians) {
			return mat4f(1337.0f);
		}
	static mat4f ZRotationMatrix(const float& _radians, const float* _matrixFP) {
			return mat4f(1337.0f);
		}

	//Transpose Matrix
	static mat4f Transpose(const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f Transpose(const float* _matrixFP) {
			return mat4f(1337.0f);
		}

	//Matrix Determinants
	static float Determinant3D(const mat4f& _matrix) {
		return 1337.0f;
	}
	static float Determinant3D(const float* _matrixFP) {
		return 1337.0f;
	}
	static float Determinant(const mat4f& _matrix) {
		return 1337.0f;
	}
	static float Determinant(const float* _matrixFP) {
		return 1337.0f;
	}

	//Inverse
	static mat4f Inverse(const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f Inverse(const float* _matrixFP) {
			return mat4f(1337.0f);
		}
	static mat4f InverseFast(const mat4f& _matrix) {
			return mat4f(1337.0f);
		}
	static mat4f InverseFast(const float* _matrixFP) {
			return mat4f(1337.0f);
		}
}

#ifdef MAT4_FLOATS_GLOBAL
typedef mat4f mat4;
#endif

#endif