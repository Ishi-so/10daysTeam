#pragma once
#include "SceneState.h"

class Object3D;

class Title : public SceneState {
public:
	Title();	// コンストラクタ
	~Title();	// デストラクタ

	void Initialize()override;// 初期化
	void Update()override;// 更新
	void Draw()override;// 描画

private:// 変数
	Object3D* bgArray[3] = { nullptr,nullptr,nullptr };
	Object3D* boxArray[2] = { nullptr,nullptr };
	Object3D* clonePlayer = nullptr;
};