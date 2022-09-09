#pragma once
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

// �O���錾
class Object3D;

// �v���C���[�N���X
class Player
{
private: // �\���� or �񋓌^ 
	// ���
	enum struct State:int
	{
		none = 0, // �Ȃ�
		speedDown, // ����
		speedUp, // ����
		invincible, // ���G
	};
private: // �����o�萔
	int INVINCIBLE_TIME = 60.0f; // ���G����
public: // �����o�֐�
	Player() = default; // �R���X�g���N�^
	~Player(); // �f�X�g���N�^
	static Player* Create(Math::Vector3 createPos); // �����֐�
	void Initialize(Math::Vector3 createPos); // ������
	void Update(); // ���t���[������
	void Draw(); // �`��

	void SetCollsion(); // �����蔻���ݒ�
	void SetSkillAbility(); // ��Ԃɂ���ăo�t�f�o�t��t�^

	Math::Sphere GetCollision()const { return collSphere; }
private: // �����o�ϐ�
	Object3D* object = nullptr; // �Q�[���I�u�W�F�N�g
	State state = State::none; // �v���C���[�̏��
	int hitPoint = 3; // �̗�(��)
	Math::Vector3 position; // ���W
	Math::Vector3 velocity; // ���x
	Math::Vector3 acc; // �����x
	float stateAcc = 1.0f; // ��Ԃɂ���Č��܂�������l�{��
	bool invincible = false; // ���G�t���O
	int invincibleCnt = 0; // ���G���Ԃ̃J�E���g

	// �����蔻��m�F�p
	Object3D* boxObj = nullptr; // box3D�I�u�W�F�N�g
	Math::Sphere collSphere; // �����蔻��p�@��
	Math::AABB collBox; // �����蔻��p�@��
	bool hitFlag = false; // �����蔻��t���O
};

