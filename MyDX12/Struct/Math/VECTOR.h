#pragma once

namespace Math {

	struct Vector3;

	struct VECTOR
	{
		float r[4];

		VECTOR();
		VECTOR(float r, float g, float b);
		VECTOR(float r, float g, float b, float a);
		VECTOR(const Vector3& v);

		Vector3 GetVector3()const;
	};

	VECTOR CrossVector(const VECTOR& v1, const VECTOR& v2);
}