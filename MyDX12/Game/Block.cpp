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
	// クラスネームのセット
	// クラスネーム取得
	const type_info& t_id = typeid(Block);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJクラスの生成
	obj = Object3D::Create(Model::CreateFromOBJ("box_v000"));

	// ・・AABBの設定・・
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void Block::Update()
{
	// 当たり判定の設定
	collisionData = Math::SetAABB(pos, scale);
	// 座標とスケールの設定
	obj->position = pos;
	obj->scale = scale;
	// 更新処理
	obj->Update();
}

void Block::Draw()
{
	// 描画
	obj->Draw();
}
