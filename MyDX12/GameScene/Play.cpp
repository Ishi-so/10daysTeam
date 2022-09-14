#include "Play.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Title.h"
#include "Menu.h"
#include "End.h"
#include "../Input/KeyInput.h"
#include "../Game/Player.h"
#include "../Game/ObjectManager.h"
#include "../2D/Sprite.h"
#include "../Tool/DigitalNumberText.h"
#include "../Camera/DebugCamera.h"

using namespace XIIlib;

Play::Play()
{
}

Play::~Play()
{
	delete timeTex;
	for (auto& x : life) {
		delete x;
	}
}

void Play::Initialize()
{
	//Messenger::GetInstance()->AddPrintOut("プレイシーンです！");
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

	ShakeCamera();
	p_camera->SetLookAtRange(shakePos.x, p_player->GetPosition().y + shakePos.y, 0);
	p_camera->SetPosition(shakePos.x, p_player->GetPosition().y + shakePos.y, -40);
	p_camera->_Update();
	ObjectManager::GetInstance()->Update();

	if (p_player->GetGoalFlag()) {
		p_game_scene->ChangeState(new End());
	}

	if (p_player->GetDeathFlag()) {
		p_game_scene->ChangeState(new Title());
	}

	timeF++;

	if (timeF == 60) {
		timeS++;
		timeF = 0;
	}

	DigitalNumberText::GetInstance()->Print(timeS, 1100, 33);

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
		if (i + 1 <= p_player->GetHitPoint()) {
			life[i]->Draw();
		}
	}

	timeTex->Draw();
}
