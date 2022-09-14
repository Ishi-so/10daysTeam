﻿#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

class DebugCamera;
class LightGroup;
class Circle;
class Tessellation;
class SceneState;
class Player; // 仮
class PlayerEffectManager;

class GameScene {
private:// 静的メンバ
	static const int debugTextTexNumber = 0;
	static const int debugJISTextTexNumber = 1;
private: // メンバ定数
	const float SHAKE_RAND_MIN = -3.0f;
	const float SHAKE_RAND_MAX = 3.0f;
	const int SHAKE_MAX_TIME = 120.0f;

private:// メンバ
	LightGroup* lightGroup = nullptr;
	DebugCamera* d_camera = nullptr;
	SceneState* state = nullptr;// Scene
	
	// カメラ系
	Math::Vector3 cameraPos;
	float cameRad = 0.0f;
	int shakeCnt = 0;
	Math::Vector3 shakePos;
	bool shakeFlag = false;

	Circle* circle = nullptr;

	// Game系
	Player* m_player = nullptr;// プレイヤークラス
	std::vector<std::vector<int>>mapData = {};
	PlayerEffectManager* playerEffects = nullptr;
	int playerDistTimer;

public:
	static GameScene* Create();

	GameScene();
	~GameScene();

	bool Initialize();// 初期化

	void Update();// 更新

	void Draw();// 描画

	void ChangeState(SceneState* different_state);// シーンの切り替え
};