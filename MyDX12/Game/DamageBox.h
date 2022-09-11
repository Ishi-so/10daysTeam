#pragma once
#include "GameObj.h"
#include <memory>

class DamageBox : public GameObj {
public:
	// �����֐�
	static std::shared_ptr<DamageBox> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	DamageBox();	// �R���X�g���N�^
	~DamageBox();	//�f�X�g���N�^

	void Init()override;	// ������
	void Update()override;	// �X�V
	void Draw()override;	// �`��

private:// �ȉ��A�ŗL�ϐ�

};