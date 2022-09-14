#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"
#include <string>

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
	};

	// プレイヤーの情報
	struct Info 
	{
		float radius = 0.5f;
		float edge = 0.0f;
	};
	struct Info info; // 情報の変数

private: // メンバ定数
	const int INVINCIBLE_TIME = 100.0f; // 無敵時間
	const float SIZE = 3.0f; // 階層判別判定のサイズ
	const float MAX_AREA = 10.4f; // 横幅の上限
	const float ADD_ACC = 0.05f; // 移動加算用
	const float SUB_ACC = 0.02f; // not移動加速用
	const float GRAVITY = -0.1f; // 落下
	const float MAX_GRAVITY = -0.3f; // 最高落下速度

public: // メンバ関数
	// 汎用関数
	Player() = default; // コンストラクタ
	~Player(); // デストラクタ
	static Player* Create(Math::Vector3 createPos); // 生成関数
	void Initialize(Math::Vector3 createPos); // 初期化
	void Update(); // 毎フレーム処理
	void Draw(); // 描画
	void HitUpdate(std::string& skillName); // 当たっとき専用処理
	void InitPlayerData();

	// ---- Setter Getter ---- 
	/* Setter */
	void SetHitFlag(bool flag) { hitFlag = flag; }// hitFlagを設定

	/* Getter */
	Math::Vector3 GetPosition()const { return position; } // 座標を取得
	Math::Sphere GetCollision()const { return collSphere; } // 当たり判定を取得
	bool GetDeathFlag()const { return deathFlag; } // 死亡フラグの取得
	std::vector<unsigned int> GetStratumData()const { return stratumData; } // 階層データを取得
	Math::Vector3 GetDirection()const { return direction; } // 方向を取得
	bool GetGoalFlag() const { return goalFlag; } // ゴールフラグを取得
	bool GetHitFlag() const { return hitFlag; } // ヒットフラグを取得

private: // 固有メンバ関数(private)
	// 固有関数
	void SetCollsion(); // 当たり判定を設定
	void StateControl(); // 状態によってバフデバフを付与
	void SetGameObjAbility(std::string& skillName); // skill名でstateを設定

private: // メンバ変数
	// Playerデータ
	Object3D* object = nullptr; // ゲームオブジェクト
	State state = State::none; // プレイヤーの状態
	int hitPoint = 3; // 体力(仮)
	Math::Vector3 position; // 座標
	Math::Vector3 velocity; // 速度
	Math::Vector3 acc; // 加速度
	Math::Vector3 prevPos; // 1f前の座標
	Math::Vector3 direction; // 移動方向
	bool deathFlag = false; // 死亡フラグ
	std::vector<unsigned int> stratumData; // 階層データ
	bool goalFlag = false;

	// プレイヤーの状態系
	float stateAcc = 1.0f; // 状態によって決まる加減速値倍率
	bool invincible = false; // 無敵フラグ
	int invincibleCnt = 0; // 無敵時間のカウント

	// 当たり判定確認用
	Math::Sphere collSphere; // 当たり判定用　球
	bool hitFlag = false; // 当たり判定フラグ
};

