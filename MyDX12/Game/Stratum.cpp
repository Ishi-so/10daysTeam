#include "Stratum.h"

std::vector<unsigned int> Stratum::stratumData(2);	// 階層データ
unsigned int Stratum::stratum = 0; // 階層
const float Stratum::LAYER_HEIGHT = 15.0f;

std::vector<unsigned int> Stratum::GetStratumData(float yPos, float size)
{
    // 配列定義
    std::vector<unsigned int> data(2);

    // 線を定義
    const float maxPos = yPos + size;
    const float minPos = yPos - size;
    
    // 座標から
    stratum = (maxPos / LAYER_HEIGHT) + 1;
    data.emplace_back(stratum);
    const int twoStratum = (minPos / LAYER_HEIGHT) + 1;
    if (stratum != twoStratum)
    {
        data.emplace_back(twoStratum);
    }

    // 代入
    stratumData = data;
    return stratumData;
}
