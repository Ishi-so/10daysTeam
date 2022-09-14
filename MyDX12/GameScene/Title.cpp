#include "Title.h"
#include "GameScene.h"
#include "../Tool/Messenger.h"
#include "Select.h"
#include "../Input/KeyInput.h"
#include "../3D/Object3D.h"
#include "../Game/ModelLoader.h"
#include "../Game/Common.h"

using namespace XIIlib;

Title::Title()
{
}

Title::~Title()
{
	delete clonePlayer;
	clonePlayer = nullptr;
	for (int i = 0; i < 12; i++) {
		delete boxArray[i];
		boxArray[i] = nullptr;
	}
	for (int i = 0; i < 3; i++) {
		delete bgArray[i];
		bgArray[i] = nullptr;
	}
}

void Title::Initialize()
{
	// �I�u�W�F�N�g�̏�����

	for (int i = 0; i < 3; i++) {
		bgArray[i] = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_BG));
		bgArray[i]->position = { 0,-37.2f,1 };
		bgArray[i]->scale = { 13.6f,13.6f,1.0f };
	}
	int yValue = 0;
	for (int i = 0; i < 12; i+=2) {// (1,13)
		// �{�b�N�X���w��̌���
		boxArray[i] = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_LONGBOX));
		boxArray[i + 1] = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_LONGBOX));
		boxArray[i]->position = {Common::ConvertPositionX(1),Common::ConvertTitlePositionY(yValue),0.0f};
		boxArray[i + 1]->position = {Common::ConvertPositionX(13),Common::ConvertTitlePositionY(yValue),0.0f};
		yValue++;
	}

	clonePlayer = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_PLAYER));
	const float cLine = 27.2f;
	bgArray[1]->position.y += cLine;
	bgArray[2]->position.y += cLine * 2;
	Messenger::GetInstance()->AddPrintOut("�^�C�g���V�[���ł��I");
}

void Title::Update()
{
	// �㉺+-37.2f�ŃJ�����O
	//bg0->position.y = -37;
	//std::cout << bg0->position.y << std::endl;
	for (int i = 0; i < 3; i++) {
		bgArray[i]->position.y += 0.6f;
		if (bgArray[i]->position.y >= 37.2f) {
			bgArray[i]->position.y = -37.2f;
		}
		bgArray[i]->Update();
	}

	for (int i = 0; i < 12; i++) {
		boxArray[i]->Update();
	}

	clonePlayer->rotation.z += 1.5f;
	clonePlayer->Update();
	// ��������؂�ւ�
	if (KeyInput::GetInstance()->Trigger(DIK_SPACE)) {
		p_game_scene->ChangeState(new Select());
	}
}

void Title::Draw()
{
	for (int i = 0; i < 3; i++) {
		bgArray[i]->Draw();
	}
	for (int i = 0; i < 12; i++) {
		boxArray[i]->Draw();
	}
	clonePlayer->Draw();
}
