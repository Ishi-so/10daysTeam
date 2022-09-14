﻿#pragma once
#include "../Tool/Messenger.h"

class GameScene;
class Player;
class DebugCamera;

class SceneState {
protected:
	SceneState() {}
public:
	// コピー禁止
	SceneState(const SceneState&) = delete;
	SceneState& operator=(const SceneState&) = delete;

	// 仮想デストラクタ
	virtual ~SceneState() = default;
public: // 継承
	virtual void Initialize() = 0;// 初期化
	virtual void Update() = 0;//　更新
	virtual void Draw() = 0;// 描画
	virtual void DrawTexture(){}
	virtual void BackTexture(){}

public: // Setter関数
	void SetGameScene(GameScene* p_game_scene) { this->p_game_scene = p_game_scene; }
	void SetPlayer(Player* p_player) { this->p_player = p_player; }
	void SetCamera(DebugCamera* p_camera) { this->p_camera = p_camera; }

public: // Getter関数

protected: // 静的メンバ変数
	static GameScene* p_game_scene;
	static Player* p_player;
	static DebugCamera* p_camera;
	static float score;
	static float time;
};