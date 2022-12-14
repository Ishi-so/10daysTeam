#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"
#include "../Struct/TypeCollision.h"

class Object3D;

class GameObj {
protected:
	std::string id;				// クラスネーム
	Math::Vector3 pos;			// 座標
	Math::Vector3 scale;		// スケール
	Math::Vector3 color;		// カラー
	bool isActive = true;		// 存在の有無用フラグ
	Math::AABB collisionData;	// 判定データ
	unsigned int stratum = 0;	// 階層
	bool hitFlag = false;       // 当たっているかフラグ
	std::string ability;        // 効果

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
	unsigned int GetStratum()const { return stratum; }			// 階層値の取得
	std::string GetAbility()const { return ability; }			// スキルの取得
	 
	//・・・Set・・・
	void SetPos(const Math::Vector3& c_pos) { pos = c_pos; }		// 座標の設定
	void SetScale(const Math::Vector3& c_scale) { scale = c_scale; }// スケールの設定
	void SetColor(const Math::Vector3& c_color) { color = c_color; }// カラーの設定
	void SetStratum(unsigned int _stratum) { stratum = _stratum; }	// 階層の設定
	void SetActive(bool _active){isActive = _active;}				// 生存フラグの設定
};