#include "End.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Title.h"
#include "Select.h"
#include "../Input/KeyInput.h"
#include "../2D/Sprite.h"

using namespace XIIlib;

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
	delete returnSelect;
}

void End::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("エンドシーンです！");
	result = Sprite::Create(5, resultPos); // リザルト画像の生成
	result->SetAnchorPoint({ 0.5f, 0.5f });

	for (int i = 0; i < _countof(medal); i++) {
		medal[i] = Sprite::Create(6 + i, medalPos); // メダル画像の生成
		medal[i]->SetAnchorPoint({ 0.5f, 0.5f });
		medal[i]->SetSize(medalSize);
	}
	medalBase = Sprite::Create(9, medalPos); // メダル台画像の生成
	medalBase->SetAnchorPoint({ 0.5f, 0.5f });

	returnTitle = Sprite::Create(10, { 50, 610 }); // タイトルへ画像の生成
	returnTitle->SetSize({ 500 * 0.7f, 100 * 0.7f });
	returnSelect = Sprite::Create(11, { 600, 610 }); // セレクトへ画像の生成
	returnSelect->SetSize({ 900 * 0.7f, 100 * 0.7f });

	titleCursor = Sprite::Create(12, { 50, 610 }); //
	selectCursor = Sprite::Create(13, { 600, 610 }); //
}

void End::Update()
{
	// 押したら切り替え
	/*if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Title());
	}*/

	if (resultPos.y < resultLastY) { // リザルトが最終座標に到達していない時
		resultPos.y += 5.0f; // リザルトを下に移動
		result->SetPosition(resultPos);
	}
	else { // リザルトが最終座標に到達した時
		medalDrawFlag = true; // 描画フラグをtrueに
		if (medalSize.x > medalLastSize.x) {
			medalSize -= {2.0f, 2.0f}; // サイズを縮小
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
			p_game_scene->ChangeState(new Title());
		}
		else if(pushLeftFlag == false) {
			p_game_scene->ChangeState(new Select());
		}
	}
}

void End::Draw()
{
}

void End::DrawTexture()
{
	result->Draw(); // リザルトの描画

	medalBase->Draw(); // メダル台の描画

	if (medalDrawFlag) {
		medal[0]->Draw(); // メダルの描画
	}

	returnTitle->Draw(); // タイトルへの描画
	returnSelect->Draw(); // セレクトへの描画

	if (pushLeftFlag) {
		titleCursor->Draw(); //
	}
	else {
		selectCursor->Draw(); // 
	}

}