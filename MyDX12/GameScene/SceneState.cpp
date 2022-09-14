#include "SceneState.h"
#include "GameScene.h"
#include "../Game/Player.h"
#include "../Camera/DebugCamera.h"

GameScene* SceneState::p_game_scene = nullptr;
Player* SceneState::p_player = nullptr;
DebugCamera* SceneState::p_camera = nullptr;

float SceneState::score = 10;
float SceneState::time = 0;