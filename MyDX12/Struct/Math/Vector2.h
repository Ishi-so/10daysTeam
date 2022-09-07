#pragma once

namespace Math {
	struct Vector2 {
		float x;	// x����
		float y;	// y����

		// �R���X�g���N�^
		Vector2();						// ��x�N�g���Ƃ���
		Vector2(float x, float y);		// x����,y�������w�肵�Ă̐���

		// �����o�֐�
		float length() const; // �m����(����)�����߂�
		Vector2& normalize(); // ���K������
		float dot(const Vector2& v)const;		// ���ς����߂�
		float cross(const Vector2& v)const;
		double distance(const Vector2& a)const;// ����

		// �P�����Z�q�I�[�o�[���[�h
		Vector2 operator+() const;
		Vector2 operator-() const;

		// ������Z�q�I�[�o�[���[�h
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