#include "Select.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Load.h"
#include "../Input/KeyInput.h"
using namespace XIIlib;

Select::Select()
{
}

Select::~Select()
{
}

void Select::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("�Z���N�g�V�[���ł��I");
}

void Select::Update()
{
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Load());
	}
}

void Select::Draw()
{
}