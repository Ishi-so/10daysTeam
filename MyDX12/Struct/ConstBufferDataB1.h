#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "../Struct/Math/Vector3.h"

struct ConstBufferDataB1
{
	Math::Vector3 ambient; // �A���r�G���g�W��
	float pad1; // �p�f�B���O
	Math::Vector3 diffuse; // �f�B�t���[�Y�W��
	float pad2; // �p�f�B���O
	Math::Vector3 specular; // �X�y�L�����[�W��
	float alpha;	// �A���t�@
};