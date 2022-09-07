#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "../Struct/Math/Vector3.h"

struct ConstBufferDataB1
{
	Math::Vector3 ambient; // アンビエント係数
	float pad1; // パディング
	Math::Vector3 diffuse; // ディフューズ係数
	float pad2; // パディング
	Math::Vector3 specular; // スペキュラー係数
	float alpha;	// アルファ
};