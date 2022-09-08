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
	// acc.y -= 0.0001f;

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
	position += velocity * stateAcc;
	object->position = position; // 座標の設定

	// ---- 当たり判定を付随 ----
	SetCollsion();

	// ---- 当たり判定 ----
	if (Math::HitCheck_AABB_Sphere(collBox, collSphere) && !invincible) // box と sphereが当たったら
	{
		// 当たっていない状態だったら
		if (!hitFlag)
		{
			// フラグをtrue
			hitFlag = true;
			// boxを赤色に設定
			boxObj->color = { 1,0,0 };
			// playerを青色に設定
			object->color = {0,0,1};
			// 無敵付与
			state = State::invincible;
		}
	}
	else 
	{
		//フラグをfalse
		hitFlag = false;
		// boxの色を戻す
		boxObj->color = { 1,1,1 };
	}

	// 状態によって効果を付与
	SetSkill();

	// ---- 最終的な座標を設定　----
	object->position = position; // 改めて設定(当たった時に押し出す処理を考慮)

	// ---- objectの更新 ----
	object->Update();
	boxObj->Update();

	// ---- カウンター ----
	// 無敵状態かつ、カウントが最大までいったら
	if (invincibleCnt >= INVINCIBLE_TIME && invincible) 
	{
		// 無敵解除
		invincible = false;
		// カウントを0クリア
		invincibleCnt = 0;
		// playerの色を戻す
		object->color = { 1,1,1 };
		// 状態を戻す
		state = State::none;
	}

	// 無敵状態なら
	if(invincible){ invincibleCnt++; } // 無敵時間をカウント
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

void Player::SetSkill()
{
	// 状態によってそれぞれの効果を付与
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
		hitFlag = false;
	}
	else
	{
		stateAcc = 1.0f;
	}
}
