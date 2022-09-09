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
#include "../Game/Common.h"

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

	d_camera->_Update();
	int texind = 2;
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/ASCIItex_ver2.png");
	Sprite::LoadTexture(debugJISTextTexNumber, L"Resources/JIS_Code_ver.1.02.png");
	Sprite::LoadTexture(texind, L"Resources/digitalNum.png");					texind++;//2
	Sprite::LoadTexture(texind, L"Resources/effect1.png");						texind++;//3
	Sprite::LoadTexture(texind, L"Resources/white1x1.png");						texind++;//4

	DebugJISText::GetInstance()->Initialize(debugJISTextTexNumber);

	cameraPos = {0.0f,1.2f,-5.0f};
	d_camera->SetPosition(cameraPos.x, cameraPos.y, cameraPos.z);

	circle = new Circle();
	circle->Initialize();

	// �X�e�[�W�̐���
	mapData = CSVLoader::GetCSVTwoVector("stage0", CSVLoader::BoardType::BOARD_2D,64);
	int xSize = CSVLoader::GetSize("x"), ySize = CSVLoader::GetSize("y");
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			if (mapData[i][j] == 0)// �Ȃ�
			{}
			else if (mapData[i][j] == 1) // �v���C���[
			{
				// player�̐���
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
			{}
			else {} // �Ȃ�
		}
	}


	// �V�[���ݒ�
	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	
	// �}�l�[�W���[�̏�����
	ObjectManager::GetInstance()->Initialize();
	// �v���C���[���}�l�[�W���[�ɃR�s�[
	ObjectManager::GetInstance()->SetPlayer(m_player);

	return true;
}

void GameScene::Update()
{
	// �J�����̓����̏���
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

	// �J�����X�V
	d_camera->_Update();

	state->Update();

	m_player->Update(); // SceneState�h���̃N���X�ł��(���͉��u��)
	ObjectManager::GetInstance()->Update();
}

void GameScene::Draw()
{
	// �w�i�X�v���C�g
	Sprite::PreDraw();

	Sprite::PostDraw();
	DirectX12::ClearDepthBuffer();
	//3D�܂��̓|�X�g�G�t�F�N�g�̕`��
	Object3D::PreDraw();
	m_player->Draw(); // SceneState�h���̃N���X�ł��(���͉��u��)

	ObjectManager::GetInstance()->Draw();
	Object3D::PostDraw();

	state->Draw();

	// ImGui�̕`��

	// �O�i�X�v���C�g

	// �����X�v���C�g
	Sprite::PreDraw();

	state->DrawTexture();
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
