#pragma once
#include <string>
#include "../Struct/Math/Vector3.h"

class Object3D;

class GameObj {
protected:
	std::string id;			// クラスネーム
	Math::Vector3 pos;		// 座標
	bool isActive = true;	// 存在の有無用フラグ

	Object3D* obj = nullptr;// オブジェクトデータ

public:
	GameObj() = default;
	virtual ~GameObj() {};

	virtual void Init() = 0;	// 初期化
	virtual void Update() = 0;	// 更新
	virtual void Draw() = 0;	// 描画

	// 共通関数
	std::string GetID()const { return id; }		// クラスネーム取得
	Math::Vector3 GetPos()const { return pos; }	// 座標の取得
	bool GetIsActive()const { return isActive; }// 存在しているかどうか
};