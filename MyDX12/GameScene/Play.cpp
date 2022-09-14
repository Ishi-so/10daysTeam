#include "Play.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Menu.h"
#include "End.h"
#include "../Input/KeyInput.h"
#include "../Game/Player.h"
#include "../Game/ObjectManager.h"
#include "../2D/Sprite.h"
#include "../Tool/DigitalNumberText.h"

using namespace XIIlib;

Play::Play()
{
}

Play::~Play()
{
}

void Play::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("プレイシーンです！");
	operation = Sprite::Create(16, { 200, 720 / 2 });
	operation->SetAnchorPoint(center);

	for (int i = 0; i < _countof(life); i++) {
		life[i] = Sprite::Create(18, { (float)0 + 130 * i, 0 });
	}

	timeTex = Sprite::Create(19, { 1280 - 300, 0 });
}

void Play::Update()
{
	p_player->Update();
	ObjectManager::GetInstance()->Update();
	if (KeyInput::GetInstance()->Trigger(DIK_R)) {
		Messenger::GetInstance()->AddPrintOut("R");
		p_player->InitPlayerData();
	}
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Menu());
	}

	if (KeyInput::GetInstance()->Trigger(DIK_RETURN)) {
		p_game_scene->ChangeState(new End());
	}

	/*if (KeyInput::GetInstance()->Trigger(DIK_1)) {
		time = 19.0f;
	}
	else if (KeyInput::GetInstance()->Trigger(DIK_2)) {
		time = 39.0f;
	}
	else if (KeyInput::GetInstance()->Trigger(DIK_3)) {
		time = 59.0f;
	}*/

	timeF++;

	if (timeF == 60) {
		timeS++;
		timeF = 0;
	}

	DigitalNumberText::GetInstance()->Print(timeS, 1050, 33);

	time = timeS;
}

void Play::Draw()
{
	p_player->Draw();
	ObjectManager::GetInstance()->Draw();
}

void Play::DrawTexture()
{
	operation->Draw();

	for (int i = 0; i < _countof(life); i++) {
		if (i + 1 >= i + 1) {
			life[i]->Draw();
		}
	}

	timeTex->Draw();
}
