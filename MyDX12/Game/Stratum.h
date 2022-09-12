#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

// ŠK‘wƒf[ƒ^
struct Stratum
{
public: // ŠÖ”
	static std::vector<unsigned int> GetStratumData(float yPos,float size = 0.0f); // ¡‚¢‚éŠK‘wƒf[ƒ^‚ğ•Ô‚·

private: // •Ï”
	static std::vector<unsigned int> stratumData;	// ŠK‘wƒf[ƒ^
	static unsigned int stratum; // ŠK‘w
private: // ’è”
	static const float LAYER_HEIGHT;
};

