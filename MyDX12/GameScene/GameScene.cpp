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

// Game驍会ｽｻ
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
	// 3D郢ｧ・ｪ郢晄じ縺夂ｹｧ・ｧ郢ｧ・ｯ郢晏現・ｽ郢ｧ・､郢晢ｽｳ郢ｧ・ｹ郢ｧ・ｿ郢晢ｽｳ郢ｧ・ｹ郢ｧ蝣､蜃ｽ隰・
	GameScene* pGameScene = new GameScene();
	if (pGameScene == nullptr)
	{
		return nullptr;
	}

	// 陋ｻ譎・ｄ陋ｹ
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
	const float Z_AXIS = -25; // 陞ゑｽ･髯ｦ蠕鯉ｽ帝坎・ｭ陞ｳ

	// 郢晢ｽｩ郢ｧ・､郢晁ご蜃ｽ隰・
	lightGroup = LightGroup::Create();

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetCircleShadowActive(0, true);
	lightGroup->SetCircleShadowActive(1, true);

	// 郢ｧ・ｫ郢晢ｽ｡郢晢ｽｩ邵ｺ・ｮ郢ｧ・ｻ郢晢ｿｽ繝ｨ
	Object3D::SetDebugCamera(d_camera);
	// 郢晢ｽｩ郢ｧ・､郢晏現・ｽ郢ｧ・ｻ郢晢ｿｽ繝ｨ
	Object3D::SetLightGroup(lightGroup);

	// 郢晢ｽ｢郢晢ｿｽﾎ晉ｹ晢ｽｭ郢晢ｽｼ郢・郢晢ｽｼ邵ｺ・ｮ髫ｪ・ｭ陞ｳ
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

	// 郢ｧ・ｹ郢晢ｿｽ・ｽ郢ｧ・ｸ邵ｺ・ｮ騾墓ｻ難ｿｽ
	mapData = CSVLoader::GetCSVTwoVector("stage0", CSVLoader::BoardType::BOARD_2D,64);
	int xSize = CSVLoader::GetSize("x"), ySize = CSVLoader::GetSize("y");
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (mapData[i][j] == 0)// 邵ｺ・ｪ邵ｺ
			{}
			else if (mapData[i][j] == 1) // 郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ
			{
				// player邵ｺ・ｮ騾墓ｻ難ｿｽ
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
      {} // 縺ｪ縺・
		}
	}

	

	// 郢ｧ・ｷ郢晢ｽｼ郢晢ｽｳ髫ｪ・ｭ陞ｳ
	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	// 郢晄ｧｭ繝ｭ郢晢ｽｼ郢ｧ・ｸ郢晢ｽ｣郢晢ｽｼ邵ｺ・ｮ陋ｻ譎・ｄ陋ｹ
	ObjectManager::GetInstance()->Initialize();
	// 郢晏干ﾎ樒ｹｧ・､郢晢ｽ､郢晢ｽｼ郢ｧ蛛ｵ・ｽ郢晞亂・ｽ郢ｧ・ｸ郢晢ｽ｣郢晢ｽｼ邵ｺ・ｫ郢ｧ・ｳ郢晄鱒・ｽ
	ObjectManager::GetInstance()->SetPlayer(m_player);

	// 郢ｧ・ｫ郢晢ｽ｡郢晢ｽｩ邵ｺ・ｮ隴厄ｽｴ隴・ｽｰ(1f騾ｶ・ｮ邵ｺ鄙ｫﾂｰ邵ｺ蜉ｱ・･邵ｺ・ｪ郢ｧ荵昶螺郢ｧ)
	Math::Vector3 playerPos = m_player->GetPosition();
	d_camera->SetPosition(playerPos.x, playerPos.y,Z_AXIS);
	d_camera->_Update();

	DigitalNumberText::GetInstance()->Initialize(2);
	return true;
}

void GameScene::Update()
{
	// 郢ｧ・ｫ郢晢ｽ｡郢晢ｽｩ邵ｺ・ｮ陷崎ｼ披ｳ邵ｺ・ｮ陷・ｽｦ騾・
	const float m_rad = 0.01f;
	const float m_range = 0.1f;
	const float lookatRange = 5.0f;

	// 繧ｫ繝｡繝ｩ譖ｴ譁ｰ
	d_camera->SetLookAtRange(0, m_player->GetPosition().y,0);
	d_camera->SetPosition(0,m_player->GetPosition().y,-40);

	d_camera->_Update();

	state->Update();

	m_player->Update(); // SceneState雎｢・ｾ騾墓ｺ假ｿｽ郢ｧ・ｯ郢晢ｽｩ郢ｧ・ｹ邵ｺ・ｧ郢ｧ・ｽ・・闔臥ｿｫ・ｽ闔会ｽｮ驗ゑｽｮ邵ｺ)
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	// 髢ｭ譴ｧ蜍ｹ郢ｧ・ｹ郢晏干ﾎ帷ｹｧ・､郢・
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	//3D邵ｺ・ｾ邵ｺ貅假ｿｽ郢晄亢縺帷ｹ晏現縺顔ｹ晁ｼ斐♂郢ｧ・ｯ郢晏現・ｽ隰蜀怜愛
	Object3D::PreDraw();
	m_player->Draw(); // SceneState雎｢・ｾ騾墓ｺ假ｿｽ郢ｧ・ｯ郢晢ｽｩ郢ｧ・ｹ邵ｺ・ｧ郢ｧ・ｽ・・闔臥ｿｫ・ｽ闔会ｽｮ驗ゑｽｮ邵ｺ)

	ObjectManager::GetInstance()->Draw();
	state->Draw();
	Object3D::PostDraw();

	// ビルボード用オブジェクト
	InstBill::PreDraw();



	InstBill::PostDraw();

	// ImGui邵ｺ・ｮ隰蜀怜愛

	// 陷題ざ蜍ｹ郢ｧ・ｹ郢晏干ﾎ帷ｹｧ・､郢・

	// 隴・ｿｽ・ｭ蜉ｱ縺帷ｹ晏干ﾎ帷ｹｧ・､郢・
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
