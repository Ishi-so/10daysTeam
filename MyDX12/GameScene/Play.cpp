#include "Play.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Menu.h"
#include "End.h"
#include "../Input/KeyInput.h"
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
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Menu());
	}

	if (KeyInput::GetInstance()->Trigger(DIK_RETURN)) {
		p_game_scene->ChangeState(new End());
	}

	if (KeyInput::GetInstance()->Trigger(DIK_1)) {
		time = 19.0f;
	}
	else if (KeyInput::GetInstance()->Trigger(DIK_2)) {
		time = 39.0f;
	}
	else if (KeyInput::GetInstance()->Trigger(DIK_3)) {
		time = 59.0f;
	}
}

void Play::Draw()
{
}