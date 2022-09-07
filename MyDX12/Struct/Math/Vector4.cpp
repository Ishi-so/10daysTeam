#include "Vector4.h"
#include <cmath>

Math::Vector4::Vector4() : Vector4(0, 0, 0, 0)
{}

Math::Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{}

Math::Vector4 Math::AddVec4(const Vector4& v0, const Vector4& v1)
{
	Math::Vector4 r;
	r.x = v0.x + v1.x;
	r.y = v0.y + v1.y;
	r.z = v0.z + v1.z;
	r.w = v0.w + v1.w;
	return r;
}

Math::Vector4 Math::SubVec4(const Vector4& v0, const Vector4& v1)
{
	Math::Vector4 r;
	r.x = v0.x - v1.x;
	r.y = v0.y - v1.y;
	r.z = v0.z - v1.z;
	r.w = v0.w - v1.w;
	return r;
}

Math::Vector4 Math::MulVec4(const Vector4& v, float s)
{
	Vector4 r;
	r.x = v.x * s;
	r.y = v.y * s;
	r.z = v.z * s;
	r.w = v.w;
	return r;
}

float Math::VecLength4Square(const Vector4& v)
{
	float ls = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	return ls;
}

float Math::VecLength4(const Vector4& v)
{
	float l = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return l;
}

Math::Vector4 Math::VecNormalize4(const Vector4& v)
{
	float l = VecLength4(v);
	Vector4 n;
	n.x = v.x / l;
	n.y = v.y / l;
	n.z = v.z / l;
	n.w = v.w / l;
	return n;
}

float Math::DotVec4(const Vector4& v0, const Vector4& v1)
{
	float r;
	r = (v0.x * v1.x) + (v0.y * v1.y) + (v0.z * v1.z) + (v0.w * v1.w);
	return r;
}

Math::Vector4 Math::CrossVec4(const Vector4& v0, const Vector4& v1)
{
	Vector4 r;
	r.x = v0.y * v1.z - v0.z * v1.y;
	r.y = v0.z * v1.x - v0.x * v1.z;
	r.z = v0.x * v1.y - v0.y * v1.x;
	r.w = 0.0f;
	return r;
}

Math::Vector4 Math::CrossVec4(const Vector4& p0, const Vector4& p1, const Vector4& p2)
{
	// ベクトルの作成
	Vector4 v0 = SubVec4(p1, p0);
	Vector4 v1 = SubVec4(p2, p1);
	// ベクトルから外積を算出
	return (CrossVec4(v0, v1));
}

Math::Vector4 Math::VectorLerp(const Vector4& v0, const Vector4& v1, float t)
{
	Vector4 result;
	result.x = v0.x + t * (v1.x - v0.x);
	result.y = v0.y + t * (v1.y - v0.y);
	result.z = v0.z + t * (v1.z - v0.z);
	result.w = v0.w + t * (v1.w - v0.w);
	return result;
}