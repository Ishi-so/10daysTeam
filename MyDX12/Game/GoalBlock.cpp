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
	// クラスネームのセット
	// クラスネーム取得
	const type_info& t_id = typeid(GoalBlock);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// 効果を設定
	ability = "Goal";

	// OBJクラスの生成
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_GOAL));
	color = { 1,1,1 };
	// ・・AABBの設定・・
	collisionData = Math::SetAABB(obj->position, obj->scale);
	// ---- 階層設定 ----
	stratum = Stratum::GetStratumData(pos.y)[0];
}

void GoalBlock::Update()
{
	// 当たり判定の設定
	collisionData = Math::SetAABB(pos, scale);
	// 座標とスケールの設定
	obj->position = pos;
	obj->scale = scale;
	obj->color = color;
	// 更新処理
	obj->Update();
}

void GoalBlock::Draw()
{
	// 描画
	obj->Draw();
}
