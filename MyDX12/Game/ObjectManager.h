#pragma once
#include <memory>
#include <vector>
#include "GameObj.h"

// オブジェクトの管理クラス
class ObjectManager {
private:
	ObjectManager();
	~ObjectManager();

	void DeadUnit();// 存在していないオブジェクトを消す
	
	std::vector<std::shared_ptr<GameObj>> mObjs;	// 管理オブジェクトコンテナ
	std::vector<std::shared_ptr<GameObj>> mAddObjs;// 追加物格納コンテナ
public:
	ObjectManager(const ObjectManager& obj) = delete;
	ObjectManager& operator = (const ObjectManager& obj) = delete;

	static ObjectManager* GetInstance();

	void Initialize(); // 初期化

	void Update(); // 更新

	void Draw(); // 描画

	void AddObject(const std::shared_ptr<GameObj>& upObject); // ユニットの追加

	void AllDestroy();// 全てを削除
};