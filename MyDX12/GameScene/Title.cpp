#include "Title.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Select.h"
#include "Play.h"
#include "../Input/KeyInput.h"
#include "../3D/Object3D.h"
#include "../Game/ModelLoader.h"
#include "../Game/Common.h"
#include "../2D/Sprite.h"
#include "../Struct/Math/Vector2.h"
#include "../Game/ObjectManager.h"
#include "../Game/Player.h"

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
	Messenger::GetInstance()->AddPrintOut("タイトルシーンです！");
}

void Title::Update()
{
	p_player->Update();
	ObjectManager::GetInstance()->Update();
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_player->SetStart();
		p_game_scene->ChangeState(new Play());
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