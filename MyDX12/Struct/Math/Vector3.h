#pragma once

namespace Math {
	struct Vector3
	{
		float x, y, z;

		// コンストラクタ
		Vector3();						// 零ベクトルとする
		Vector3(float x, float y, float z);		// x成分,y成分を指定しての生成

		// メンバ関数
		float length() const; // ノルム(長さ)を求める
		Vector3& normalize(); // 正規化する
		float dot(const Vector3& v)const;		// 内積を求める
		Vector3 cross(const Vector3& v)const;	// 外積を求める

		// 単項演算子オーバーロード
		Vector3 operator+() const;
		Vector3 operator-() const;

		// 代入演算子オーバーロード
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
	};

	const Vector3 operator+(const Vector3& v1, const Vector3& v2);
	const Vector3 operator-(const Vector3& v1, const Vector3& v2);
	const Vector3 operator*(const Vector3& v, float s);
	const Vector3 operator*(float s, const Math::Vector3& v);
	const Vector3 operator/(const Vector3& v, float s);
	const Vector3 lerp(const Vector3& start, const Vector3& end, const float t);
	const Vector3 easeIn(const Vector3& start, const Vector3& end, const float t);
	const Vector3 easeOut(const Vector3& start, const Vector3& end, const float t);
	const Vector3 easeInOut(const Vector3& start, const Vector3& end, const float t);
}