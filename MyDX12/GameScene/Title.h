#pragma once
#include "SceneState.h"
#include "../Struct/Math/Vector2.h"
#include <vector>

class Sprite;

class Title : public SceneState {
public:
	Title();	// コンストラクタ
	~Title();	// デストラクタ

	void Initialize()override;// 初期化
	void Update()override;// 更新
	void Draw()override;// 描画
	void DrawTexture()override;

private:// 変数

	Sprite* title = nullptr; // タイトル
	Sprite* pushSpace = nullptr; // プッシュスペース
	const Math::Vector2 center{ 0.5f, 0.5f }; // 中心設定用
	bool setOffFlag = false;
};