#pragma once
#include "GameObj.h"
#include <memory>

class Block : public GameObj {
public:
	// 生成関数
	static std::shared_ptr<Block> Create(const Math::Vector3& _pos, const Math::Vector3& _scale);
	
	Block();	// コンストラクタ
	~Block();	//デストラクタ

	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Draw()override;	// 描画

private:// 以下、固有変数
};