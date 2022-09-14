#pragma once
#include "../Tool/Messenger.h"
#include "../Struct/Math/Vector3.h"

class GameScene;
class Player;
class DebugCamera;

namespace XIIlib
{
	class Audio;
}

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

protected: //　共通関数
	void ShakeCamera(); // カメラシェイク

public: // Setter関数
	void SetGameScene(GameScene* p_game_scene) { this->p_game_scene = p_game_scene; }
	void SetPlayer(Player* p_player) { this->p_player = p_player; }
	void SetCamera(DebugCamera* p_camera) { this->p_camera = p_camera; };
	void SetAudio(XIIlib::Audio* p_audio) { this->p_audio = p_audio; }

public: // Getter関数

protected: // 静的メンバ変数
	static GameScene* p_game_scene;
	static Player* p_player;
	static DebugCamera* p_camera;
	static XIIlib::Audio* p_audio;
	static float score;
	static float time;
	static float zAxis;

	const float SHAKE_RAND_MIN = -0.3f;
	const float SHAKE_RAND_MAX = 0.3f;
	const int SHAKE_MAX_TIME = 20.0f;
	int shakeCnt = 0;
	Math::Vector3 shakePos;
	bool shakeFlag = false;
};