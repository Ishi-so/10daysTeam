#pragma once
#include "GameObj.h"
#include <memory>

class GoalBlock : public GameObj {
public:
	// 生成関数
	static std::shared_ptr<GoalBlock> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);

	GoalBlock();	// コンストラクタ
	~GoalBlock();	//デストラクタ

	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Draw()override;	// 描画

private:// 以下、固有変数
};
