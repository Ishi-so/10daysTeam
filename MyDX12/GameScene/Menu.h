#pragma once
#include "SceneState.h"

class Menu : public SceneState {
public:
	Menu();	// �R���X�g���N�^
	~Menu();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�

};
