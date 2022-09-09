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
	Messenger::GetInstance()->AddPrintOut("���j���[�V�[���ł��I");
}

void Menu::Update()
{
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Play());
	}
}

void Menu::Draw()
{
}