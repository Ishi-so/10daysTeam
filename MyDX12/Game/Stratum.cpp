#include "Stratum.h"

std::vector<unsigned int> Stratum::stratumData(2);	// �K�w�f�[�^
unsigned int Stratum::stratum = 0; // �K�w
const float Stratum::LAYER_HEIGHT = 15.0f;

std::vector<unsigned int> Stratum::GetStratumData(float yPos, float size)
{
    // �z���`
    std::vector<unsigned int> data(2);

    // �����`
    const float maxPos = yPos + size;
    const float minPos = yPos - size;
    
    // ���W����
    stratum = (maxPos / LAYER_HEIGHT) + 1;
    data.emplace_back(stratum);
    const int twoStratum = (minPos / LAYER_HEIGHT) + 1;
    if (stratum != twoStratum)
    {
        data.emplace_back(twoStratum);
    }

    // ���
    stratumData = data;
    return stratumData;
}
