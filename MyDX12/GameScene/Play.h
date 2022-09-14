#pragma once
#include "SceneState.h"
#include "../Struct/Math/Vector2.h"

class Sprite;

class Play : public SceneState {
public:
	Play();	// コンストラクタ
	~Play();	// デストラクタ

	void Initialize()override;// 初期化
	void Update()override;// 更新
	void Draw()override;// 描画
	void DrawTexture()override;

private:// 変数
	Sprite* operation = nullptr; // 操作説明
	const Math::Vector2 center{ 0.5f, 0.5f }; // 中心設定用
	Sprite* life[3];
	Sprite* timeTex = nullptr;
	int timeM = 0;
	int timeS = 0;
	int timeF = 0;
};
