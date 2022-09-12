#include "End.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Title.h"
#include "../Input/KeyInput.h"
#include "../2D/Sprite.h"

using namespace XIIlib;

End::End()
{
}

End::~End()
{
	delete result;
	/*for (auto x : results) {
		delete x;
	}*/

	for (auto x : medal){
		delete x;
	}
	delete medalBase;
}

void End::Initialize()
{
	Messenger::GetInstance()->AddPrintOut("エンドシーンです！");
	result = Sprite::Create(5, resultPos); // リザルト画像の生成
	result->SetAnchorPoint({ 0.5f, 0.5f });

	/*for (int i = 0; i < _countof(results); i++) {
		resultSize[i] = { resultLastSize * 10 };
		results[i] = Sprite::Create(10 + i, { (float)150 + 200 * i,150 });
		results[i]->SetAnchorPoint({ 0.5f, 0.5f });
		results[i]->SetSize(resultSize[i]);
	}*/

	for (int i = 0; i < _countof(medal); i++) {
		medal[i] = Sprite::Create(6 + i, medalPos); // メダル画像の生成
		medal[i]->SetAnchorPoint({ 0.5f, 0.5f });
		medal[i]->SetSize(medalSize);
	}
	medalBase = Sprite::Create(9, medalPos); // メダル台画像の生成
	medalBase->SetAnchorPoint({ 0.5f, 0.5f });
}

void End::Update()
{
	// 押したら切り替え
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Title());
	}

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

	//switch (sChar){
	//case ShrinkChar::R:
	//	if (resultSize[0].x >= resultLastSize.x) {
	//		resultSize[0] -= shrinkValue;
	//		if (alpha > 1) {
	//			alpha += 0.1f;
	//		}
	//		else {
	//			alpha = 1.0f;
	//		}
	//		results[0]->SetSize({ resultSize[0] });
	//		results[0]->SetColor(1, 1, 1, alpha);
	//	}
	//	else {
	//		sChar = ShrinkChar::E;
	//	}
	//	break;
	//case ShrinkChar::E:
	//	if (resultSize[1].x >= resultLastSize.x) {
	//		resultSize[1] -= shrinkValue;
	//		results[1]->SetSize({ resultSize[1] });
	//	}
	//	else {
	//		sChar = ShrinkChar::S;
	//	}
	//	break;
	//case ShrinkChar::S:
	//	if (resultSize[2].x >= resultLastSize.x) {
	//		resultSize[2] -= shrinkValue;
	//		results[2]->SetSize({ resultSize[2] });
	//	}
	//	else {
	//		sChar = ShrinkChar::U;
	//	}
	//	break;
	//case ShrinkChar::U:
	//	if (resultSize[3].x >= resultLastSize.x) {
	//		resultSize[3] -= shrinkValue;
	//		results[3]->SetSize({ resultSize[3] });
	//	}
	//	else {
	//		sChar = ShrinkChar::L;
	//	}
	//	break;
	//case ShrinkChar::L:
	//	if (resultSize[4].x >= resultLastSize.x) {
	//		resultSize[4] -= shrinkValue;
	//		results[4]->SetSize({ resultSize[4] });
	//	}
	//	else {
	//		sChar = ShrinkChar::T;
	//	}
	//	break;
	//case ShrinkChar::T:
	//	if (resultSize[5].x >= resultLastSize.x) {
	//		resultSize[5] -= shrinkValue;
	//		results[5]->SetSize({ resultSize[5] });
	//	}
	//	else {
	//		sChar = ShrinkChar::M;
	//	}
	//	break;
	//case ShrinkChar::M:
	//	medalDrawFlag = true; // 描画フラグをtrueに
	//	if (medalSize.x > medalLastSize.x) {
	//		medalSize -= {2.0f, 2.0f}; // サイズを縮小
	//		for (auto x : medal) {
	//			x->SetSize(medalSize);
	//		}
	//	}
	//	break;
	//}
}

void End::Draw()
{
}

void End::DrawTexture()
{
	result->Draw(); // リザルトの描画

	/*for (int i = 0; i < _countof(results); i++) {
		results[i]->Draw();
	}*/

	medalBase->Draw(); // メダル台の描画

	if (medalDrawFlag) {
		medal[0]->Draw(); // メダルの描画
	}
}