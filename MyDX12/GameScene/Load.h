#pragma once
#include "SceneState.h"

class Load : public SceneState {
public:
	Load();	// �R���X�g���N�^
	~Load();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�
};