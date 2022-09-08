#include "GameScene.h"
#include "../Light/LightGroup.h"
#include "../Camera/DebugCamera.h"
#include "../3D/Object3D.h"
#include "../3D/ObjectContainer.h"
#include "../2D/Sprite.h"
#include "../Input/KeyInput.h"
#include "../Tool/DebugJISText.h"
#include "../Game/ObjectManager.h"

#include "../2D/Circle.h"

#include "Title.h"
#include "../Game/Player.h"

GameScene* GameScene::Create()
{
	// 3Dオブジェクトのインスタンスを生成
	GameScene* pGameScene = new GameScene();
	if (pGameScene == nullptr)
	{
		return nullptr;
	}

	// 初期化
	if (!pGameScene->Initialize())
	{
		delete pGameScene;
		return nullptr;
	}

	return pGameScene;
}

GameScene::GameScene()
{
	state = new Title();
}

GameScene::~GameScene()
{
	delete m_player;
	delete circle;
	delete objectB;
	delete objectA;
	delete state;
	state = nullptr;
	delete lightGroup;
	lightGroup = nullptr;
	delete d_camera;
	d_camera = nullptr;
}

bool GameScene::Initialize()
{
	// ここは始まりの書!!
	// アフロディ林属性なのにゴッドノウズとヘブンズタイムは風属性

	d_camera = new DebugCamera();
	d_camera->_Initialize(100.0f, 0.05f, 10.0f);
	d_camera->SetLookAtRange(0, 1, 0);

	// ライト生成
	lightGroup = LightGroup::Create();

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetCircleShadowActive(0, true);
	lightGroup->SetCircleShadowActive(1, true);

	// カメラのセット
	Object3D::SetDebugCamera(d_camera);
	// ライトのセット
	Object3D::SetLightGroup(lightGroup);

	d_camera->_Update();
	int texind = 2;
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/ASCIItex_ver2.png");
	Sprite::LoadTexture(debugJISTextTexNumber, L"Resources/JIS_Code_ver.1.02.png");
	Sprite::LoadTexture(texind, L"Resources/digitalNum.png");					texind++;//2
	Sprite::LoadTexture(texind, L"Resources/effect1.png");						texind++;//3

	DebugJISText::GetInstance()->Initialize(debugJISTextTexNumber);

	objectA = Object3D::Create(Model::CreateFromOBJ("sphere"));
	objectB = Object3D::Create(Model::CreateFromOBJ("sphere"));

	cameraPos = {0.0f,1.2f,-5.0f};
	d_camera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z);

	circle = new Circle();
	circle->Initialize();

	// playerの生成
	m_player = Player::Create();

	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	ObjectManager::GetInstance()->Initialize();

	return true;
}

void GameScene::Update()
{
	// カメラの動きの処理
	const float m_rad = 0.01f;
	const float m_range = 0.1f;
	const float lookatRange = 5.0f;
	if (XIIlib::KeyInput::GetInstance()->Push(DIK_A)) {
		cameRad -= m_rad;
	}
	else if (XIIlib::KeyInput::GetInstance()->Push(DIK_D)) {
		cameRad += m_rad;
	}

	if (XIIlib::KeyInput::GetInstance()->Push(DIK_UP)) {
		cameraPos.x += sinf(cameRad) * m_range;
		cameraPos.z += cosf(cameRad) * m_range;
	}
	if (XIIlib::KeyInput::GetInstance()->Push(DIK_DOWN)) {
		cameraPos.x -= sinf(cameRad) * m_range;
		cameraPos.z -= cosf(cameRad) * m_range;
	}
	if (XIIlib::KeyInput::GetInstance()->Push(DIK_LEFT)) {
		cameraPos.x -= cosf(cameRad) * m_range;
		cameraPos.z += sinf(cameRad) * m_range;
	}
	if (XIIlib::KeyInput::GetInstance()->Push(DIK_RIGHT)) {
		cameraPos.x += cosf(cameRad) * m_range;
		cameraPos.z -= sinf(cameRad) * m_range;
	}

	d_camera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z);
	Math::Vector3 cLookAtPt = { 0,0,0 };
	cLookAtPt.x = d_camera->GetPos_X() + (sinf(m_rad) * lookatRange);
	cLookAtPt.z = d_camera->GetPos_Z() + (cosf(m_rad) * lookatRange);

	d_camera->SetLookAtRange(cLookAtPt.x, cLookAtPt.y, cLookAtPt.z);

	d_camera->SetUpVector(0.0f, 1.0f, 0.0f);

	// カメラ更新
	d_camera->_Update();

	static_cast<Object3D*>(objectA)->position = {0,0,-2.0f};
	static_cast<Object3D*>(objectA)->scale = {2,2,2};
	static_cast<Object3D*>(objectA)->alpha = 0.7f;
	static_cast<Object3D*>(objectA)->rotation.z = 90.0f;
	//static_cast<Object3D*>(objectA)->color = {1,0,0};

	static_cast<Object3D*>(objectB)->position = {0.0f,0,2.0f};

	static_cast<Object3D*>(objectA)->Update();
	static_cast<Object3D*>(objectB)->Update();

	// Aは透過オブジェクト、Bは不透明オブジェクト
	// Zバッファの関係で奥から先に描画される
	// そのため本来はそのままでいいのだが
	// 透過オブジェクトは後に描画しなければならない
	// これを解決するためにZの座標で判別するのではなく
	// デプス値で判別しなければならない
	// 手順として、アルファ値が1であるかどうかの判別をする
	// 判別出来たら不透明を先に描画させる
	// その後残りを描画させるのだがもし
	// 描画順においておかしな点がある場合はデプス地で判定

	// 第一のフィルタ(IF:アルファ値)

	// 第二のフィルタ(IF：デプス値(Z値))
	circle->DrawCircle(300,300,100,255, 255, 255, 255);

	state->Update();

	m_player->Update(); // SceneState派生のクラスでやる(今は仮置き)
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	// 背景スプライト
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	//3Dまたはポストエフェクトの描画
	Object3D::PreDraw();
	//static_cast<Object3D*>(objectB)->Draw();
	m_player->Draw(); // SceneState派生のクラスでやる(今は仮置き)
	//static_cast<Object3D*>(objectA)->Draw();

	ObjectManager::GetInstance()->Draw();
	Object3D::PostDraw();

	state->Draw();

	// ImGuiの描画

	// 前景スプライト

	// 文字スプライト
	Sprite::PreDraw();

	XIIlib::Messenger::GetInstance()->DrawMessage();
	DebugJISText::GetInstance()->DrawAll();

	Sprite::PostDraw();

	Circle::PreDraw();
	circle->Draw();
	Circle::PostDraw();
}

void GameScene::ChangeState(SceneState* different_state)
{
	delete state;
	state = nullptr;
	state = different_state;
	state->Initialize();
}
