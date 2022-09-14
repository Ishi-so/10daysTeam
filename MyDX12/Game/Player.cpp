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
	position = createPos;

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

	// �e�X�g�p
	//if (KeyInput::GetInstance()->Push(DIK_W)) // �E�ړ�
	//{
	//	position.y += 0.5f;
	//}
	//else if (KeyInput::GetInstance()->Push(DIK_S)) // ���ړ�
	//{
	//	position.y -= 0.5f;
	//}

	// ����
	acc.y = GRAVITY;

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
	
	// ---- ���W�̍X�V ----
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
	StateControl();

	// �̗͂�0�����ɂȂ�����
	if (hitPoint <= 0)
	{
		object->color = { 1,0,1 };
		deathFlag = true;
	}

	// ---- �ŏI�I�ȍ��W��ݒ�@----
	object->position = position; // ���߂Đݒ�(�����������ɉ����o���������l��)

	// �K�w�f�[�^�̍X�V
	stratumData = Stratum::GetStratumData(position.y, SIZE);

	// ---- object�̍X�V ----
	object->Update();

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
	}

	// ���G��ԂȂ�
	if(invincible){ invincibleCnt++; } // ���G���Ԃ��J�E���g
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
	// �v���C���[�Ƀ_���[�W
	hitPoint--;
	// player��F�ɐݒ�
	object->color = { 0,0,1 };
	// ���G�t�^
	invincible = true;
	// ��Ԃɂ���Č��ʂ�t�^
	SetGameObjAbility(skillName);
	StateControl();
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
		stateAcc = 1.5f;
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
	else if (skillName == "speeddown")
	{
		state = State::speedDown;
	}
}
