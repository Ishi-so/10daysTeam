#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

// �K�w�f�[�^
struct Stratum
{
public: // �֐�
	static std::vector<unsigned int> GetStratumData(float yPos,float size = 0.0f); // ������K�w�f�[�^��Ԃ�

private: // �ϐ�
	static std::vector<unsigned int> stratumData;	// �K�w�f�[�^
	static unsigned int stratum; // �K�w
private: // �萔
	static const float LAYER_HEIGHT;
};

