#pragma once
#include "Math/Vector4.h"
#include "Math/Matrix4.h"

struct ConstBufferData
{
	Math::Vector4 color;	// F(RGBA)
	Math::Matrix4 myMat;		// 3D•ÏŠ·s—ñ
};