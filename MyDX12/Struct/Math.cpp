#include "Math.h"
#include <cmath>
#include <xmmintrin.h>
#define PI 3.14159265358979323846

using namespace Math;

float Math::ConvertToRadians(float degree)
{
	return degree * (PI / 180.0f);
}

float Math::Transform(float bnMax, float aMax, float bNow)
{
	float afbn = aMax * bNow;
	float ms = bnMax;
	return afbn /ms;
}