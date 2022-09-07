#pragma once
#include "../Struct/Math/Matrix4.h"
#include "../Struct/Math/Vector3.h"
#include "../Struct/Math/Vector4.h"

struct ConstBufferDataB0
{
	//XMMATRIX mat;	// ３Ｄ変換行列
	Math::Vector4 color;
	Math::Matrix4 viewproj;	// ビュ―プロジェクション行列
	Math::Matrix4 world;		// ワールド行列
	Math::Vector3 cameraPos;	// カメラ座標(ワールド座標)

	Math::Vector4 lightpos;
	Math::Matrix4 wlp;
	Math::Matrix4 wlpt;
	Math::Vector3 pd;

	float _time;					// シェーダー内部で使うタイマー
	float isElec;					// シェーダータイプ
};