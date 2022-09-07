#include "Player.h"
#include "../Struct/Math/Vector3.h"
#include "../3D/Object3D.h"

/*Player::Player()
{}*/

Player::~Player()
{
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
}

void Player::Update()
{
	// object�̍X�V
	object->position = position; // ���W�̐ݒ�
	object->Update();
}

void Player::Draw()
{
	// object�̕`��
	object->Draw();
}
