#include "GoalBlock.h"
#include "../3D/Object3D.h"
#include "Common.h"
#include "ModelLoader.h"
#include "Stratum.h"

std::shared_ptr<GoalBlock> GoalBlock::Create(const Math::Vector3& _pos, const Math::Vector3& _scale)
{
	std::shared_ptr<GoalBlock> goal = std::make_shared<GoalBlock>();
	goal->SetPos(_pos);
	goal->SetScale(_scale);
	goal->Init();

	return std::move(goal);
}

GoalBlock::GoalBlock()
{
}

GoalBlock::~GoalBlock()
{
	delete obj;
	obj = nullptr;
}

void GoalBlock::Init()
{
	// �N���X�l�[���̃Z�b�g
	// �N���X�l�[���擾
	const type_info& t_id = typeid(GoalBlock);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// ���ʂ�ݒ�
	ability = "Goal";

	// OBJ�N���X�̐���
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_GOAL));
	color = { 1,1,1 };
	// �E�EAABB�̐ݒ�E�E
	collisionData = Math::SetAABB(obj->position, obj->scale);
	// ---- �K�w�ݒ� ----
	stratum = Stratum::GetStratumData(pos.y)[0];
}

void GoalBlock::Update()
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

void GoalBlock::Draw()
{
	// �`��
	obj->Draw();
}
