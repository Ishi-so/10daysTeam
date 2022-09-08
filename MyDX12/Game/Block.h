#pragma once
#include "GameObj.h"

class Block : public GameObj {
public:
	Block();
	~Block();

	void Init()override;	// 初期化
	void Update()override;	// 更新
	void Draw()override;	// 描画

private:// 以下、固有変数


};