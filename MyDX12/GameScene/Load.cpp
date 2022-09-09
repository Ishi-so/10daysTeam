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
	Messenger::GetInstance()->AddPrintOut("ロードシーンです！");
}

void Load::Update()
{
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Play());
	}
}

void Load::Draw()
{
}
