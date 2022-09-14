#pragma once
#include "GameObj.h"
#include <memory>

class GoalBlock : public GameObj {
public:
	// �����֐�
	static std::shared_ptr<GoalBlock> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	GoalBlock();	// �R���X�g���N�^
	~GoalBlock();	//�f�X�g���N�^

	void Init()override;	// ������
	void Update()override;	// �X�V
	void Draw()override;	// �`��

private:// �ȉ��A�ŗL�ϐ�
};
