#include "Matrix4.h"
#include "../Math.h"
#include "Vector3.h"
#include <cmath>

Math::Matrix4::Matrix4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				r[i].r[j] = 1;
			}
			else
			{
				r[i].r[j] = 0;
			}
		}
	}
}

Math::Matrix4& Math::Matrix4::Identity()
{
	*this = Matrix4();
	return *this;
}

Math::Matrix4& Math::Matrix4::operator*=(const Matrix4& m)
{
	*this = *this * m;
	return *this;
}

void Math::Matrix4::Transposed()
{
	Matrix4 tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++) {
			tmp.r[j].r[i] = this->r[i].r[j];
		}
	}
	*this = tmp;
}

void Math::Matrix4::Inverse()
{	
	float delta = r[0].r[0] * r[1].r[1] * r[2].r[2] * r[3].r[3] + r[0].r[0] * r[1].r[2] * r[2].r[3] * r[3].r[1] + r[0].r[0] * r[1].r[3] * r[2].r[1] * r[3].r[2] +
		r[0].r[1] * r[1].r[0] * r[2].r[3] * r[3].r[2] + r[0].r[1] * r[1].r[2] * r[2].r[0] * r[3].r[3] + r[0].r[1] * r[1].r[3] * r[2].r[2] * r[3].r[0] +
		r[0].r[2] * r[1].r[0] * r[2].r[1] * r[3].r[3] + r[0].r[2] * r[1].r[1] * r[2].r[3] * r[3].r[0] + r[0].r[2] * r[1].r[3] * r[2].r[0] * r[3].r[1] +
		r[0].r[3] * r[1].r[0] * r[2].r[2] * r[3].r[1] + r[0].r[3] * r[1].r[1] * r[2].r[0] * r[3].r[2] + r[0].r[3] * r[1].r[2] * r[2].r[1] * r[3].r[0] -
		r[0].r[0] * r[1].r[1] * r[2].r[3] * r[3].r[2] - r[0].r[0] * r[1].r[2] * r[2].r[1] * r[3].r[3] - r[0].r[0] * r[1].r[3] * r[2].r[2] * r[3].r[1] -
		r[0].r[1] * r[1].r[0] * r[2].r[2] * r[3].r[3] - r[0].r[1] * r[1].r[2] * r[2].r[3] * r[3].r[0] - r[0].r[1] * r[1].r[3] * r[2].r[0] * r[3].r[2] -
		r[0].r[2] * r[1].r[0] * r[2].r[3] * r[3].r[1] - r[0].r[2] * r[1].r[1] * r[2].r[0] * r[3].r[3] - r[0].r[2] * r[1].r[3] * r[2].r[1] * r[3].r[0] -
		r[0].r[3] * r[1].r[0] * r[2].r[1] * r[3].r[2] - r[0].r[3] * r[1].r[1] * r[2].r[2] * r[3].r[0] - r[0].r[3] * r[1].r[2] * r[2].r[0] * r[3].r[1];

	// É¢(ÉfÉãÉ^) = 0ÇÃÇ∆Ç´ÇÕèàóùÇ≈Ç´Ç»Ç¢ÇÃÇ≈ÇªÇÃÇ‹Ç‹ï‘Ç∑
	if (delta == 0.0f)return;
	delta = 1.0f / delta;		// ó\ÇﬂãtêîÇ…ÇµÇƒÇ®Ç≠

	Matrix4 result;
	result.r[0].r[0] = delta * (r[1].r[1] * r[2].r[2] * r[3].r[3] + r[1].r[2] * r[2].r[3] * r[3].r[1] + r[1].r[3] * r[2].r[1] * r[3].r[2] -
		r[1].r[1] * r[2].r[3] * r[3].r[2] - r[1].r[2] * r[2].r[1] * r[3].r[3] - r[1].r[3] * r[2].r[2] * r[3].r[1]);
	result.r[0].r[1] = delta * (r[0].r[1] * r[2].r[3] * r[3].r[2] + r[0].r[2] * r[2].r[1] * r[3].r[3] + r[0].r[3] * r[2].r[2] * r[3].r[1] -
		r[0].r[1] * r[2].r[2] * r[3].r[3] - r[0].r[2] * r[2].r[3] * r[3].r[1] - r[0].r[3] * r[2].r[1] * r[3].r[2]);
	result.r[0].r[2] = delta * (r[0].r[1] * r[1].r[2] * r[3].r[3] + r[0].r[2] * r[1].r[3] * r[3].r[1] + r[0].r[3] * r[1].r[1] * r[3].r[2] -
		r[0].r[1] * r[1].r[3] * r[3].r[2] - r[0].r[2] * r[1].r[1] * r[3].r[3] - r[0].r[3] * r[1].r[2] * r[3].r[1]);
	result.r[0].r[3] = delta * (r[0].r[1] * r[1].r[3] * r[2].r[2] + r[0].r[2] * r[1].r[1] * r[2].r[3] + r[0].r[3] * r[1].r[2] * r[2].r[1] -
		r[0].r[1] * r[1].r[2] * r[2].r[3] - r[0].r[2] * r[1].r[3] * r[2].r[1] - r[0].r[3] * r[1].r[1] * r[2].r[2]);

	result.r[1].r[0] = delta * (r[1].r[0] * r[2].r[3] * r[3].r[2] + r[1].r[2] * r[2].r[0] * r[3].r[3] + r[1].r[3] * r[2].r[2] * r[3].r[0] -
		r[1].r[0] * r[2].r[2] * r[3].r[3] - r[1].r[2] * r[2].r[3] * r[3].r[0] - r[1].r[3] * r[2].r[0] * r[3].r[2]);
	result.r[1].r[1] = delta * (r[0].r[0] * r[2].r[2] * r[3].r[3] + r[0].r[2] * r[2].r[3] * r[3].r[0] + r[0].r[3] * r[2].r[0] * r[3].r[2] -
		r[0].r[0] * r[2].r[3] * r[3].r[2] - r[0].r[2] * r[2].r[0] * r[3].r[3] - r[0].r[3] * r[2].r[2] * r[3].r[0]);
	result.r[1].r[2] = delta * (r[0].r[0] * r[1].r[3] * r[3].r[2] + r[0].r[2] * r[1].r[0] * r[3].r[3] + r[0].r[3] * r[1].r[2] * r[3].r[0] -
		r[0].r[0] * r[1].r[2] * r[3].r[3] - r[0].r[2] * r[1].r[3] * r[3].r[0] - r[0].r[3] * r[1].r[0] * r[3].r[2]);
	result.r[1].r[3] = delta * (r[0].r[0] * r[1].r[2] * r[2].r[3] + r[0].r[2] * r[1].r[3] * r[2].r[0] + r[0].r[3] * r[1].r[0] * r[2].r[2] -
		r[0].r[0] * r[1].r[3] * r[2].r[2] - r[0].r[2] * r[1].r[0] * r[2].r[3] - r[0].r[3] * r[1].r[2] * r[2].r[0]);

	result.r[2].r[0] = delta * (r[1].r[0] * r[2].r[1] * r[3].r[3] + r[1].r[1] * r[2].r[3] * r[3].r[0] + r[1].r[3] * r[2].r[0] * r[3].r[1] -
		r[1].r[0] * r[2].r[3] * r[3].r[1] - r[1].r[1] * r[2].r[0] * r[3].r[3] - r[1].r[3] * r[2].r[1] * r[3].r[0]);
	result.r[2].r[1] = delta * (r[0].r[0] * r[2].r[3] * r[3].r[1] + r[0].r[1] * r[2].r[0] * r[3].r[3] + r[0].r[3] * r[2].r[1] * r[3].r[0] -
		r[0].r[0] * r[2].r[1] * r[3].r[3] - r[0].r[1] * r[2].r[3] * r[3].r[0] - r[0].r[3] * r[2].r[0] * r[3].r[1]);
	result.r[2].r[2] = delta * (r[0].r[0] * r[1].r[1] * r[3].r[3] + r[0].r[1] * r[1].r[3] * r[3].r[0] + r[0].r[3] * r[1].r[0] * r[3].r[1] -
		r[0].r[0] * r[1].r[3] * r[3].r[1] - r[0].r[1] * r[1].r[0] * r[3].r[3] - r[0].r[3] * r[1].r[1] * r[3].r[0]);
	result.r[2].r[3] = delta * (r[0].r[0] * r[1].r[3] * r[2].r[1] + r[0].r[1] * r[1].r[0] * r[2].r[3] + r[0].r[3] * r[1].r[1] * r[2].r[0] - 
		r[0].r[0] * r[1].r[1] * r[2].r[3] - r[0].r[1] * r[1].r[3] * r[2].r[0] - r[0].r[3] * r[1].r[0] * r[2].r[1]);

	result.r[3].r[0] = delta * (r[1].r[0] * r[2].r[2] * r[3].r[1] + r[1].r[1] * r[2].r[0] * r[3].r[2] + r[1].r[2] * r[2].r[1] * r[3].r[0] -
		r[1].r[0] * r[2].r[1] * r[3].r[2] - r[1].r[1] * r[2].r[2] * r[3].r[0] - r[1].r[2] * r[2].r[0] * r[3].r[1]);
	result.r[3].r[1] = delta * (r[0].r[0] * r[2].r[1] * r[3].r[2] + r[0].r[1] * r[2].r[2] * r[3].r[0] + r[0].r[2] * r[2].r[0] * r[3].r[1] -
		r[0].r[0] * r[2].r[2] * r[3].r[1] - r[0].r[1] * r[2].r[0] * r[3].r[2] - r[0].r[2] * r[2].r[1] * r[3].r[0]);
	result.r[3].r[2] = delta * (r[0].r[0] * r[1].r[2] * r[3].r[1] + r[0].r[1] * r[1].r[0] * r[3].r[2] + r[0].r[2] * r[1].r[1] * r[3].r[0] -
		r[0].r[0] * r[1].r[1] * r[3].r[2] - r[0].r[1] * r[1].r[2] * r[3].r[0] - r[0].r[2] * r[1].r[0] * r[3].r[1]);
	result.r[3].r[3] = delta * (r[0].r[0] * r[1].r[1] * r[2].r[2] + r[0].r[1] * r[1].r[2] * r[2].r[0] + r[0].r[2] * r[1].r[0] * r[2].r[1] - 
		r[0].r[0] * r[1].r[2] * r[2].r[1] - r[0].r[1] * r[1].r[0] * r[2].r[2] - r[0].r[2] * r[1].r[1] * r[2].r[0]);

	*this = result;
}

const Math::Matrix4 Math::operator*(const Math::Matrix4& m1, const Math::Matrix4& m2)
{
	Math::Matrix4 result;
	Matrix4 a = m1,b = m2;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float temp = 0.0f;

			for (int k = 0; k < 4; k++)
			{
				temp += a.r[i].r[k] * b.r[k].r[j];
			}

			result.r[i].r[j] = temp;
		}
	}

	return result;
}

const Math::VECTOR Math::operator*(const Math::VECTOR& v, const Math::Matrix4& m)
{
	Math::VECTOR result;
	for (int i = 0; i < 4; i++)
	{
		float temp = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			temp += v.r[j] * m.r[j].r[i];
		}

		result.r[i] = temp;
	}

	return result;
}

Math::Matrix4 Math::MatrixOrthoOffCenterLH(float left, float right, float bottom, float top, float near, float far)
{
	Math::Matrix4 projectionResult;
	projectionResult.r[0].r[0] = 2.0f / (right - left);
	projectionResult.r[1].r[1] = 2.0f / (top - bottom);
	projectionResult.r[2].r[2] = 1.0f / (far - near);
	projectionResult.r[3].r[0] = (left + right) / (left - right);
	projectionResult.r[3].r[1] = (top + bottom) / (bottom - top);
	projectionResult.r[3].r[2] = near / (near - far);

	return projectionResult;
}

Math::Matrix4 Math::MatrixLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	Vector3 zT = Vector3(eye - target).normalize();
	Vector3 xT = Vector3(up.cross(zT)).normalize();
	Vector3 yT = zT.cross(xT);

	Matrix4 rV = Matrix4();
	// h->vÇÃèá
	rV.r[0].r[0] = xT.x;
	rV.r[0].r[1] = xT.y;
	rV.r[0].r[2] = xT.z;

	rV.r[1].r[0] = yT.x;
	rV.r[1].r[1] = yT.y;
	rV.r[1].r[2] = yT.z;

	rV.r[2].r[0] = -zT.x;
	rV.r[2].r[1] = -zT.y;
	rV.r[2].r[2] = -zT.z;

	Matrix4 tV = Matrix4();
	tV.r[3].r[0] = -eye.x;
	tV.r[3].r[1] = -eye.y;
	tV.r[3].r[2] = -eye.z;

	rV.Transposed();
	tV.Transposed();

	Matrix4 result = rV * tV;

	return result;
}

Math::Matrix4 Math::MatrixPerspectiveFovLH(float fov, float aspect, float near, float far)
{
	Math::Matrix4 result = Matrix4();
	float field = 1.0f / (tanf(fov * 0.5f));
	result.r[0].r[0] = field / aspect;
	result.r[1].r[1] = field;
	result.r[2].r[2] = ((far + near)/(far - near));
	result.r[2].r[3] = 1.0f;
	result.r[3].r[2] = -((far * near) / (far - near));
	result.r[3].r[3] = 0.0f;

	return result;
}

Math::Matrix4 Math::Scaling(float x, float y, float z)
{
	Math::Matrix4 m;

	m.r[0].r[0] = x;
	m.r[1].r[1] = y;
	m.r[2].r[2] = z;
	return m;
}

Math::Matrix4 Math::RotX(float rot)
{
	Math::Matrix4 m;
	m.r[1].r[1] = std::cosf(ConvertToRadians(rot));
	m.r[1].r[2] = std::sinf(ConvertToRadians(rot));
	m.r[2].r[1] = -std::sinf(ConvertToRadians(rot));
	m.r[2].r[2] = std::cosf(ConvertToRadians(rot));
	return m;
}

Math::Matrix4 Math::RotY(float rot)
{
	Math::Matrix4 m;
	m.r[0].r[0] = std::cosf(ConvertToRadians(rot));
	m.r[0].r[2] = -std::sinf(ConvertToRadians(rot));
	m.r[2].r[0] = std::sinf(ConvertToRadians(rot));
	m.r[2].r[2] = std::cosf(ConvertToRadians(rot));
	return m;
}

Math::Matrix4 Math::RotZ(float rot)
{
	Math::Matrix4 m;
	m.r[0].r[0] = std::cosf(ConvertToRadians(rot));
	m.r[0].r[1] = std::sinf(ConvertToRadians(rot));
	m.r[1].r[0] = -std::sinf(ConvertToRadians(rot));
	m.r[1].r[1] = std::cosf(ConvertToRadians(rot));
	return m;
}

Math::Matrix4 Math::Translation(float x, float y, float z)
{
	Math::Matrix4 m;
	m.r[3].r[0] = x;
	m.r[3].r[1] = y;
	m.r[3].r[2] = z;
	return m;
}