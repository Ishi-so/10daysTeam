#pragma once
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

// 前方宣言
class Object3D;

// プレイヤークラス
class Player
{
private: // 構造体 or 列挙型 
	// 状態
	enum struct State:int
	{
		none = 0, // なし
		speedDown, // 減速
		speedUp, // 加速
		invincible, // 無敵
	};
private: // メンバ定数
	int INVINCIBLE_TIME = 60.0f; // 無敵時間
public: // メンバ関数
	Player() = default; // コンストラクタ
	~Player(); // デストラクタ
	static Player* Create(Math::Vector3 createPos); // 生成関数
	void Initialize(Math::Vector3 createPos); // 初期化
	void Update(); // 毎フレーム処理
	void Draw(); // 描画

	void SetCollsion(); // 当たり判定を設定
	void SetSkillAbility(); // 状態によってバフデバフを付与

	Math::Sphere GetCollision()const { return collSphere; }
private: // メンバ変数
	Object3D* object = nullptr; // ゲームオブジェクト
	State state = State::none; // プレイヤーの状態
	int hitPoint = 3; // 体力(仮)
	Math::Vector3 position; // 座標
	Math::Vector3 velocity; // 速度
	Math::Vector3 acc; // 加速度
	float stateAcc = 1.0f; // 状態によって決まる加減速値倍率
	bool invincible = false; // 無敵フラグ
	int invincibleCnt = 0; // 無敵時間のカウント

	// 当たり判定確認用
	Object3D* boxObj = nullptr; // box3Dオブジェクト
	Math::Sphere collSphere; // 当たり判定用　球
	Math::AABB collBox; // 当たり判定用　箱
	bool hitFlag = false; // 当たり判定フラグ
};

