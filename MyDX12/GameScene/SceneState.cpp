#include "SceneState.h"
#include "GameScene.h"
#include "../Game/Player.h"

GameScene* SceneState::p_game_scene = nullptr;
Player* SceneState::p_player = nullptr;
float SceneState::score = 10;
float SceneState::time = 0;