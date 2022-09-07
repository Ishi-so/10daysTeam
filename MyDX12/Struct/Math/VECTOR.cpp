#include "VECTOR.h"
#include "Vector3.h"

Math::VECTOR::VECTOR() :r{ 0,0,0,1 }
{}

Math::VECTOR::VECTOR(float x, float y, float z) : r{ x,y,z,1 }
{}

Math::VECTOR::VECTOR(float x, float y, float z, float a)
	: r{ x,y,z,a }
{
}

Math::VECTOR::VECTOR(const Vector3& v)
	:r{v.x,v.y,v.z,0}
{
}

Math::Vector3 Math::VECTOR::GetVector3()const
{
	Vector3 result = { r[0],r[1],r[2] };
	return result;
}

Math::VECTOR Math::CrossVector(const VECTOR& v1, const VECTOR& v2)
{
	Vector3 v3_1 = v1.GetVector3(),
			v3_2 = v2.GetVector3();

	return VECTOR(v3_1.cross(v3_2));
}
