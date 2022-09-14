#pragma once
#include "SceneState.h"
#include "../Struct/Math/Vector2.h"

class Sprite;

enum class MedalColor{
	GOLD,
	SILVER,
	BRONZE,
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
	Math::Vector2 resultPos{ 1280 / 2, -50 }; // リザルトの座標
	const float resultLastY = 150.0f; // リザルトの最終座標

	Sprite* medal[3]; // メダルの画像
	Math::Vector2 medalPos{ 1280 / 2, 470 }; // メダルの座標
	bool medalDrawFlag = false; // 描画フラグ
	Math::Vector2 medalSize{ 600.0f, 600.0f }; // メダルのサイズ
	const Math::Vector2 medalLastSize{ 300.0f, 300.0f }; // メダルの最終サイズ

	const Math::Vector2 center{ 0.5f, 0.5f }; // 中心設定用

	Sprite* medalBase = nullptr; // メダル台画像
	Math::Vector2 medalBasePos{ medalPos }; // メダル台の座標

	Sprite* returnTitle = nullptr; // タイトルへ画像

	Sprite* titleCursor = nullptr; // タイトル用カーソル

	const Math::Vector2 titlePos{ 1280 / 2, 650 };

	MedalColor medalColor = MedalColor::GOLD; // メダルの色
	const int goldTime = 8 * 3;
	const int silverTime = 10 * 3;
	const int bronzeTime = 12 * 3;

	const float resultTime = time;

	Sprite* timeTex = nullptr;
	bool setBackFlag = false;
};