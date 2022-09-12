#include "DamageBox.h"
#include "../3D/Object3D.h"
#include "Common.h"
#include "ModelLoader.h"

std::shared_ptr<DamageBox> DamageBox::Create(const Math::Vector3& _pos, const Math::Vector3& _scale)
{
	std::shared_ptr<DamageBox> damageBox = std::make_shared<DamageBox>();
	damageBox->Init();
	damageBox->SetPos(_pos);
	damageBox->SetScale(_scale);

	return std::move(damageBox);
}

DamageBox::DamageBox()
{
}

DamageBox::~DamageBox()
{
	delete obj;
	obj = nullptr;
}

void DamageBox::Init()
{
	// �N���X�l�[���̃Z�b�g
	// �N���X�l�[���擾
	const type_info& t_id = typeid(DamageBox);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJ�N���X�̐���
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_BLOCK));
	color = { 1,1,1 };
	// �E�EAABB�̐ݒ�E�E
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void DamageBox::Update()
{
	// �����蔻��̐ݒ�
	collisionData = Math::SetAABB(pos, scale);
	// ���W�ƃX�P�[���̐ݒ�
	obj->position = pos;
	obj->scale = scale;
	obj->color = color;
	// �X�V����
	obj->Update();
}

void DamageBox::Draw()
{
	// �`��
	obj->Draw();
}
