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
	delete operationR;
	delete operationL;
}

void Play::Initialize()
{
	//Messenger::GetInstance()->AddPrintOut("プレイシーンです！");
	const float texSizeX = 1280.0f * 0.25f;
	operationL = Sprite::Create(20, { texSizeX, 720 * 0.8f });
	operationL->SetAnchorPoint(center);
	//operationL->SetSize({ 128.0f,64.0f * 5.0f });

	operationR = Sprite::Create(21, { 1280.0f - texSizeX, 720 * 0.8f });
	operationR->SetAnchorPoint(center);
	//operationR->SetSize({ 128.0f * 5.0f ,64.0f * 5.0f });

	for (int i = 0; i < _countof(life); i++) {
		life[i] = Sprite::Create(18, { (float)0 + 130 * i, 0 });
	}

	timeTex = Sprite::Create(19, { 1280 - 300, 0 });
}

void Play::Update()
{
	if (p_player->GetDeathFlag()) {
		appFlag = true;
	}
	p_player->Update();
	
	ShakeCamera();
	p_camera->SetLookAtRange(shakePos.x, p_player->GetPosition().y + shakePos.y, 0);
	p_camera->SetPosition(shakePos.x, p_player->GetPosition().y + shakePos.y, zAxis);
	p_camera->_Update();
	ObjectManager::GetInstance()->Update();

	if (p_player->GetGoalFlag()) {
		p_game_scene->ChangeState(new End());
	}

	if (appFlag) { 
		zAxis += 1.0f;
		if (zAxis >= -20) {
			shakePos = {};
		}
	}
	if (zAxis >= 0) {
		p_player->InitPlayerData();
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
	operationL->Draw();
	operationR->Draw();

	for (int i = 0; i < _countof(life); i++) {
		if (i + 1 <= p_player->GetHitPoint()) {
			life[i]->Draw();
		}
	}

	timeTex->Draw();
}
