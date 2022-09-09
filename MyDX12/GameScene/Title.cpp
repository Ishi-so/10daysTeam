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
	Messenger::GetInstance()->AddPrintOut("タイトルシーンです！");
}

void Title::Update()
{
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Select());
	}
}

void Title::Draw()
{
}
