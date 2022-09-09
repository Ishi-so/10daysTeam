#include "Load.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Play.h"
#include "../Input/KeyInput.h"
using namespace XIIlib;

Load::Load()
{
}

Load::~Load()
{
	
}

void Load::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("���[�h�V�[���ł��I");
}

void Load::Update()
{
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Play());
	}
}

void Load::Draw()
{
}
