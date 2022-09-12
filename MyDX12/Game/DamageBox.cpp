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
	// クラスネームのセット
	// クラスネーム取得
	const type_info& t_id = typeid(DamageBox);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJクラスの生成
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_BLOCK));
	color = { 1,1,1 };
	// ・・AABBの設定・・
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void DamageBox::Update()
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

void DamageBox::Draw()
{
	// 描画
	obj->Draw();
}
