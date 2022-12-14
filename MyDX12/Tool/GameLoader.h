#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../Struct/Math.h"
#include "../Struct/Math/Vector3.h"

namespace XIIlib
{
	struct ObjectInfomations
	{
		std::string className;
		std::string objName;
		std::string tagName;
		std::string individual;

		std::string modelName;

		Math::Vector3 pos;
		Math::Vector3 scl;
		Math::Vector3 rot;

		Math::Vector3 base;
		float metalness;
		float roughness;
		float specular;

		unsigned int hitpoint;
		unsigned int doorColor;
		unsigned int itemID;
	};

	class GameLoader
	{
	public: // 関数
		GameLoader();
		~GameLoader(){}

		// 読み込み
		void LoadFile(const std::string& filename);
		unsigned int GetOJBSize()const;
		ObjectInfomations GetObjects(int index)const;
		void ReadClear();

	private: // 変数
		unsigned int objSize;
		std::vector<ObjectInfomations> read_data;
	};
}