#pragma once
#include "SceneState.h"

class End : public SceneState {
public:
	End();	// �R���X�g���N�^
	~End();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�

};