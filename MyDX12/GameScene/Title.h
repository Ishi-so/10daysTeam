#pragma once
#include "SceneState.h"

class Object3D;

class Title : public SceneState {
public:
	Title();	// �R���X�g���N�^
	~Title();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�
	Object3D* bgArray[3] = { nullptr,nullptr,nullptr };
	Object3D* boxArray[2] = { nullptr,nullptr };
	Object3D* clonePlayer = nullptr;
};