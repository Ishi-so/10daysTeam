#include "Stratum.h"

std::vector<unsigned int> Stratum::stratumData = {};	// ŠK‘wƒf[ƒ^
unsigned int Stratum::stratum = 0; // ŠK‘w
const float Stratum::LAYER_HEIGHT = 15.0f;

std::vector<unsigned int> Stratum::GetStratumData(float yPos, float size)
{
    // ”z—ñ(vector)’è‹`
    std::vector<unsigned int> data{};

    // ü‚ğ’è‹`
    const float maxPos = abs(yPos) - size;
    const float minPos = abs(yPos) + size;
    
    // À•W‚©‚çŠK‘wZo
    stratum = (maxPos / LAYER_HEIGHT) + 1;
    data.emplace_back(stratum);
    const int twoStratum = (minPos / LAYER_HEIGHT) + 1;
    // 2‚Â–Ú‚ÌŠK‘wİ’è
    data.emplace_back(twoStratum);

    // ŠK‘wƒf[ƒ^‚ğ‘ã“ü
    stratumData = data;
    data.clear();
    return stratumData;
}
