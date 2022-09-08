#pragma once
#include "SceneState.h"

class End : public SceneState {
public:
	End();	// コンストラクタ
	~End();	// デストラクタ

	void Initialize()override;// 初期化
	void Update()override;// 更新
	void Draw()override;// 描画

private:// 変数

};