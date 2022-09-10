#pragma once
#include "GameObj.h"
#include <memory>

class ItemBox : public GameObj {
public:
	// 生成関数
	static std::shared_ptr<ItemBox> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	ItemBox();	// コンストラクタ
	~ItemBox();	//デストラクタ

	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Draw()override;	// 描画

private:// 以下、固有変数
	float moveTimer = 0.0f;
	bool udSwitch = false;
	static const float dist;
	static const float endTime;

private:
	void Floating();
};