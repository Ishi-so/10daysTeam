#include "SceneState.h"
#include "GameScene.h"
#include "../Game/Player.h"
#include "../Camera/DebugCamera.h"

GameScene* SceneState::p_game_scene = nullptr;
Player* SceneState::p_player = nullptr;
DebugCamera* SceneState::p_camera = nullptr;

float SceneState::score = 10;
float SceneState::time = 0;

void SceneState::ShakeCamera()
{
	// Playerが何かと当たったら
	if (p_player->GetHitFlag())
	{
		shakeFlag = true;
	}

	// カウントが指定したフレームまで来たら止める
	if (shakeCnt >= SHAKE_MAX_TIME)
	{
		// 0クリア
		shakePos = { 0,0,0 };
		shakeCnt = 0;
		shakeFlag = false; // シェイクをやめる
	}

	// シェイク中
	if (shakeFlag)
	{
		// 偶数の時揺れる
		if (shakeCnt % 2 == 0)
		{
			shakePos.x = SHAKE_RAND_MIN + (int)(rand() * (SHAKE_RAND_MAX - SHAKE_RAND_MIN + 1) / (1 + RAND_MAX));
			shakePos.y = SHAKE_RAND_MIN + (int)(rand() * (SHAKE_RAND_MAX - SHAKE_RAND_MIN + 1) / (1 + RAND_MAX));
		}
		shakeCnt++;
	}
}
