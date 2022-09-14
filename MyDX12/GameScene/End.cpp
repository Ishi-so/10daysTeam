#include "End.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Title.h"
#include "Select.h"
#include "../Input/KeyInput.h"
#include "../2D/Sprite.h"
#include "../Game/Player.h"
#include "../Game/ObjectManager.h"
#include "../Tool/DigitalNumberText.h"

using namespace XIIlib;

const float End::resultScore = score;

End::End()
{
}

End::~End()
{
	delete result;

	for (auto x : medal){
		delete x;
	}
	delete medalBase;

	delete returnTitle;

	delete titleCursor;
}

void End::Initialize()
{
	p_player->Update();
	ObjectManager::GetInstance()->Update();
	Messenger::GetInstance()->AddPrintOut("エンドシーンです！");
	result = Sprite::Create(5, resultPos); // リザルト画像の生成
	result->SetAnchorPoint(center);
	result->SetSize({ 450, 150 });

	for (int i = 0; i < _countof(medal); i++) {
		medal[i] = Sprite::Create(6 + i, medalPos); // メダル画像の生成
		medal[i]->SetAnchorPoint(center);
		medal[i]->SetSize(medalSize);
	}
	medalBase = Sprite::Create(9, medalPos); // メダル台画像の生成
	medalBase->SetAnchorPoint(center);

	returnTitle = Sprite::Create(10, titlePos); // タイトルへ画像の生成
	returnTitle->SetSize({ 500 * 0.7f, 100 * 0.7f });
	returnTitle->SetAnchorPoint(center);

	titleCursor = Sprite::Create(12, titlePos); //
	titleCursor->SetAnchorPoint(center);

	timeTex = Sprite::Create(19, resultPos + Math::Vector2(0, 130));
	timeTex->SetAnchorPoint(center);
}

void End::Update()
{
	if (resultPos.y < resultLastY) { // リザルトが最終座標に到達していない時
		resultPos.y += 5.0f; // リザルトを下に移動
		result->SetPosition(resultPos);
		timeTex->SetPosition(resultPos + Math::Vector2(0, 130));
	}
	else { // リザルトが最終座標に到達した時
		medalDrawFlag = true; // メダル描画フラグをtrueに
		if (medalSize.x > medalLastSize.x) {
			medalSize -= {3.0f, 3.0f}; // サイズを縮小
			for (auto x : medal) {
				x->SetSize(medalSize);
			}
		}
	}

	XIIlib::KeyInput* input = XIIlib::KeyInput::GetInstance();

	if (input->Trigger(DIK_LEFT) || input->Trigger(DIK_A)) {
		pushLeftFlag = true;
	}
	else if (input->Trigger(DIK_RIGHT) || input->Trigger(DIK_D)) {
		pushLeftFlag = false;
	}

	if (input->Trigger(DIK_SPACE)) {
		if (pushLeftFlag) {
			p_player->InitPlayerData();
			p_game_scene->ChangeState(new Title());
		}
		else if (pushLeftFlag == false) {
			p_game_scene->ChangeState(new Select());
		}
	}

	if (resultTime < goldTime) {
		medalColor = MedalColor::GOLD; // 金色に
	}
	else if (resultTime < silverTime && resultTime >= goldTime) {
		medalColor = MedalColor::SILVER; // 銀色に
	}
	else {
		medalColor = MedalColor::BRONZE; // 銅色に
	}

	DigitalNumberText::GetInstance()->Print(resultTime, resultPos.x - 20, resultPos.y + 110);
}

void End::Draw()
{
	p_player->Draw();
	ObjectManager::GetInstance()->Draw();
}

void End::DrawTexture()
{
	result->Draw(); // リザルトの描画

	medalBase->Draw(); // メダル台の描画

	if (medalDrawFlag) {
		medal[static_cast<int>(medalColor)]->Draw(); // メダルの描画
	}

	returnTitle->Draw(); // タイトルへの描画

	titleCursor->Draw();

	timeTex->Draw();
}