#pragma once
#include <vector>
#include "../Struct/Math/Vector3.h"
#include <memory>

class SphereEff;

class PlayerEffectManager {
private:
	std::vector<std::shared_ptr<SphereEff>> vcon;

public:
	static PlayerEffectManager* Create();

	PlayerEffectManager();
	~PlayerEffectManager();

	void Initialize();
	void Add(const Math::Vector3& v, const Math::Vector3& pos);
	void Update();
	void Draw();

	void AllClear();
};