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
	// 生成
	Player* player = new Player();

	// 初期化
	player->Initialize(createPos);

	return player;
}

void Player::Initialize(Math::Vector3 createPos)
{
	// ---- 座標の設定 ----
	position = createPos;

	// ---- オブジェクトの生成設定 ----
	// プレイヤーオブジェクトモデル
	object = Object3D::Create(Model::CreateFromOBJ("sphere"));
	object->position = position;
	info.radius = object->scale.x / 2;
	info.edge = object->position.x + info.radius; // プレイヤーオブジェクトの端っこ

	// ---- 当たり判定を付随させる ----
	SetCollsion();

	// ---- 階層データの初期化 ----
	stratumData.resize(2);
	stratumData = Stratum::GetStratumData(position.y, SIZE);
}

void Player::Update()
{
	// 状態をリセット
	//state = State::none;
	// 現在の座標を保存
	prevPos = position;

	// ---- 移動 ----
	// キーボード操作
	if (KeyInput::GetInstance()->Push(DIK_D)) // 右移動
	{
		acc.x = ADD_ACC;
	}
	else if (KeyInput::GetInstance()->Push(DIK_A)) // 左移動
	{
		acc.x = -ADD_ACC;
	}
	else // 移動していない
	{
		// 少しづつ停止
		acc.x = 0.0f;
		if (velocity.x > 0) {
			velocity.x += -SUB_ACC;
		}
		else if (velocity.x < 0)
		{
			velocity.x += SUB_ACC;
		}
	}

	// テスト用
	//if (KeyInput::GetInstance()->Push(DIK_W)) // 右移動
	//{
	//	position.y += 0.5f;
	//}
	//else if (KeyInput::GetInstance()->Push(DIK_S)) // 左移動
	//{
	//	position.y -= 0.5f;
	//}

	// 落下
	acc.y = GRAVITY;

	// 左右加速度制御(0.1f以内に調整)
	if (abs(velocity.x) > 0.1f) // veloが0.1f以上になれば
	{
		if (velocity.x > 0) // veloが+なら
		{
			velocity.x += 0.1f - velocity.x;
		}
		else if (velocity.x < 0) // veloが-なら
		{
			velocity.x += -0.1f - velocity.x;
		}
	}
	
	// 落下加速度制御
	if (velocity.y < MAX_GRAVITY)
	{
		velocity.y = MAX_GRAVITY;
	}
	
	// ---- 座標の更新 ----
	velocity += acc; 
	position.y += velocity.y * stateAcc; // 加算されたveloと状態加速によって座標を更新
	position.x += velocity.x;

	// 横壁の範囲上限
	if (MAX_AREA <= position.x + info.radius)
	{
		// 押し出し
		position.x = MAX_AREA - info.radius;
	}
	else if (position.x - info.radius <= -MAX_AREA)
	{
		// 押し出し
		position.x = -MAX_AREA + info.radius;
	}
	
	object->position = position; // 座標の設定
	direction = position - prevPos; // 方向を設定

	// ---- 当たり判定を付随 ----
	SetCollsion();

	// ---- 当たり判定 ----
	// ObjectManagerに記載
	
	// ---- プレイヤー状態更新 ----
	// 状態によって効果を付与
	StateControl();

	// 体力が0未満になったら
	if (hitPoint <= 0)
	{
		InitPlayerData();
		object->color = { 1,0,1 };
		deathFlag = true;
	}

	// ---- 最終的な座標を設定　----
	object->position = position; // 改めて設定(当たった時に押し出す処理を考慮)

	// 階層データの更新
	stratumData = Stratum::GetStratumData(position.y, SIZE);

	// ---- objectの更新 ----
	object->Update();

	// ---- カウント ----
	// 無敵状態かつ、カウントが最大までいったら
	if (invincibleCnt >= INVINCIBLE_TIME && invincible) 
	{
		// ヒットフラグを立てる
		hitFlag = false;
		// 無敵解除
		invincible = false;
		// カウントを0クリア
		invincibleCnt = 0;
		// playerの色を戻す
		//object->color = { 1,1,1 };
	}

	// 無敵状態なら
	if(invincible)
	{
		if (invincibleCnt % 5 == 0)
		{
			if (object->alpha >= 1.0f) { object->alpha = 0.0f; }
			else if (object->alpha <= 0.0f) { object->alpha = 1.0f; }
		}
		
		// 無敵時間をカウント
		invincibleCnt++; 
	} 
}

void Player::Draw()
{
	// objectの描画
	object->Draw();
}

void Player::HitUpdate(std::string& skillName)
{
	// ゴールブロックと当たったらフラグを変えてリターン
	if (skillName == "Goal") { 
		goalFlag = true; 
		return;
	}

	// 無敵状態であれば即リターン
	if (invincible)return;
	// 状態によって効果を付与
	SetGameObjAbility(skillName);
	StateControl();
}

void Player::InitPlayerData()
{
	// 基本情報
	state = State::none; // プレイヤーの状態
	hitPoint = 3; // 体力(仮)
	position = {}; // 座標
	velocity = {}; // 速度
	acc = {}; // 加速度
	prevPos = {}; // 1f前の座標
	direction = {}; // 移動方向
	deathFlag = false; // 死亡フラグ
	stratumData = {0,0}; // 階層データ
	goalFlag = false;

	// プレイヤーの状態系
	stateAcc = 1.0f; // 状態によって決まる加減速値倍率
	invincible = false; // 無敵フラグ
	invincibleCnt = 0; // 無敵時間のカウント

	// 当たり判定確認用
	hitFlag = false; // 当たり判定フラグ

	// playerを青色に設定
	object->color = { 1,1,1 };
}

void Player::SetCollsion()
{
	// 当たり判定を設定
	collSphere.pos = Math::Vector4(object->position.x, object->position.y, object->position.z, 1.0f);
	collSphere.r = object->scale.x;
}

void Player::StateControl()
{
	// 状態によってそれぞれの効果を付与
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
	// 名前によって状態変化
	if (skillName == "speedup")
	{
		state = State::speedUp;
	}
	else if (skillName == "speeddown") // block
	{
		state = State::speedDown;
		// ヒットフラグを立てる
		hitFlag = true;
		// プレイヤーにダメージ
		hitPoint--;
		// playerを青色に設定
		//object->color = { 0,0,1 };
		// 無敵付与
		invincible = true;
	}
}
