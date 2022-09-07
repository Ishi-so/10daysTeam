#pragma once

namespace Math {
	struct Vector2 {
		float x;	// x成分
		float y;	// y成分

		// コンストラクタ
		Vector2();						// 零ベクトルとする
		Vector2(float x, float y);		// x成分,y成分を指定しての生成

		// メンバ関数
		float length() const; // ノルム(長さ)を求める
		Vector2& normalize(); // 正規化する
		float dot(const Vector2& v)const;		// 内積を求める
		float cross(const Vector2& v)const;
		double distance(const Vector2& a)const;// 距離

		// 単項演算子オーバーロード
		Vector2 operator+() const;
		Vector2 operator-() const;

		// 代入演算子オーバーロード
		Vector2& operator+=(const Vector2& v);
		Vector2& operator-=(const Vector2& v);
		Vector2& operator*=(float s);
		Vector2& operator/=(float s);
	};

	const Math::Vector2 operator+(const Math::Vector2& v1, const Math::Vector2& v2);
	const Math::Vector2 operator-(const Math::Vector2& v1, const Math::Vector2& v2);
	const Math::Vector2 operator*(const Math::Vector2& v, float s);
	const Math::Vector2 operator*(float s, const Math::Vector2& v);
	const Math::Vector2 operator/(const Math::Vector2& v, float s);
}