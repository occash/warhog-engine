#ifndef MATRIX_H
#define MATRIX_H

#include "config.h"

class Matrix4
{
public:
	inline Matrix4();
	inline Matrix4(float f);
	inline Matrix4(const Matrix4& other);

	inline Vector4 &operator[](unsigned int index);
	inline const Vector4 &operator[](unsigned int index) const;

	inline Matrix4 operator+(const Matrix4& other) const;
	inline Matrix4 operator-(const Matrix4& other) const;
	inline Matrix4 operator*(const Matrix4& other) const;
	inline Matrix4 operator/(const Matrix4& other) const;

	inline Matrix4 inverse() const;
	inline Matrix4 transpose() const;

	union {
		ALIGNED(struct, 32) {
			Vector4 row[4];
		};
		ALIGNED(float data[16], 32);
	};

#if defined(USE_SSE)
private:
	inline Matrix4(__m256 d01, __m256 d23);
#endif
};

#if defined(USE_SSE)
//Default is identity matrix
Matrix4::Matrix4()
{
	_mm256_store_ps(data, _mm256_set_ps(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f));
	_mm256_store_ps(data + 8, _mm256_set_ps(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f));
}

Matrix4::Matrix4(float f)
{
	_mm256_store_ps(data, _mm256_set1_ps(f));
	_mm256_store_ps(data + 8, _mm256_set1_ps(f));
}

Matrix4::Matrix4(const Matrix4& other)
{
	_mm256_store_ps(data, _mm256_load_ps(other.data));
	_mm256_store_ps(data + 8, _mm256_load_ps(other.data + 8));
}

Matrix4::Matrix4(__m256 d01, __m256 d23)
{
	_mm256_store_ps(data, d01);
	_mm256_store_ps(data + 8, d23);
}

Vector4 & Matrix4::operator[](unsigned int index)
{
	return row[index];
}

const Vector4 & Matrix4::operator[](unsigned int index) const
{
	return row[index];
}
/*
Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	return{ _mm256_add_ps(m01, other.m01), _mm256_add_ps(m23, other.m23) };
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	return{ _mm256_sub_ps(m01, other.m01), _mm256_sub_ps(m23, other.m23) };
}
*/
Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	__m256 m01 = _mm256_load_ps(data);
	__m256 result1 = _mm256_mul_ps(_mm256_shuffle_ps(m01, m01, 0x00), _mm256_broadcast_ps(&other.row[0].data));
	result1 = _mm256_add_ps(result1, _mm256_mul_ps(_mm256_shuffle_ps(m01, m01, 0x55), _mm256_broadcast_ps(&other.row[1].data)));
	result1 = _mm256_add_ps(result1, _mm256_mul_ps(_mm256_shuffle_ps(m01, m01, 0xaa), _mm256_broadcast_ps(&other.row[2].data)));
	result1 = _mm256_add_ps(result1, _mm256_mul_ps(_mm256_shuffle_ps(m01, m01, 0xff), _mm256_broadcast_ps(&other.row[3].data)));

	__m256 m23 = _mm256_load_ps(data + 8);
	__m256 result2 = _mm256_mul_ps(_mm256_shuffle_ps(m23, m23, 0x00), _mm256_broadcast_ps(&other.row[0].data));
	result2 = _mm256_add_ps(result2, _mm256_mul_ps(_mm256_shuffle_ps(m23, m23, 0x55), _mm256_broadcast_ps(&other.row[1].data)));
	result2 = _mm256_add_ps(result2, _mm256_mul_ps(_mm256_shuffle_ps(m23, m23, 0xaa), _mm256_broadcast_ps(&other.row[2].data)));
	result2 = _mm256_add_ps(result2, _mm256_mul_ps(_mm256_shuffle_ps(m23, m23, 0xff), _mm256_broadcast_ps(&other.row[3].data)));

	return{ result1, result2 };
}

#else
#endif

#endif