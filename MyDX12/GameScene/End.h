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
	// パターン１
	Sprite* result = nullptr; // リザルトの画像
	Math::Vector2 resultPos{ 1280 / 2, -100 }; // リザルトの座標
	const float resultLastY = 100.0f; // リザルトの最終座標

	// パターン２
	//Sprite* results[6]; // リザルトの画像
	//Math::Vector2 resultSize[6]; // リザルトのサイズ
	//const Math::Vector2 resultLastSize{ 50.0f, 100.0f }; // リザルトの最終サイズ
	//const Math::Vector2 shrinkValue{ 25.0f, 50.0f };
	//ShrinkChar sChar = ShrinkChar::R; // 縮小している文字
	//float alpha = 0.0f;

	Sprite* medal[3]; // メダルの画像
	Math::Vector2 medalPos{ 1280 / 2, 400 }; // メダルの座標
	bool medalDrawFlag = false; // 描画フラグ
	Math::Vector2 medalSize{ 460.0f, 460.0f }; // メダルのサイズ
	const Math::Vector2 medalLastSize{ 230.0f, 230.0f }; // メダルの最終サイズ

	Sprite* medalBase = nullptr; // メダル台
	Math::Vector2 medalBasePos{ medalPos }; // メダル台の座標
};