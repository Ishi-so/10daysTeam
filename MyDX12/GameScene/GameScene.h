#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

class DebugCamera;
class LightGroup;
class Tessellation;
class SceneState;
class Player; // 仮
class PlayerEffectManager;
class Sprite;

class GameScene {
private:// 静的メンバ
	static const int debugTextTexNumber = 0;
	static const int debugJISTextTexNumber = 1;
private: // メンバ定数
	

private:// メンバ
	LightGroup* lightGroup = nullptr;
	DebugCamera* d_camera = nullptr;
	SceneState* state = nullptr;// Scene
	
	// カメラ系
	Math::Vector3 cameraPos;
	float cameRad = 0.0f;
	

	// Game系
	Player* m_player = nullptr;// プレイヤークラス
	std::vector<std::vector<int>>mapData = {};
	PlayerEffectManager* playerEffects = nullptr;
	int playerDistTimer;
	std::vector<Sprite*>bgArray;
	Sprite* frontTex = nullptr;
	float frontAlpha = 0.0f;
	bool onOffFlagFront = false;

public:
	static GameScene* Create();

	GameScene();
	~GameScene();

	bool Initialize();// 初期化

	void Update();// 更新

	void Draw();// 描画

	void ChangeState(SceneState* different_state);// シーンの切り替え

	// オンオフ
	bool FadeInOut(bool flag);

	void CreateStage();
};