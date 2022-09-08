#pragma once
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

// �O���錾
class Object3D;

// �v���C���[�N���X
class Player
{
private: // �����o�萔
public: // �����o�֐�
	Player() = default; // �R���X�g���N�^
	~Player(); // �f�X�g���N�^
	static Player* Create(); // �����֐�
	void Initialize(); // ������
	void Update(); // ���t���[������
	void Draw(); // �`��

	void SetCollsion(); // �����蔻���ݒ�
private: // �����o�ϐ�
	Object3D* object = nullptr; // �Q�[���I�u�W�F�N�g
	int hitPoint = 3; // �̗�(��)
	Math::Vector3 position; // ���W
	Math::Vector3 velocity; // ���x
	Math::Vector3 acc; // �����x

	// �����蔻��m�F�p
	Object3D* boxObj = nullptr;
	Math::Sphere collSphere;
	Math::AABB collBox;
};

