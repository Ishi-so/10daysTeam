#include "Block.h"
#include "../3D/Object3D.h"
#include "Common.h"

std::shared_ptr<Block> Block::Create(const Math::Vector3& _pos, const Math::Vector3& _scale)
{
	std::shared_ptr<Block> block = std::make_shared<Block>();
	block->Init();
	block->SetPos(_pos);
	block->SetScale(_scale);

	return std::move(block);
}

Block::Block()
{
}

Block::~Block()
{
	delete obj;
	obj = nullptr;
}

void Block::Init()
{
	// �N���X�l�[���̃Z�b�g
	// �N���X�l�[���擾
	const type_info& t_id = typeid(Block);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJ�N���X�̐���
	obj = Object3D::Create(Model::CreateFromOBJ("box_v000"));

	// �E�EAABB�̐ݒ�E�E
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void Block::Update()
{
	// �����蔻��̐ݒ�
	collisionData = Math::SetAABB(pos, scale);
	// ���W�ƃX�P�[���̐ݒ�
	obj->position = pos;
	obj->scale = scale;
	// �X�V����
	obj->Update();
}

void Block::Draw()
{
	// �`��
	obj->Draw();
}
