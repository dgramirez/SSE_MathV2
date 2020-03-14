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
		void Mabs();

		//Equality Check
		bool IsZero() const;
		bool IsEqual(const mat4f& _matrix) const;
		bool IsEqual(const float* _matrixFP) const;
		bool IsEqual(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
	};

	//Matrix Absolute Value
	static mat4f Mabs(const mat4f& _matrix);
	static mat4f Mabs(const float* _matrixFP);

	//Set
	static mat4f SetMatrix(const float& _diagonal);
	static mat4f SetMatrix(const __m128& _vectorSSEx, const __m128& _vectorSSEy, const __m128& _vectorSSEz, const __m128& _vectorSSEt);
	static mat4f SetMatrix(const float& _e11, const float& _e12, const float& _e13, const float& _e14,
		const float& _e21, const float& _e22, const float& _e23, const float& _e24,
		const float& _e31, const float& _e32, const float& _e33, const float& _e34,
		const float& _e41, const float& _e42, const float& _e43, const float& _e44);
}

#endif