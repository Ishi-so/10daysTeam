#include <time.h>
#include "Library.h"
#include "WindowsApp.h"
#include "DirectX12.h"
#include "../Input/KeyInput.h"
#include "../Audio/Sound.h"
#include "../3D/Object3D.h"
#include "../2D/Sprite.h"
#include "../2D/Point2D.h"
#include "../2D/Line2D.h"
#include "../2D/Circle.h"
#include "../Light/LightGroup.h"
#include "../3D/Line.h"
#include "../Particle/ParticleManager.h"
#include "../3D/CollCapsule.h"
#include "../3D/CollBox.h"
#include "../3D/CollCircle.h"
#include "../GameScene/GameScene.h"
#include "../3D/Tessellation.h"

using namespace XIIlib;

XIIlib::Library::Library()
{
}

XIIlib::Library::~Library()
{
	delete gameScene;
	delete dx12;
	w_app->TerminateWindow();
	delete w_app;
}

bool XIIlib::Library::Initialize()
{
	srand(static_cast<unsigned int> (time(NULL)));
	// ウィンドウの生成
	w_app = new WindowsApp();
	w_app->GenerateWindow();
	//DirectX初期化処理
	dx12 = new DirectX12();
	dx12->Initialize(w_app);
	// Input初期化
	keyInput = KeyInput::GetInstance();
	keyInput->Initialize(w_app->GetInstance(), w_app->GetWinHandle());

	// その他汎用クラスの初期化
	Sprite::StaticInitialize();
	Point2D::StaticInitialize();
	Line2D::StaticInitialize();
	Circle::StaticInitialize();
	Line::StaticInitialize();
	Object3D::StaticInitialize();
	LightGroup::StaticInitialize(DirectX12::GetDevice());
	ParticleManager::GetInstance()->Initialize("effect1.png");
	CollisionCapsule::StaticInitialize();
	CollisionBox::StaticInitialize();
	CollisionCircle::StaticInitialize();
	Tessellation::StaticInitialize();

	dx12->SetClearColor(0.5f, 0.5f, 0.5f);

	gameScene = GameScene::Create();

	return true;
}

bool XIIlib::Library::Message()
{
	return w_app->Message();
}

void XIIlib::Library::InputUpdate()
{
	keyInput->Update();
}

void XIIlib::Library::Play()
{
	// ゲームの更新処理
	gameScene->Update();

	// 描画開始
	dx12->Previous();
	// ゲームの描画処理
	gameScene->Draw();
	// 描画終了
	dx12->PostProcessing();
}
