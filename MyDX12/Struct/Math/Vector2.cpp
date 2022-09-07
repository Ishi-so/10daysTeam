#include "Vector2.h"
#include <cmath>

Math::Vector2::Vector2()
	:x(0.0f), y(0.0f)
{}

Math::Vector2::Vector2(float x, float y)
	: x(x), y(y)
{}

float Math::Vector2::length() const
{
	return sqrtf(powf(x, 2) + pow(y, 2));
}

Math::Vector2& Math::Vector2::normalize()
{
	float len = length();
	if (len != 0)
	{
		return *this /= len;
	}
	return *this;
}

float Math::Vector2::dot(const Vector2& v)const
{
	return (x * v.x) + (y * v.y);
}

float Math::Vector2::cross(const Vector2& v) const
{
	return (x * v.y) - (y * v.x);
}

double Math::Vector2::distance(const Vector2& a) const
{
	return sqrt((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
}

Math::Vector2 Math::Vector2::operator+() const
{
	return *this;
}

Math::Vector2 Math::Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Math::Vector2& Math::Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;

	return *this;
}

Math::Vector2& Math::Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

Math::Vector2& Math::Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}

Math::Vector2& Math::Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

const Math::Vector2 Math::operator+(const Math::Vector2& v1, const Math::Vector2& v2)
{
	Math::Vector2 temp(v1);
	return temp += v2;
}

const Math::Vector2 Math::operator-(const Math::Vector2& v1, const Math::Vector2& v2)
{
	Math::Vector2 temp(v1);
	return temp -= v2;
}

const Math::Vector2 Math::operator*(const Math::Vector2& v, float s)
{
	Math::Vector2 temp(v);
	return temp *= s;
}

const Math::Vector2 Math::operator*(float s, const Math::Vector2& v)
{
	return v * s;
}

const Math::Vector2 Math::operator/(const Math::Vector2& v, float s)
{
	Math::Vector2 temp(v);
	return temp /= s;
}