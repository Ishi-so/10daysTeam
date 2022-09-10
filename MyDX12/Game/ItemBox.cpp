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
	// クラスネームのセット
	// クラスネーム取得
	const type_info& t_id = typeid(ItemBox);
	std::string path = t_id.name();
	id = Common::SeparateFilePath(path).second;

	// OBJクラスの生成
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_ITEM));
	Math::Vector3 tmpV = { 1,1,1 };
	color = tmpV;
	scale = tmpV * 0.5f;

	// ・・AABBの設定・・
	collisionData = Math::SetAABB(obj->position, obj->scale);
}

void ItemBox::Update()
{
	// 当たり判定の設定
	collisionData = Math::SetAABB(pos, scale);
	
	// 浮遊処理
	Floating();

	// 座標とスケールの設定
	//obj->position = pos;
	obj->scale = scale;
	obj->color = color;
	// 回転の設定
	obj->rotation.y += 1.5f;
	if (obj->rotation.y > 180.0f)obj->rotation.y = 0.0f;

	// 更新処理
	obj->Update();
}

void ItemBox::Draw()
{
	// 描画
	obj->Draw();
}

void ItemBox::Floating()
{
	if (!udSwitch) {// 上から下に
		const float moveY = pos.y + dist;// スタート位置
		// タイムから位置を算出
		float addPos = Easing::InOutCubic(moveTimer, 0.0f, dist * 2.0f, endTime);
		obj->position.y = moveY - addPos;

		// 時間を進ませる
		moveTimer += Common::constFrame;
		if (moveTimer >= endTime) {
			// 通れば切り替え
			moveTimer = 0.0f;
			udSwitch = true;
		}
	}
	else {// 下から上に
		const float moveY = pos.y - dist;// スタート位置
		// タイムから位置を算出
		float addPos = Easing::InOutCubic(moveTimer, 0.0f, dist * 2.0f, endTime);
		obj->position.y = moveY + addPos;

		// 時間を進ませる
		moveTimer += Common::constFrame;
		if (moveTimer >= endTime) {
			// 通れば切り替え
			moveTimer = 0.0f;
			udSwitch = false;
		}
	}
}
