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

	// player�̐���
	m_player = Player::Create();

	state->SetGameScene(this);
	state->SetPlayer(m_player);
	state->Initialize();

	ObjectManager::GetInstance()->Initialize();

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

	static_cast<Object3D*>(objectA)->position = {0,0,-2.0f};
	static_cast<Object3D*>(objectA)->scale = {2,2,2};
	static_cast<Object3D*>(objectA)->alpha = 0.7f;
	static_cast<Object3D*>(objectA)->rotation.z = 90.0f;
	//static_cast<Object3D*>(objectA)->color = {1,0,0};

	static_cast<Object3D*>(objectB)->position = {0.0f,0,2.0f};

	static_cast<Object3D*>(objectA)->Update();
	static_cast<Object3D*>(objectB)->Update();

	// A�͓��߃I�u�W�F�N�g�AB�͕s�����I�u�W�F�N�g
	// Z�o�b�t�@�̊֌W�ŉ������ɕ`�悳���
	// ���̂��ߖ{���͂��̂܂܂ł����̂���
	// ���߃I�u�W�F�N�g�͌�ɕ`�悵�Ȃ���΂Ȃ�Ȃ�
	// ������������邽�߂�Z�̍��W�Ŕ��ʂ���̂ł͂Ȃ�
	// �f�v�X�l�Ŕ��ʂ��Ȃ���΂Ȃ�Ȃ�
	// �菇�Ƃ��āA�A���t�@�l��1�ł��邩�ǂ����̔��ʂ�����
	// ���ʏo������s�������ɕ`�悳����
	// ���̌�c���`�悳����̂�������
	// �`�揇�ɂ����Ă������ȓ_������ꍇ�̓f�v�X�n�Ŕ���

	// ���̃t�B���^(IF:�A���t�@�l)

	// ���̃t�B���^(IF�F�f�v�X�l(Z�l))
	circle->DrawCircle(300,300,100,255, 255, 255, 255);

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
	//static_cast<Object3D*>(objectB)->Draw();
	m_player->Draw(); // SceneState�h���̃N���X�ł��(���͉��u��)
	//static_cast<Object3D*>(objectA)->Draw();

	ObjectManager::GetInstance()->Draw();
	Object3D::PostDraw();

	state->Draw();

	// ImGui�̕`��

	// �O�i�X�v���C�g

	// �����X�v���C�g
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
