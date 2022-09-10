#include "ItemBox.h"
#include "../3D/Object3D.h"
#include "Common.h"
#include "ModelLoader.h"
#include "../Tool/Easing.h"

const float ItemBox::dist = 0.5f;
const float ItemBox::endTime = 1.5f;

std::shared_ptr<ItemBox> ItemBox::Create(const Math::Vector3& _pos, const Math::Vector3& _scale)
{
	std::shared_ptr<ItemBox> itemBox = std::make_shared<ItemBox>();
	itemBox->Init();
	itemBox->SetPos(_pos);
	itemBox->SetScale(_scale);

	return std::move(itemBox);
}

ItemBox::ItemBox()
{
}

ItemBox::~ItemBox()
{
	delete obj;
	obj = nullptr;
}

void ItemBox::Init()
{
	// �N���X�l�[���̃Z�b�g
	// �N���X�l�[���擾
	const type_info& t_id = typeid(ItemBox);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJ�N���X�̐���
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_ITEM));
	Math::Vector3 tmpV = { 1,1,1 };
	color = tmpV;
	scale = tmpV * 0.5f;

	// �E�EAABB�̐ݒ�E�E
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void ItemBox::Update()
{
	// �����蔻��̐ݒ�
	collisionData = Math::SetAABB(pos, scale);
	
	// ���V����
	Floating();

	// ���W�ƃX�P�[���̐ݒ�
	//obj->position = pos;
	obj->scale = scale;
	obj->color = color;
	// ��]�̐ݒ�
	obj->rotation.y += 1.5f;
	if (obj->rotation.y > 180.0f)obj->rotation.y = 0.0f;

	// �X�V����
	obj->Update();
}

void ItemBox::Draw()
{
	// �`��
	obj->Draw();
}

void ItemBox::Floating()
{
	if (!udSwitch) {// �ォ�牺��
		const float moveY = pos.y + dist;// �X�^�[�g�ʒu
		// �^�C������ʒu���Z�o
		float addPos = Easing::InOutCubic(moveTimer, 0.0f, dist * 2.0f, endTime);
		obj->position.y = moveY - addPos;

		// ���Ԃ�i�܂���
		moveTimer += Common::constFrame;
		if (moveTimer >= endTime) {
			// �ʂ�ΐ؂�ւ�
			moveTimer = 0.0f;
			udSwitch = true;
		}
	}
	else {// ��������
		const float moveY = pos.y - dist;// �X�^�[�g�ʒu
		// �^�C������ʒu���Z�o
		float addPos = Easing::InOutCubic(moveTimer, 0.0f, dist * 2.0f, endTime);
		obj->position.y = moveY + addPos;

		// ���Ԃ�i�܂���
		moveTimer += Common::constFrame;
		if (moveTimer >= endTime) {
			// �ʂ�ΐ؂�ւ�
			moveTimer = 0.0f;
			udSwitch = false;
		}
	}
}
