#pragma once
#include <string>

namespace Common {
	static float posStartX = -14.0f,posStartY = 0.0f;
	static float posDistance = 2.0f;

	// クラスネームの取り出し関数
	std::pair<std::string, std::string> SeparateFilePath(const std::string& path);

	// 要素数を素に位置座標を取得
	float ConvertPositionX(int point);// X座標
	float ConvertPositionY(int point);// Y座標
}