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

	boxObj = Object3D::Create(Model::CreateFromOBJ("box_v000"));
	boxObj->position = {5.0f,0.0f,0.0f};

	// 当たり判定を付随させる
	SetCollsion();
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
	object->position = position; // 座標の設定

	// ---- 当たり判定を付随 ----
	SetCollsion();

	// ---- 当たり判定 ----
	if (Math::HitCheck_AABB_Sphere(collBox, collSphere)) // box と sphereが当たったら
	{
		// 赤色
		boxObj->color = {1,0,0};
	}

	// ---- 最終的な座標を設定　----
	object->position = position; // 改めて設定(当たった時に押し出す処理を考慮)

	// ---- objectの更新 ----
	object->Update();
	boxObj->Update();
}

void Player::Draw()
{
	// objectの描画
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
