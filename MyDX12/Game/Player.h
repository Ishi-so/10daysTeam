#pragma once
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

// 前方宣言
class Object3D;

// プレイヤークラス
class Player
{
private: // メンバ定数
public: // メンバ関数
	Player() = default; // コンストラクタ
	~Player(); // デストラクタ
	static Player* Create(); // 生成関数
	void Initialize(); // 初期化
	void Update(); // 毎フレーム処理
	void Draw(); // 描画

	void SetCollsion(); // 当たり判定を設定
private: // メンバ変数
	Object3D* object = nullptr; // ゲームオブジェクト
	int hitPoint = 3; // 体力(仮)
	Math::Vector3 position; // 座標
	Math::Vector3 velocity; // 速度
	Math::Vector3 acc; // 加速度

	// 当たり判定確認用
	Object3D* boxObj = nullptr;
	Math::Sphere collSphere;
	Math::AABB collBox;
};

