#pragma once
#include "GameObj.h"

class Block : public GameObj {
public:
	Block();
	~Block();

	void Init()override;	// ������
	void Update()override;	// �X�V
	void Draw()override;	// �`��

private:// �ȉ��A�ŗL�ϐ�


};