#include "Vector3.h"
#include <cmath>
using namespace Math;

Vector3::Vector3() : Vector3(0, 0, 0)
{}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{}

float Vector3::length() const
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

Vector3& Vector3::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

float Vector3::dot(const Vector3& v)const
{
	return (x * v.x) + (y * v.y) + (z * v.z);
}

Vector3 Vector3::cross(const Vector3& v)const
{
	Vector3 temp(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	return temp;
}


Vector3 Vector3::operator+() const
{
	return *this;
}

Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

const Vector3 Math::operator+(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp += v2;
}

const Vector3 Math::operator-(const Vector3& v1, const Vector3& v2)
{
	Vector3 temp(v1);
	return temp -= v2;
}

const Vector3 Math::operator*(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp *= s;
}

const Vector3 Math::operator*(float s, const Vector3& v)
{
	return v * s;
}

const Vector3 Math::operator/(const Vector3& v, float s)
{
	Vector3 temp(v);
	return temp /= s;
}

const Vector3 Math::lerp(const Vector3& start, const Vector3& end, const float t)
{
	return start * (1.0f - t) + end * t;
}

const Vector3 Math::easeIn(const Vector3& start, const Vector3& end, const float t)
{
	float w = 2.0f;
	return start * (1.0f - powf(t, w)) + end * powf(t, w);
}

const Vector3 Math::easeOut(const Vector3& start, const Vector3& end, const float t)
{
	float n = t * (2.0f - t);
	return start * (1.0f - n) + end * n;
}

const Vector3 Math::easeInOut(const Vector3& start, const Vector3& end, const float t)
{
	float w = 2.0f;
	float n = powf(t, w) * ((w + 1.0f) - (w * t));
	return start * (1.0f - n) + end * n;
}