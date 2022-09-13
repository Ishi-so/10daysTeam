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

// Game�n
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
	// 3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	GameScene* pGameScene = new GameScene();
	if (pGameScene == nullptr)
	{
		return nullptr;
	}

	// ������
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
	// �����͎n�܂�̏�!!
	// �A�t���f�B�ё����Ȃ̂ɃS�b�h�m�E�Y�ƃw�u���Y�^�C���͕�����

	d_camera = new DebugCamera();
	d_camera->_Initialize(100.0f, 0.05f, 10.0f);
	d_camera->SetLookAtRange(0, 1, 0);
	const float Z_AXIS = -25; // ���s��ݒ�

	// ���C�g����
	lightGroup = LightGroup::Create();

	lightGroup->SetDirLightActive(0, true);
	lightGroup->SetDirLightActive(1, true);
	lightGroup->SetDirLightActive(2, true);

	lightGroup->SetCircleShadowActive(0, true);
	lightGroup->SetCircleShadowActive(1, true);

	// �J�����̃Z�b�g
	Object3D::SetDebugCamera(d_camera);
	// ���C�g�̃Z�b�g
	Object3D::SetLightGroup(lightGroup);

	// ���f�����[�_�[�̐ݒ�
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

	// �X�e�[�W����
	mapData = CSVLoader::GetCSVTwoVector("stage2", CSVLoader::BoardType::BOARD_2D, 15);
	int xSize = CSVLoader::GetSize("x"), ySize = CSVLoader::GetSize("y");
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (mapData[i][j] == 0)// �Ȃ�
			{
			}
			else if (mapData[i][j] == 1) // �v���C���[
			{
				// player����
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
				// �Ȃ�
			}
		}
	}

	// �V�[���ݒ�
	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	// �}�l�[�W���[�̏�����
	ObjectManager::GetInstance()->Initialize();
	// �}�l�[�W���[��Player��ݒ�
	ObjectManager::GetInstance()->SetPlayer(m_player);

	// �J�����̍X�V(1f�ڂ��������Ȃ邽��)
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
	// �J�����̓����萔
	const float m_rad = 0.01f;
	const float m_range = 0.1f;
	const float lookatRange = 5.0f;

	// �J�����̍X�V
	d_camera->SetLookAtRange(0, m_player->GetPosition().y, 0);
	d_camera->SetPosition(0, m_player->GetPosition().y, -40);
	d_camera->_Update();

	// �V�[���̍X�V
	state->Update();

	m_player->Update(); // SceneState�h���̃N���X�ł��(���͉��u��)
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
	// �w�i�X�v���C�g
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	// 3D�܂��̓|�X�g�G�t�F�N�g�̕`��
	Object3D::PreDraw();
	m_player->Draw(); // SceneState�h���̃N���X�ł��(���͉��u��)

	ObjectManager::GetInstance()->Draw();
	state->Draw();
	playerEffects->Draw();
	Object3D::PostDraw();

	// �r���{�[�h�p�I�u�W�F�N�g
	

	// ImGui�̕`��

	// �O�i�X�v���C�g

	// �����X�v���C�g
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