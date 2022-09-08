#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

class Object3D;

class GameObj {
protected:
	std::string id;			// クラスネーム
	Math::Vector3 pos;		// 座標
	Math::Vector3 scale;	// スケール
	bool isActive = true;	// 存在の有無用フラグ
	Math::AABB collisionData;

	Object3D* obj = nullptr;// オブジェクトデータ

public:
	GameObj() = default;
	virtual ~GameObj() {};

	virtual void Init() = 0;	// 初期化
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

	// 共通関数
	//・・・Get・・・
	std::string GetID()const { return id; }						// クラスネーム取得
	Math::Vector3 GetPos()const { return pos; }					// 座標の取得
	bool GetIsActive()const { return isActive; }				// 存在しているかどうか
	Math::AABB GetCollisionData()const { return collisionData; }// AABBデータの取得

	// ・・・Set・・・
	void SetPos(const Math::Vector3& c_pos) { pos = c_pos; }	// 座標の設定
	void SetScale(const Math::Vector3& c_scale) { scale = c_scale; }
};