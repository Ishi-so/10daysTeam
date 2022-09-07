#pragma once

namespace Math {

	struct Vector4
	{
		float x, y, z, w;
		// コンストラクタ
		Vector4();						// 零ベクトルとする
		Vector4(float x, float y, float z, float w = 0.0f);		// x成分,y成分を指定しての生成
	};

	Vector4 AddVec4(const Vector4& v0, const Vector4& v1);

	Vector4 SubVec4(const Vector4& v0, const Vector4& v1);

	Vector4 MulVec4(const Vector4& v, float s);

	float VecLength4Square(const Vector4& v);

	float VecLength4(const Vector4& v);

	Vector4 VecNormalize4(const Vector4& v);

	float DotVec4(const Vector4& v0, const Vector4& v1);

	Vector4 CrossVec4(const Vector4& v0, const Vector4& v1);

	Vector4 CrossVec4(const Vector4& p0, const Vector4& p1, const Vector4& p2);

	Vector4 VectorLerp(const Vector4& v0, const Vector4& v1, float t);
}