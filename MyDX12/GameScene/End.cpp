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
	Messenger::GetInstance()->AddPrintOut("エンドシーンです！");
}

void End::Update()
{
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Title());
	}
}

void End::Draw()
{
}