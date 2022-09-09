#include "Menu.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Play.h"
#include "../Input/KeyInput.h"
using namespace XIIlib;

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("メニューシーンです！");
}

void Menu::Update()
{
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Play());
	}
}

void Menu::Draw()
{
}