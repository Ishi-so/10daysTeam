#pragma once
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"
#include <string>

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

	// �v���C���[�̏��
	struct Info 
	{
		float radius = 0.5f;
		float edge = 0.0f;
	};
	struct Info info; // ���̕ϐ�

private: // �����o�萔
	const int INVINCIBLE_TIME = 60.0f; // ���G����
	const float SIZE = 3.0f; // �K�w���ʔ���̃T�C�Y
	const float MAX_AREA = 10.4f; // �����̏��

public: // �����o�֐�
	// �ėp�֐�
	Player() = default; // �R���X�g���N�^
	~Player(); // �f�X�g���N�^
	static Player* Create(Math::Vector3 createPos); // �����֐�
	void Initialize(Math::Vector3 createPos); // ������
	void Update(); // ���t���[������
	void Draw(); // �`��
	void HitUpdate(std::string& skillName); // �������Ƃ���p����
	
	// ---- Setter Getter ---- 
	/* Setter */
	void SetHitFlag(bool flag) { hitFlag = flag; }// hitFlag��ݒ�

	/* Getter */
	Math::Vector3 GetPosition()const { return position; } // ���W���擾
	Math::Sphere GetCollision()const { return collSphere; } // �����蔻����擾
	bool GetDeathFlag()const { return deathFlag; } // ���S�t���O�̎擾
	std::vector<unsigned int> GetStratumData()const { return stratumData; } // �K�w�f�[�^���擾
	Math::Vector3 GetDirection()const { return direction; } // �������擾

private: // �ŗL�����o�֐�(private)
	// �ŗL�֐�
	void SetCollsion(); // �����蔻���ݒ�
	void SetSkillAbility(); // ��Ԃɂ���ăo�t�f�o�t��t�^
	void SetSkill(); // skill����state��ݒ�

private: // �����o�ϐ�
	// Player�f�[�^
	Object3D* object = nullptr; // �Q�[���I�u�W�F�N�g
	State state = State::none; // �v���C���[�̏��
	int hitPoint = 3; // �̗�(��)
	Math::Vector3 position; // ���W
	Math::Vector3 velocity; // ���x
	Math::Vector3 acc; // �����x
	Math::Vector3 prevPos; // 1f�O�̍��W
	Math::Vector3 direction; // �ړ�����
	bool deathFlag = false; // ���S�t���O
	std::vector<unsigned int> stratumData; // �K�w�f�[�^

	// �v���C���[�̏�Ԍn
	float stateAcc = 1.0f; // ��Ԃɂ���Č��܂�������l�{��
	bool invincible = false; // ���G�t���O
	int invincibleCnt = 0; // ���G���Ԃ̃J�E���g

	// �����蔻��m�F�p
	Math::Sphere collSphere; // �����蔻��p�@��
	bool hitFlag = false; // �����蔻��t���O
};

