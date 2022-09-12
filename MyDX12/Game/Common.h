#pragma once
#include <string>

namespace Common {
	static float posStartX = -14.0f,posStartY = 0.0f;
	static float posDistance = 2.0f;
	static float constFrame = 1.0f / 60.0f;// 1�t���[�����̏����_�^

	// �N���X�l�[���̎��o���֐�
	std::pair<std::string, std::string> SeparateFilePath(const std::string& path);

	// �v�f����f�Ɉʒu���W���擾
	float ConvertPositionX(int point);// X���W
	float ConvertPositionY(int point);// Y���W
}