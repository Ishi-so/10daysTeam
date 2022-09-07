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
	// 生成
	Player* player = new Player();

	// 初期化
	player->Initialize();

	return player;
}

void Player::Initialize()
{
	// オブジェクトの生成設定
	object = Object3D::Create(Model::CreateFromOBJ("sphere"));
	object->position = position;
}

void Player::Update()
{
	// objectの更新
	object->position = position; // 座標の設定
	object->Update();
}

void Player::Draw()
{
	// objectの描画
	object->Draw();
}
