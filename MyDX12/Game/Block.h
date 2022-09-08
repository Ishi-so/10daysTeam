#pragma once
#include "GameObj.h"
#include <memory>

class Block : public GameObj {
public:
	static std::shared_ptr<Block> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	Block();
	~Block();

	void Init()override;	// ������
	void Update()override;	// �X�V
	void Draw()override;	// �`��

private:// �ȉ��A�ŗL�ϐ�


};