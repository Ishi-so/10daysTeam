#pragma once
#include "SceneState.h"

class Play : public SceneState {
public:
	Play();	// �R���X�g���N�^
	~Play();	// �f�X�g���N�^

	void Initialize()override;// ������
	void Update()override;// �X�V
	void Draw()override;// �`��

private:// �ϐ�

};
