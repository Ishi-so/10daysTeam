#pragma once
#include "GameObj.h"
#include <memory>

class ItemBox : public GameObj {
public:
	// �����֐�
	static std::shared_ptr<ItemBox> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	ItemBox();	// �R���X�g���N�^
	~ItemBox();	//�f�X�g���N�^

	void Init()override;	// ������
	void Update()override;	// �X�V
	void Draw()override;	// �`��

private:// �ȉ��A�ŗL�ϐ�
	float moveTimer = 0.0f;
	bool udSwitch = false;
	static const float dist;
	static const float endTime;

private:
	void Floating();
};