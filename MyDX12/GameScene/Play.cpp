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
	Messenger::GetInstance()->AddPrintOut("�v���C�V�[���ł��I");
}

void Play::Update()
{
	// ��������؂�ւ�
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