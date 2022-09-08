#include "Player.h"
#include "../Struct/Math/Vector3.h"
#include "../3D/Object3D.h"
#include "../Input/KeyInput.h"

using namespace XIIlib;
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
	// ---- 移動 ----
	// キーボード操作
	if (KeyInput::GetInstance()->Push(DIK_D)) // 右移動
	{
		acc.x = 0.02f;
	}
	else if (KeyInput::GetInstance()->Push(DIK_A)) // 左移動
	{
		acc.x = -0.02f;
	}
	else // 移動していない
	{
		// 少しづつ停止
		acc.x = 0.0f;
		if (velocity.x > 0) {
			velocity.x += -0.02f;
		}
		else if (velocity.x < 0)
		{
			velocity.x += 0.02f;
		}
	}
	// 落下
	//acc.y -= 0.0001f;

	// 左右加速度制御
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
	
	// 落下加速度制御
	if (velocity.y > 0.001f)
	{
		velocity.y = 0.001f;
	}
	
	// ---- 座標の更新 ----
	velocity += acc;
	position += velocity;

	// ---- objectの更新 ----
	object->position = position; // 座標の設定
	object->Update();
}

void Player::Draw()
{
	// objectの描画
	object->Draw();
}
