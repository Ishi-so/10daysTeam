#pragma once
#include "../Struct/Math/Vector3.h"
class Object3D;

class SphereEff {
private:
	Math::Vector3 position;
	Math::Vector3 vec;
	float addScale, scale, a;

	Object3D* obj = nullptr;
public:
	SphereEff(const Math::Vector3& pos, const Math::Vector3& _vec);
	~SphereEff();

	void Update();

	void Draw();

	float GetAlpha()const { return a; }
};