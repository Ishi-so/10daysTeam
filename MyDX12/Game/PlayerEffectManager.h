#pragma once
#include <vector>
#include "../Struct/Math/Vector3.h"

class InstBill;

class PlayerEffectManager {
public:
	struct DataAset {
		Math::Vector3 position;
		Math::Vector3 vec;
		float addScale, scale, addColor, color, a;
	};
private:
	std::vector<DataAset> vcon;

	InstBill* iBill = nullptr;
public:
	static PlayerEffectManager* Create();

	PlayerEffectManager();
	~PlayerEffectManager();

	void Initialize();
	void Add(float c, float s, const Math::Vector3& v, const Math::Vector3& pos);
	void Update();
	void Draw();

	void AllClear();
};