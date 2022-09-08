#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"

class Object3D;

class GameObj {
protected:
	std::string id;			// �N���X�l�[��
	Math::Vector3 pos;		// ���W
	bool isActive = true;	// ���݂̗L���p�t���O

	Object3D* obj = nullptr;// �I�u�W�F�N�g�f�[�^

public:
	GameObj() = default;
	virtual ~GameObj() {};

	virtual void Init() = 0;	// ������
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

	// ���ʊ֐�
	std::string GetID()const { return id; }		// �N���X�l�[���擾
	Math::Vector3 GetPos()const { return pos; }	// ���W�̎擾
	bool GetIsActive()const { return isActive; }// ���݂��Ă��邩�ǂ���
};