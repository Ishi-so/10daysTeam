#pragma once
#include "SceneState.h"

class Select : public SceneState {
public:
	Select();	// �R���X�g���N�^
	~Select();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�

};