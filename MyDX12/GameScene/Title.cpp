#include "Title.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Select.h"
#include "Play.h"
#include "../Input/KeyInput.h"
#include "../3D/Object3D.h"
#include "../Game/Common.h"
#include "../2D/Sprite.h"
#include "../Struct/Math/Vector2.h"
#include "../Game/ObjectManager.h"
#include "../Game/Player.h"
#include "../Camera/DebugCamera.h"

using namespace XIIlib;

Title::Title()
{
}

Title::~Title()
{
}

void Title::Initialize()
{

	title = Sprite::Create(14, { 1280 / 2, 720 / 2 });
	title->SetAnchorPoint(center);
	pushSpace = Sprite::Create(15, { 1280 / 2, 720 - 100 });
	pushSpace->SetAnchorPoint(center);
	//Messenger::GetInstance()->AddPrintOut("タイトルシーンです！");

	time = 0;

	ObjectManager::GetInstance()->AllDestroy();
	p_game_scene->CreateStage();
}

void Title::Update()
{
	p_player->Update();
	ObjectManager::GetInstance()->Update();
	p_camera->SetLookAtRange(shakePos.x, p_player->GetPosition().y + shakePos.y, 0);
	p_camera->SetPosition(shakePos.x, p_player->GetPosition().y + shakePos.y, -40);
	p_camera->_Update();
	if (setOffFlag) {
		
		// 押したら切り替え
		if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
			p_player->SetStart();
			p_game_scene->ChangeState(new Play());
		}
	}
	else
	{
		if (p_game_scene->FadeInOut(false)) {
			setOffFlag = true;
		}
	}
}

void Title::Draw()
{
	p_player->Draw();
	ObjectManager::GetInstance()->Draw();
}

void Title::DrawTexture()
{
	pushSpace->Draw();
	title->Draw();
}