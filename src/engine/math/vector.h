#ifndef VECTOR_H
#define VECTOR_H

#include "config.h"

#if defined(USE_SSE)
#include <smmintrin.h>
#else
#include <cmath>
#endif

class Vector4;

class Vector3
{
public:
	inline Vector3();
	inline Vector3(float v);
	inline Vector3(float x, float y, float z);
	inline Vector3(const Vector3& other);
	inline Vector3(const Vector4& other);

	inline Vector3 operator+(const Vector3& v) const;
	inline Vector3 operator-(const Vector3& v) const;
	inline Vector3 operator*(const Vector3& v) const;
	inline Vector3 operator/(const Vector3& v) const;

	inline float dot(const Vector3& other) const;
	inline Vector3 cross(const Vector3& other) const;

	inline float length() const;
	inline Vector3 normalize() const;

	union {
		ALIGNED(struct, 16) {
			float x, y, z;
		};
		ALIGNED(struct, 16) {
			float r, g, b;
		};
#if defined(USE_SSE)
		__m128 data;
#else
		ALIGNED(float data[3], 16);
#endif
	};

#if defined(USE_SSE)
	//Proper aligned new and delete
	void *operator new (size_t size) 
	{ 
		return _mm_malloc(size, 16); 
	}

	void operator delete (void *p)
	{
		_mm_free(p);
	}

private:
	inline Vector3(__m128 m);
#endif
};

class Vector4
{
public:
	inline Vector4();
	inline Vector4(float v);
	inline Vector4(float x, float y, float z, float w);
	inline Vector4(const Vector4& other);

	inline Vector4 operator+(const Vector4& v) const;
	inline Vector4 operator-(const Vector4& v) const;
	inline Vector4 operator*(const Vector4& v) const;
	inline Vector4 operator/(const Vector4& v) const;

	inline float dot(const Vector4& other) const;
	inline Vector4 cross(const Vector4& other) const;

	inline float length() const;
	inline Vector4 normalize() const;

	union {
		ALIGNED(struct, 16) {
			float x, y, z, w;
		};
		ALIGNED(struct, 16) {
			float r, g, b, a;
		};
#if defined(USE_SSE)
		__m128 data;
#else
		ALIGNED(float data[4], 16);
#endif
	};

#if defined(USE_SSE)
	//Proper aligned new and delete
	void *operator new (size_t size)
	{
		return _mm_malloc(size, 16);
	}

		void operator delete (void *p)
	{
		_mm_free(p);
	}

private:
	inline Vector4(__m128 m);
#endif
};

#if defined(USE_SSE) //SSE vector
Vector3::Vector3() :
	data(_mm_setzero_ps())
{}

Vector3::Vector3(float v) :
	data(_mm_set_ps(0, v, v, v))
{}

Vector3::Vector3(float x, float y, float z) :
	data(_mm_set_ps(0, z, y, x))
{}

Vector3::Vector3(const Vector3& v) :
	data(v.data)
{}

Vector3::Vector3(const Vector4& v) :
	data(v.data)
{}

Vector3::Vector3(__m128 m) :
	data(m)
{}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return _mm_add_ps(data, v.data);
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return _mm_sub_ps(data, v.data);
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return _mm_mul_ps(data, v.data);
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	return _mm_div_ps(data, v.data);
}

float Vector3::dot(const Vector3& v) const
{
	return _mm_cvtss_f32(_mm_dp_ps(data, v.data, 0x71));
}

Vector3 Vector3::cross(const Vector3& v) const
{
	return _mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 0, 2, 1)), 
			_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 1, 0, 2))
		),
		_mm_mul_ps(
			_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 1, 0, 2)), 
			_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 0, 2, 1))
		)
	);
}

float Vector3::length() const
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(data, data, 0x71)));
}

Vector3 Vector3::normalize() const
{
	return _mm_mul_ps(data, _mm_rsqrt_ps(_mm_dp_ps(data, data, 0x7F)));
}

Vector4::Vector4() :
	data(_mm_setzero_ps())
{}

Vector4::Vector4(float v) :
	data(_mm_set_ps1(v))
{}

Vector4::Vector4(float x, float y, float z, float w) :
	data(_mm_set_ps(0, x, y, z))
{}

Vector4::Vector4(const Vector4& v) :
	data(v.data)
{}

Vector4::Vector4(__m128 m) :
	data(m)
{}

Vector4 Vector4::operator+(const Vector4& v) const
{
	return _mm_add_ps(data, v.data);
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	return _mm_sub_ps(data, v.data);
}

Vector4 Vector4::operator*(const Vector4& v) const
{
	return _mm_mul_ps(data, v.data);
}

Vector4 Vector4::operator/(const Vector4& v) const
{
	return _mm_div_ps(data, v.data);
}

float Vector4::dot(const Vector4& v) const
{
	return _mm_cvtss_f32(_mm_dp_ps(data, v.data, 0xF1));
}

Vector4 Vector4::cross(const Vector4& v) const
{
	//The same as for Vector3
	return _mm_sub_ps(
		_mm_mul_ps(
			_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 0, 2, 1)),
			_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 1, 0, 2))
		),
		_mm_mul_ps(
			_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 1, 0, 2)), 
			_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 0, 2, 1))
		)
	);
}

float Vector4::length() const
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(data, data, 0xF1)));
}

Vector4 Vector4::normalize() const
{
	return _mm_mul_ps(data, _mm_rsqrt_ps(_mm_dp_ps(data, data, 0xFF)));
}
#else //Scalar vector
Vector3::Vector3() :
	data{0, 0, 0}
{}

Vector3::Vector3() :
	data{v, v, v}
{}

Vector3::Vector3(float x, float y, float z) :
	data{ x, y, z }
{}

Vector3::Vector3(const Vector3& v) :
	data{ v.x, v.y, v.z }
{}

Vector3::Vector3(const Vector4& v) :
	data{ v.x, v.y, v.z }
{}

Vector3 Vector3::operator+(const Vector3& v) const
{
	return {x + v.x, y + v.y, z + v.z};
}

Vector3 Vector3::operator-(const Vector3& v) const
{
	return {x - v.x, y - v.y, z - v.z};
}

Vector3 Vector3::operator*(const Vector3& v) const
{
	return {x * v.x, y * v.y, z * v.z};
}

Vector3 Vector3::operator/(const Vector3& v) const
{
	return {x / v.x, y / v.y, z / v.z};
}
float Vector3::dot(const Vector3& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3& v)
{
	return {
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	};
}

float Vector3::length()
{
	return std::sqrt(x * x, y * y, z * z);
}

void Vector3::normalize()
{
	float l = length();
	return {x / l, y / l, z / l};
}

Vector4 Vector4::operator+(const Vector4& v) const
{
	return {x + v.x, y + v.y, z + v.z, w + v.w};
}

Vector4 Vector4::operator-(const Vector4& v) const
{
	return {x - v.x, y - v.y, z - v.z, w - v.w};
}

Vector4 Vector4::operator*(const Vector4& v) const
{
	return {x * v.x, y * v.y, z * v.z, w * v.w};
}

Vector4 Vector4::operator/(const Vector4& v) const
{
	return {x / v.x, y / v.y, z / v.z, w / v.w};
}

float Vector4::dot(const Vector4& v)
{
	return _mm_cvtss_f32(_mm_dp_ps(data, v.data, 0xF1));
}

Vector4 Vector4::cross(const Vector4& v)
{
	//The same as for Vector3
	return _mm_sub_ps(
		_mm_mul_ps(
		_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 0, 2, 1)),
		_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 1, 0, 2))
		),
		_mm_mul_ps(
		_mm_shuffle_ps(data, data, _MM_SHUFFLE(3, 1, 0, 2)),
		_mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 0, 2, 1))
		)
		);
}

float Vector4::length()
{
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(data, data, 0xF1)));
}

void Vector4::normalize()
{
	data = _mm_mul_ps(data, _mm_rsqrt_ps(_mm_dp_ps(data, data, 0xFF)));
}
#endif

#endif