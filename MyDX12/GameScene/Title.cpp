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
	delete clonePlayer;
	clonePlayer = nullptr;
	
	for (auto& x : bgArray) {
		delete x;
		x = nullptr;
	}
}

void Title::Initialize()
{
	// オブジェクトの初期化
	const float distTex = 360.0f;
	const float d_texSizeX = 160.0f, d_texSizeY = 90.0f;
	for (int i = 0; i < 3; i++) {
		bgArray.push_back(Sprite::Create(17, { 0,0 }));
		bgArray[i]->SetSize({d_texSizeX * 8.0f,d_texSizeY * 4.0f});
		bgArray[i]->SetPosition({0,distTex * i});
	}

	clonePlayer = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_PLAYER));
	clonePlayer->alpha = 1.0f;

	title = Sprite::Create(14, { 1280 / 2, 720 / 2 });
	title->SetAnchorPoint(center);
	pushSpace = Sprite::Create(15, { 1280 / 2, 720 - 100 });
	pushSpace->SetAnchorPoint(center);
	Messenger::GetInstance()->AddPrintOut("タイトルシーンです！");
}

void Title::Update()
{
	// 上下+-37.2fでカメラ外
	//bg0->position.y = -37;
	//std::cout << bg0->position.y << std::endl;
	const float distTex = 360.0f;
	for (auto& x : bgArray) {
		Math::Vector2 mPos = x->GetPosition();
		x->SetPosition(mPos - Math::Vector2(0,1.0f));
		if (x->GetPosition().y <= -distTex) {
			x->SetPosition({ x->GetPosition().x,distTex * 2.0f });
		}
	}

	const float addRotZ = 1.5f;
	const float maxRot = 360.0f;
	clonePlayer->rotation.z += addRotZ;
	clonePlayer->alpha = 1.0f;
	if (clonePlayer->rotation.z >= maxRot) {
		clonePlayer->rotation.z = clonePlayer->rotation.z - maxRot;
	}
	clonePlayer->Update();
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
	clonePlayer->Draw();
}

void Title::DrawTexture()
{
	pushSpace->Draw();
	title->Draw();
}

void Title::BackTexture()
{
	for (auto& x : bgArray) {
		x->Draw();
	}
}
