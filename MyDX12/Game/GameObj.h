#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

class Object3D;

class GameObj {
protected:
	std::string id;			// �N���X�l�[��
	Math::Vector3 pos;		// ���W
	Math::Vector3 scale;	// �X�P�[��
	bool isActive = true;	// ���݂̗L���p�t���O
	Math::AABB collisionData;

	Object3D* obj = nullptr;// �I�u�W�F�N�g�f�[�^

public:
	GameObj() = default;
	virtual ~GameObj() {};

	virtual void Init() = 0;	// ������
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

	// ���ʊ֐�
	//�E�E�EGet�E�E�E
	std::string GetID()const { return id; }						// �N���X�l�[���擾
	Math::Vector3 GetPos()const { return pos; }					// ���W�̎擾
	bool GetIsActive()const { return isActive; }				// ���݂��Ă��邩�ǂ���
	Math::AABB GetCollisionData()const { return collisionData; }// AABB�f�[�^�̎擾

	// �E�E�ESet�E�E�E
	void SetPos(const Math::Vector3& c_pos) { pos = c_pos; }	// ���W�̐ݒ�
	void SetScale(const Math::Vector3& c_scale) { scale = c_scale; }
};