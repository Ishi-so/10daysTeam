#include "Stratum.h"

std::vector<unsigned int> Stratum::stratumData = {};	// �K�w�f�[�^
unsigned int Stratum::stratum = 0; // �K�w
const float Stratum::LAYER_HEIGHT = 15.0f;

std::vector<unsigned int> Stratum::GetStratumData(float yPos, float size)
{
    // �z��(vector)��`
    std::vector<unsigned int> data{};

    // �����`
    const float maxPos = abs(yPos) - size;
    const float minPos = abs(yPos) + size;
    
    // ���W����K�w�Z�o
    stratum = (maxPos / LAYER_HEIGHT) + 1;
    data.emplace_back(stratum);
    const int twoStratum = (minPos / LAYER_HEIGHT) + 1;
    // 2�ڂ̊K�w�ݒ�
    data.emplace_back(twoStratum);

    // �K�w�f�[�^����
    stratumData = data;
    data.clear();
    return stratumData;
}
