#pragma once
#include "SceneState.h"
#include "../Struct/Math/Vector2.h"

class Sprite;

enum class ShrinkChar {
	R,
	E,
	S,
	U,
	L,
	T,
	M,
};

class End : public SceneState {
public:
	End();	// コンストラクタ
	~End();	// デストラクタ

	void Initialize()override;// 初期化
	void Update()override;// 更新
	void Draw()override;// 描画

	void DrawTexture()override; // テクスチャ描画

private:// 変数
	Sprite* result = nullptr; // リザルトの画像
	Math::Vector2 resultPos{ 1280 / 2, -100 }; // リザルトの座標
	const float resultLastY = 100.0f; // リザルトの最終座標

	Sprite* medal[3]; // メダルの画像
	Math::Vector2 medalPos{ 1280 / 2, 400 }; // メダルの座標
	bool medalDrawFlag = false; // 描画フラグ
	Math::Vector2 medalSize{ 460.0f, 460.0f }; // メダルのサイズ
	const Math::Vector2 medalLastSize{ 230.0f, 230.0f }; // メダルの最終サイズ

	const Math::Vector2 center{ 0.5f, 0.5f }; // 中心設定用

	Sprite* medalBase = nullptr; // メダル台
	Math::Vector2 medalBasePos{ medalPos }; // メダル台の座標

	Sprite* returnTitle = nullptr; //
	Sprite* returnSelect = nullptr; //

	Sprite* titleCursor = nullptr; //
	Sprite* selectCursor = nullptr; //

	const Math::Vector2 titlePos{ 50, 610 };
	const Math::Vector2 selectpos{ 600, 610 };
	bool pushLeftFlag = true; // 左キーを押しているか
};