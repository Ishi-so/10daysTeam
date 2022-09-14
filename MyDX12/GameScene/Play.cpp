#include "Play.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Menu.h"
#include "End.h"
#include "../Input/KeyInput.h"
#include "../Game/Player.h"

using namespace XIIlib;

Play::Play()
{
}

Play::~Play()
{
}

void Play::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("プレイシーンです！");
}

void Play::Update()
{
	if (KeyInput::GetInstance()->Trigger(DIK_R)) {
		Messenger::GetInstance()->AddPrintOut("R");
		p_player->InitPlayerData();
	}
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Menu());
	}

	if (KeyInput::GetInstance()->Trigger(DIK_RETURN)) {
		p_game_scene->ChangeState(new End());
	}
}

void Play::Draw()
{
}