#pragma once
#include "VECTOR.h"

namespace Math {

	struct Vector3;

	struct Matrix4
	{
		VECTOR r[4];

		Matrix4();	// 零行列

		Matrix4& Identity();	// 単位行列
		Matrix4& operator*=(const Matrix4& m);

		void Transposed();// 転置行列

		void Inverse();
	};

	const Math::Matrix4 operator* (const Math::Matrix4& m1, const Math::Matrix4& m2);
	const Math::VECTOR operator* (const Math::VECTOR& v, const Math::Matrix4& m);

	Math::Matrix4 MatrixOrthoOffCenterLH(float left,float right,float bottom,float top,float near,float far);
	Math::Matrix4 MatrixLookAtLH(const Vector3& eye,const Vector3& target,const Vector3& up);
	Math::Matrix4 MatrixPerspectiveFovLH(float fov,float aspect,float near,float far);
	Math::Matrix4 Scaling(float x, float y, float z);
	Math::Matrix4 RotX(float rot);
	Math::Matrix4 RotY(float rot);
	Math::Matrix4 RotZ(float rot);
	Math::Matrix4 Translation(float x, float y, float z);
}