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
	delete boxObj;
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
	// ���W�̐ݒ�
	position = createPos;
	// �I�u�W�F�N�g�̐����ݒ�
	object = Object3D::Create(Model::CreateFromOBJ("sphere"));
	object->position = position;

	boxObj = Object3D::Create(Model::CreateFromOBJ("box_v000"));
	boxObj->position = {5.0f,0.0f,0.0f};

	// �����蔻���t��������
	SetCollsion();

	// �K�w�f�[�^�̏�����
	stratumData.resize(2);
	stratumData = Stratum::GetStratumData(position.y, SIZE);
}

void Player::Update()
{
	// ��Ԃ����Z�b�g
	state = State::none;

	// ---- �ړ� ----
	// �L�[�{�[�h����
	if (KeyInput::GetInstance()->Push(DIK_D)) // �E�ړ�
	{
		acc.x = 0.02f;
	}
	else if (KeyInput::GetInstance()->Push(DIK_A)) // ���ړ�
	{
		acc.x = -0.02f;
	}
	else // �ړ����Ă��Ȃ�
	{
		// �����Â�~
		acc.x = 0.0f;
		if (velocity.x > 0) {
			velocity.x += -0.02f;
		}
		else if (velocity.x < 0)
		{
			velocity.x += 0.02f;
		}
	}

	// ����
	//acc.y = -0.1f;

	// ���E�����x����
	if (abs(velocity.x) > 0.1f)
	{
		if (velocity.x > 0) {
			velocity.x += 0.1f - velocity.x;
		}
		else if (velocity.x < 0)
		{
			velocity.x += -0.1f - velocity.x;
		}
	}
	
	// ���������x����
	if (velocity.y < -0.3f)
	{
		velocity.y = -0.3f;
	}
	
	// ---- ���W�̍X�V ----
	velocity += acc;
	position += velocity * stateAcc;
	object->position = position; // ���W�̐ݒ�

	// ---- �����蔻���t�� ----
	SetCollsion();

	// ---- �����蔻�� ----
	// ObjectManager�ɋL��

	if (!invincible) {
		// box�̐F��߂�
		boxObj->color = { 1,1,1 };
	}

	// ��Ԃɂ���Č��ʂ�t�^
	SetSkillAbility();

	// �̗͂�0�����ɂȂ�����
	if (hitPoint <= 0)
	{
		object->color = { 1,0,1 };
	}

	// ---- �ŏI�I�ȍ��W��ݒ�@----
	object->position = position; // ���߂Đݒ�(�����������ɉ����o���������l��)

	// �K�w�f�[�^�̍X�V
	stratumData = Stratum::GetStratumData(position.y, SIZE);
	//stratumData = {2,3};

	// ---- object�̍X�V ----
	object->Update();
	boxObj->Update();

	// ---- �J�E���g ----
	// ���G��Ԃ��A�J�E���g���ő�܂ł�������
	if (invincibleCnt >= INVINCIBLE_TIME && invincible) 
	{
		// ���G����
		invincible = false;
		// �J�E���g��0�N���A
		invincibleCnt = 0;
		// player�̐F��߂�
		object->color = { 1,1,1 };
		// ��Ԃ�߂�
		state = State::none;
	}

	// ���G��ԂȂ�
	if(invincible){ invincibleCnt++; } // ���G���Ԃ��J�E���g
}

void Player::Draw()
{
	// object�̕`��
	object->Draw();
	boxObj->Draw();
}

void Player::HitUpdate()
{
	// box��ԐF�ɐݒ�
	boxObj->color = { 1,0,0 };
	// ���G��Ԃ���Ȃ�������
	if (!invincible)
	{
		// �v���C���[�Ƀ_���[�W
		hitPoint--;
		// player��F�ɐݒ�
		object->color = { 0,0,1 };
		// ���G�t�^
		state = State::invincible;
		// ��Ԃɂ���Č��ʂ�t�^
		SetSkillAbility();
	}
}

void Player::SetCollsion()
{
	// sphere
	collSphere.pos = Math::Vector4(object->position.x, object->position.y, object->position.z, 1.0f);
	collSphere.r = object->scale.x;

	// box
	collBox.max = Math::Vector4(boxObj->position.x + boxObj->scale.x,
		boxObj->position.y + boxObj->scale.y,
		boxObj->position.z + boxObj->scale.z,
		1.0f);
	collBox.min = Math::Vector4(boxObj->position.x - boxObj->scale.x,
		boxObj->position.y - boxObj->scale.y,
		boxObj->position.z - boxObj->scale.z,
		1.0f);
}

void Player::SetSkillAbility()
{
	// ��Ԃɂ���Ă��ꂼ��̌��ʂ�t�^
	if (state == State::none)
	{
		stateAcc = 1.0f;
	}
	else if (state == State::speedDown)
	{
		stateAcc = 0.5f;
	}
	else if (state == State::speedUp)
	{
		stateAcc = 1.5f;
	}
	else if (state == State::invincible)
	{
		invincible = true;
	}
	else
	{
		stateAcc = 1.0f;
	}
}
