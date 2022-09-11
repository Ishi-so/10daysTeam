#pragma once
#include <memory>
#include <vector>
#include "GameObj.h"

class Player;// プレイヤー

// オブジェクトの管理クラス
class ObjectManager {
private:
	ObjectManager();
	~ObjectManager();

	void DeadObject();// 存在していないオブジェクトを消す
	
	std::vector<std::shared_ptr<GameObj>> mObjs;	// 管理オブジェクトコンテナ
	std::vector<std::shared_ptr<GameObj>> mAddObjs;// 追加物格納コンテナ

	Player* pPlayer = nullptr;
public:
	ObjectManager(const ObjectManager& obj) = delete;
	ObjectManager& operator = (const ObjectManager& obj) = delete;

	static ObjectManager* GetInstance();

	void Initialize(); // 初期化

	void Update(); // 更新

	void Draw(); // 描画

	void AddObject(const std::shared_ptr<GameObj>& upObject); // ユニットの追加

	void AllDestroy();// 全てを削除

	void SetPlayer(Player* p_player) { pPlayer = p_player; }// プレイヤーのデータをコピーする

	void HitCheck();// 判定処理

	void PropValueCheck(const std::shared_ptr<GameObj>& obj,const int stratum);
};