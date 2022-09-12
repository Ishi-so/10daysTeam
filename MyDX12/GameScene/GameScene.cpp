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

// Game邉ｻ
#include "Title.h"
#include "../Game/Player.h"
#include "../Game/ModelLoader.h"
#include "../Game/CSVLoader.h"
#include "../Game/Block.h"
#include "../Game/ItemBox.h"
#include "../Game/Common.h"
#include "../Tool/DigitalNumberText.h"
#include "../Game/InstBill.h"

GameScene* GameScene::Create()
{
	// 3D繧�E�繝悶ず繧�E�繧�E�繝医�E�繧�E�繝ｳ繧�E�繧�E�繝ｳ繧�E�繧堤函謁E
	GameScene* pGameScene = new GameScene();
	if (pGameScene == nullptr)
	{
		return nullptr;
	}

	// 蛻晁E��蛹
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
	delete state;
	state = nullptr;
	delete lightGroup;
	lightGroup = nullptr;
	delete d_camera;
	d_camera = nullptr;
}

bool GameScene::Initialize()
{
	d_camera = new DebugCamera();
	d_camera->_Initialize(100.0f, 0.05f, 10.0f);
	d_camera->SetLookAtRange(0, 1, 0);
	const float Z_AXIS = -25; // 螂･陦後ｒ險�E�螳

	// 繝ｩ繧�E�繝育函謁E
	lightGroup = LightGroup::Create();

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetCircleShadowActive(0, true);
	lightGroup->SetCircleShadowActive(1, true);

	// 繧�E�繝｡繝ｩ縺�E�繧�E�繝�ヨ
	Object3D::SetDebugCamera(d_camera);
	// 繝ｩ繧�E�繝医�E�繧�E�繝�ヨ
	Object3D::SetLightGroup(lightGroup);

	// 繝｢繝�Ν繝ｭ繝ｼ繁E繝ｼ縺�E�險�E�螳
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
	Sprite::LoadTexture(texind, L"Resources/medalBase.png");                   texind++;//9
	Sprite::LoadTexture(texind, L"Resources/R.png");                       texind++;//10
	Sprite::LoadTexture(texind, L"Resources/E.png");                       texind++;//11
	Sprite::LoadTexture(texind, L"Resources/S.png");                       texind++;//12
	Sprite::LoadTexture(texind, L"Resources/U.png");                       texind++;//13
	Sprite::LoadTexture(texind, L"Resources/L.png");                       texind++;//14
	Sprite::LoadTexture(texind, L"Resources/T.png");                       texind++;//15


	DebugJISText::GetInstance()->Initialize(debugJISTextTexNumber);

	circle = new Circle();
	circle->Initialize();

	// 繧�E�繝��E�繧�E�縺�E�逕滓�
	mapData = CSVLoader::GetCSVTwoVector("stage0", CSVLoader::BoardType::BOARD_2D,64);
	int xSize = CSVLoader::GetSize("x"), ySize = CSVLoader::GetSize("y");
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (mapData[i][j] == 0)// 縺�E�縺
			{}
			else if (mapData[i][j] == 1) // 繝励Ξ繧�E�繝､繝ｼ
			{
				// player縺�E�逕滓�
				m_player = Player::Create({
					Common::ConvertPositionX(j),
					Common::ConvertPositionY(i),
					0
					}
				);
			}
			else if (mapData[i][j] == 2) // block
			{
				
				std::shared_ptr<Block> box = Block::Create({
				Common::ConvertPositionX(j),
				Common::ConvertPositionY(i),
				0 },
					{ 1,1,1 }
				);
				ObjectManager::GetInstance()->AddObject(std::move(box));

			}
			else if (mapData[i][j] == 3) // item
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
      {} // なぁE
		}
	}

	

	// 繧�E�繝ｼ繝ｳ險�E�螳
	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	// 繝槭ロ繝ｼ繧�E�繝｣繝ｼ縺�E�蛻晁E��蛹
	ObjectManager::GetInstance()->Initialize();
	// 繝励Ξ繧�E�繝､繝ｼ繧偵�E�繝阪�E�繧�E�繝｣繝ｼ縺�E�繧�E�繝斐�E�
	ObjectManager::GetInstance()->SetPlayer(m_player);

	// 繧�E�繝｡繝ｩ縺�E�譖ｴ譁E��(1f逶�E�縺翫°縺励�E�縺�E�繧九◆繧)
	Math::Vector3 playerPos = m_player->GetPosition();
	d_camera->SetPosition(playerPos.x, playerPos.y,Z_AXIS);
	d_camera->_Update();

	DigitalNumberText::GetInstance()->Initialize(2);
	return true;
}

void GameScene::Update()
{
	// 繧�E�繝｡繝ｩ縺�E�蜍輔″縺�E�蜁E��送E
	const float m_rad = 0.01f;
	const float m_range = 0.1f;
	const float lookatRange = 5.0f;

	// カメラ更新
	d_camera->SetLookAtRange(0, m_player->GetPosition().y,0);
	d_camera->SetPosition(0,m_player->GetPosition().y,-40);

	d_camera->_Update();

	state->Update();

	m_player->Update(); // SceneState豢�E�逕溘�繧�E�繝ｩ繧�E�縺�E�繧�E��E�E莉翫�E�莉ｮ鄂ｮ縺)
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	// 閭梧勹繧�E�繝励Λ繧�E�繁E
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	//3D縺�E�縺溘�繝昴せ繝医お繝輔ぉ繧�E�繝医�E�謠冗判
	Object3D::PreDraw();
	m_player->Draw(); // SceneState豢�E�逕溘�繧�E�繝ｩ繧�E�縺�E�繧�E��E�E莉翫�E�莉ｮ鄂ｮ縺)

	ObjectManager::GetInstance()->Draw();
	state->Draw();
	Object3D::PostDraw();

	// �r���{�[�h�p�I�u�W�F�N�g
	InstBill::PreDraw();



	InstBill::PostDraw();

	// ImGui縺�E�謠冗判

	// 蜑肴勹繧�E�繝励Λ繧�E�繁E

	// 譁E���E�励せ繝励Λ繧�E�繁E
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
