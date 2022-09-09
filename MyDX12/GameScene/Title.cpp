#include "Title.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Select.h"
#include "../Input/KeyInput.h"
using namespace XIIlib;

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("�^�C�g���V�[���ł��I");
}

void Title::Update()
{
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Select());
	}
}

void Title::Draw()
{
}
