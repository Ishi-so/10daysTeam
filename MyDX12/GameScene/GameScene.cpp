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

// Game系
#include "Title.h"
#include "../Game/Player.h"
#include "../Game/ModelLoader.h"
#include "../Game/CSVLoader.h"
#include "../Game/Block.h"
#include "../Game/ItemBox.h"
#include "../Game/Common.h"
#include "../Tool/DigitalNumberText.h"
#include "../Game/PlayerEffectManager.h"

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
	delete playerEffects;
	playerEffects = nullptr;
	delete m_player;
	delete circle;
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
	const float Z_AXIS = -25; // 奥行を設定

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

	// モデルローダーの設定
	ModelLoader::GetInstance()->Initialize();
	ModelLoader::GetInstance()->Load();

	int texind = 2;
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/ASCIItex_ver2.png");
	Sprite::LoadTexture(debugJISTextTexNumber, L"Resources/JIS_Code_ver.1.02.png");
	Sprite::LoadTexture(texind, L"Resources/digitalNum.png");					texind++;//2
	Sprite::LoadTexture(texind, L"Resources/effect1.png");						texind++;//3
	Sprite::LoadTexture(texind, L"Resources/white1x1.png");						texind++;//4
	Sprite::LoadTexture(texind, L"Resources/result.png");                       texind++;//5
	Sprite::LoadTexture(texind, L"Resources/goldMedal.png");                    texind++;//6
	Sprite::LoadTexture(texind, L"Resources/SilverMedal.png");                  texind++;//7
	Sprite::LoadTexture(texind, L"Resources/bronzeMedal.png");                  texind++;//8
	Sprite::LoadTexture(texind, L"Resources/medalBase.png");                    texind++;//9
	Sprite::LoadTexture(texind, L"Resources/return_title.png");                 texind++;//10
	Sprite::LoadTexture(texind, L"Resources/return_select.png");                texind++;//11


	DebugJISText::GetInstance()->Initialize(debugJISTextTexNumber);

	circle = new Circle();
	circle->Initialize();

	// ステージ生成
	mapData = CSVLoader::GetCSVTwoVector("stage2", CSVLoader::BoardType::BOARD_2D, 15);
	int xSize = CSVLoader::GetSize("x"), ySize = CSVLoader::GetSize("y");
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (mapData[i][j] == 0)// なし
			{
			}
			else if (mapData[i][j] == 1) // プレイヤー
			{
				// player生成
				m_player = Player::Create({
					Common::ConvertPositionX(j),
					Common::ConvertPositionY(i),
					0
					}
				);
			}
			else if (mapData[i][j] == 2) // Block
			{

				std::shared_ptr<Block> box = Block::Create({
				Common::ConvertPositionX(j),
				Common::ConvertPositionY(i),
				0 },
					{ 1,1,1 }
				);
				ObjectManager::GetInstance()->AddObject(std::move(box));

			}
			else if (mapData[i][j] == 3) // Item
			{
				std::shared_ptr<ItemBox> iBox = ItemBox::Create({
				Common::ConvertPositionX(j),
				Common::ConvertPositionY(i),
				0 },
					{ 1,1,1 }
				);
				ObjectManager::GetInstance()->AddObject(std::move(iBox));
			}
			else
			{
				// なし
			}
		}
	}

	// シーン設定
	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	// マネージャーの初期化
	ObjectManager::GetInstance()->Initialize();
	// マネージャーにPlayerを設定
	ObjectManager::GetInstance()->SetPlayer(m_player);

	// カメラの更新(1f目おかしくなるため)
	Math::Vector3 playerPos = m_player->GetPosition();
	d_camera->SetPosition(playerPos.x, playerPos.y, Z_AXIS);
	d_camera->_Update();

	DigitalNumberText::GetInstance()->Initialize(2);
	playerEffects = PlayerEffectManager::Create();
	playerDistTimer = 0;
	return true;
}

void GameScene::Update()
{
	// カメラの動き定数
	const float m_rad = 0.01f;
	const float m_range = 0.1f;
	const float lookatRange = 5.0f;

	// カメラの更新
	d_camera->SetLookAtRange(0, m_player->GetPosition().y, 0);
	d_camera->SetPosition(0, m_player->GetPosition().y, -40);
	d_camera->_Update();

	// シーンの更新
	state->Update();

	m_player->Update(); // SceneState派生のクラスでやる(今は仮置き)
	if (playerDistTimer >= 10) {
		playerDistTimer = 0;
		if (m_player->GetDirection().y >= 1.0f) {
			
		}
	}
	playerEffects->Add(m_player->GetDirection().normalize(), m_player->GetPosition());
	playerDistTimer++;

	playerEffects->Update();

	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	// 背景スプライト
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	// 3Dまたはポストエフェクトの描画
	Object3D::PreDraw();
	m_player->Draw(); // SceneState派生のクラスでやる(今は仮置き)

	ObjectManager::GetInstance()->Draw();
	state->Draw();
	playerEffects->Draw();
	Object3D::PostDraw();

	// ビルボード用オブジェクト
	

	// ImGuiの描画

	// 前景スプライト

	// 文字スプライト
	Sprite::PreDraw();

	state->DrawTexture();
	XIIlib::Messenger::GetInstance()->DrawMessage();
	DebugJISText::GetInstance()->DrawAll();
	DigitalNumberText::GetInstance()->DrawAll();

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