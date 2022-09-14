#include "Player.h"
#include "../Struct/Math/Vector3.h"
#include "../3D/Object3D.h"
#include "../Input/KeyInput.h"
#include "Stratum.h"

using namespace XIIlib;
/*Player::Player()
{}*/

Player::~Player()
{
	delete object;
}

Player* Player::Create(Math::Vector3 createPos)
{
	// ����
	Player* player = new Player();

	// ������
	player->Initialize(createPos);

	return player;
}

void Player::Initialize(Math::Vector3 createPos)
{
	// ---- ���W�̐ݒ� ----
	defaultPos = createPos; // �������̍��W���f�t�H���g�ɐݒ�
	position = defaultPos;

	// ---- �I�u�W�F�N�g�̐����ݒ� ----
	// �v���C���[�I�u�W�F�N�g���f��
	object = Object3D::Create(Model::CreateFromOBJ("sphere"));
	object->position = position;
	info.radius = object->scale.x / 2;
	info.edge = object->position.x + info.radius; // �v���C���[�I�u�W�F�N�g�̒[����

	// ---- �����蔻���t�������� ----
	SetCollsion();

	// ---- �K�w�f�[�^�̏����� ----
	stratumData.resize(2);
	stratumData = Stratum::GetStratumData(position.y, SIZE);
}

void Player::Update()
{
	// ��Ԃ����Z�b�g
	//state = State::none;
	// ���݂̍��W��ۑ�
	prevPos = position;

	// ---- �ړ� ----
	// �L�[�{�[�h����
	if (KeyInput::GetInstance()->Push(DIK_D)) // �E�ړ�
	{
		acc.x = ADD_ACC;
	}
	else if (KeyInput::GetInstance()->Push(DIK_A)) // ���ړ�
	{
		acc.x = -ADD_ACC;
	}
	else // �ړ����Ă��Ȃ�
	{
		// �����Â�~
		acc.x = 0.0f;
		if (velocity.x > 0) {
			velocity.x += -SUB_ACC;
		}
		else if (velocity.x < 0)
		{
			velocity.x += SUB_ACC;
		}
	}

	// ����
	if(startFlag)acc.y = GRAVITY;
	
	// ���E�����x����(0.1f�ȓ��ɒ���)
	if (abs(velocity.x) > 0.1f) // velo��0.1f�ȏ�ɂȂ��
	{
		if (velocity.x > 0) // velo��+�Ȃ�
		{
			velocity.x += 0.1f - velocity.x;
		}
		else if (velocity.x < 0) // velo��-�Ȃ�
		{
			velocity.x += -0.1f - velocity.x;
		}
	}
	
	// ���������x����
	if (velocity.y < MAX_GRAVITY)
	{
		velocity.y = MAX_GRAVITY;
	}
	
	// ---- ���W�Ɖ�]�̍X�V ----
	const float MAX_ROT = 360.0f;
	rotation.z += ADD_ROT_Z;
	if (rotation.z >= MAX_ROT) {
		rotation.z = rotation.z - MAX_ROT;
	}
	velocity += acc; 
	position.y += velocity.y * stateAcc; // ���Z���ꂽvelo�Ə�ԉ����ɂ���č��W���X�V
	position.x += velocity.x;

	// ���ǂ͈̔͏��
	if (MAX_AREA <= position.x + info.radius)
	{
		// �����o��
		position.x = MAX_AREA - info.radius;
	}
	else if (position.x - info.radius <= -MAX_AREA)
	{
		// �����o��
		position.x = -MAX_AREA + info.radius;
	}
	
	object->position = position; // ���W�̐ݒ�
	direction = position - prevPos; // ������ݒ�

	// ---- �����蔻���t�� ----
	SetCollsion();

	// ---- �����蔻�� ----
	// ObjectManager�ɋL��
	
	// ---- �v���C���[��ԍX�V ----
	// ��Ԃɂ���Č��ʂ�t�^
	//StateControl();

	// �̗͂�0�����ɂȂ�����
	if (hitPoint <= 0)
	{
		InitPlayerData();
		deathFlag = true;
	}

	// ---- �ŏI�I�ȍ��W�Ɖ�]��ݒ�@----
	object->rotation = rotation; // ��]��ݒ�
	object->position = position; // ���߂Đݒ�(�����������ɉ����o���������l��)

	// �K�w�f�[�^�̍X�V
	stratumData = Stratum::GetStratumData(position.y, SIZE);

	// ---- object�̍X�V ----
	object->Update();

	// ---- �J�E���g ----
	// ���G��Ԃ��A�J�E���g���ő�܂ł�������
	if (invincibleCnt >= INVINCIBLE_TIME && invincible) 
	{
		// �q�b�g�t���O�𗧂Ă�
		hitFlag = false;
		// ���G����
		invincible = false;
		// �J�E���g��0�N���A
		invincibleCnt = 0;
	}

	// ���G��ԂȂ�
	if(invincible)
	{
		if (invincibleCnt % 5 == 0)
		{
			if (object->alpha >= 1.0f) { object->alpha = 0.0f; }
			else if (object->alpha <= 0.0f) { object->alpha = 1.0f; }
		}
		
		// ���G���Ԃ��J�E���g
		invincibleCnt++; 
	} 
}

void Player::Draw()
{
	// object�̕`��
	object->Draw();
}

void Player::HitUpdate(std::string& skillName)
{
	// �S�[���u���b�N�Ɠ���������t���O��ς��ă��^�[��
	if (skillName == "Goal") { 
		goalFlag = true; 
		return;
	}

	// ���G��Ԃł���Α����^�[��
	if (invincible)return;
	// ��Ԃɂ���Č��ʂ�t�^
	SetGameObjAbility(skillName);
	StateControl();
}

void Player::InitPlayerData()
{
	// ������
	// ��{���
	state = State::none; // �v���C���[�̏��
	hitPoint = 3; // �̗�(��)
	position = defaultPos; // ���W
	velocity = {}; // ���x
	acc = {}; // �����x
	prevPos = defaultPos; // 1f�O�̍��W
	rotation = {}; // ��]
	direction = {}; // �ړ�����
	deathFlag = false; // ���S�t���O
	stratumData = {0,0}; // �K�w�f�[�^
	startFlag = false;
	goalFlag = false;

	// �v���C���[�̏�Ԍn
	stateAcc = 1.0f; // ��Ԃɂ���Č��܂�������l�{��
	invincible = false; // ���G�t���O
	invincibleCnt = 0; // ���G���Ԃ̃J�E���g

	// �����蔻��m�F�p
	hitFlag = false; // �����蔻��t���O

	// object�n
	object->alpha = 1.0f;
}

void Player::SetCollsion()
{
	// �����蔻���ݒ�
	collSphere.pos = Math::Vector4(object->position.x, object->position.y, object->position.z, 1.0f);
	collSphere.r = object->scale.x;
}

void Player::StateControl()
{
	// ��Ԃɂ���Ă��ꂼ��̌��ʂ�t�^
	if (state == State::none)
	{
		stateAcc = 1.0f;
	}
	else if (state == State::speedDown)
	{
		// HP�ɂ���Č�����ω�
		if (hitPoint == 2) {
			stateAcc = 0.7f;
		}
		else if (hitPoint == 1)
		{
			stateAcc = 0.4f;
		}
		else
		{
			stateAcc = 0.0f;
		}
	}
	else if (state == State::speedUp)
	{
		stateAcc = 1.4f;
	}
	else
	{
		stateAcc = 1.0f;
	}
}

void Player::SetGameObjAbility(std::string& skillName)
{
	// ���O�ɂ���ď�ԕω�
	if (skillName == "speedup")
	{
		state = State::speedUp;
	}
	else if (skillName == "speeddown") // block
	{
		state = State::speedDown;
		// �q�b�g�t���O�𗧂Ă�
		hitFlag = true;
		// �v���C���[�Ƀ_���[�W
		hitPoint--;
		// ���G�t�^
		invincible = true;
	}
}
