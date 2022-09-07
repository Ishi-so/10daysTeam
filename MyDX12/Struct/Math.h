#pragma once
#include <vector>
#include "Math/Vector2.h"
#include "Math/Vector4.h"

namespace Math
{
	struct IMG_DATA
	{
		Vector2 position;
		float rotation;
		Vector2 scale;
		Vector4 color;
	};

	// 255 : 1 = 130 : x => x = 130/255
	float Transform(float bnMax, float aMax,float bNow);

	float ConvertToRadians(float degree);
}