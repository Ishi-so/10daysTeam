#pragma once
#include "../Struct/Math/Matrix4.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Vector4.h"

struct ConstBufferDataB0
{
	//XMMATRIX mat;	// �R�c�ϊ��s��
	Math::Vector4 color;
	Math::Matrix4 viewproj;	// �r���\�v���W�F�N�V�����s��
	Math::Matrix4 world;		// ���[���h�s��
	Math::Vector3 cameraPos;	// �J�������W(���[���h���W)

	Math::Vector4 lightpos;
	Math::Matrix4 wlp;
	Math::Matrix4 wlpt;
	Math::Vector3 pd;

	float _time;					// �V�F�[�_�[�����Ŏg���^�C�}�[
	float isElec;					// �V�F�[�_�[�^�C�v
};