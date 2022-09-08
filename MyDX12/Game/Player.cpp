#include "Player.h"
#include "../Struct/Math/Vector3.h"
#include "../3D/Object3D.h"
#include "../Input/KeyInput.h"

using namespace XIIlib;
/*Player::Player()
{}*/

Player::~Player()
{
	delete boxObj;
	delete object;
}

Player* Player::Create()
{
	// ����
	Player* player = new Player();

	// ������
	player->Initialize();

	return player;
}

void Player::Initialize()
{
	// �I�u�W�F�N�g�̐����ݒ�
	object = Object3D::Create(Model::CreateFromOBJ("sphere"));
	object->position = position;

	boxObj = Object3D::Create(Model::CreateFromOBJ("box_v000"));
	boxObj->position = {5.0f,0.0f,0.0f};

	// �����蔻���t��������
	SetCollsion();
}

void Player::Update()
{
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
	//acc.y -= 0.0001f;

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
	if (velocity.y > 0.001f)
	{
		velocity.y = 0.001f;
	}
	
	// ---- ���W�̍X�V ----
	velocity += acc;
	position += velocity;
	object->position = position; // ���W�̐ݒ�

	// ---- �����蔻���t�� ----
	SetCollsion();

	// ---- �����蔻�� ----
	if (Math::HitCheck_AABB_Sphere(collBox, collSphere)) // box �� sphere������������
	{
		// �ԐF
		boxObj->color = {1,0,0};
	}

	// ---- �ŏI�I�ȍ��W��ݒ�@----
	object->position = position; // ���߂Đݒ�(�����������ɉ����o���������l��)

	// ---- object�̍X�V ----
	object->Update();
	boxObj->Update();
}

void Player::Draw()
{
	// object�̕`��
	object->Draw();
	boxObj->Draw();
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
