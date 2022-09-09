#include "End.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Title.h"
#include "../Input/KeyInput.h"
using namespace XIIlib;

End::End()
{
}

End::~End()
{
}

void End::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("�G���h�V�[���ł��I");
}

void End::Update()
{
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Title());
	}
}

void End::Draw()
{
}