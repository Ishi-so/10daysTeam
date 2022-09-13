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
	// �E�B���h�E�̐���
	w_app = new WindowsApp();
	w_app->GenerateWindow();
	//DirectX����������
	dx12 = new DirectX12();
	dx12->Initialize(w_app);
	// Input������
	keyInput = KeyInput::GetInstance();
	keyInput->Initialize(w_app->GetInstance(), w_app->GetWinHandle());

	// ���̑��ėp�N���X�̏�����
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
	// �Q�[���̍X�V����
	gameScene->Update();

	// �`��J�n
	dx12->Previous();
	// �Q�[���̕`�揈��
	gameScene->Draw();
	// �`��I��
	dx12->PostProcessing();
}
