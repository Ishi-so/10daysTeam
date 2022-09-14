#include "SphereEff.h"
#include "../3D/Object3D.h"
#include "ModelLoader.h"

SphereEff::SphereEff(const Math::Vector3& pos, const Math::Vector3& _vec)
{
	// オブジェクトの初期化
	obj = Object3D::Create(ModelLoader::GetInstance()->GetModel(MODEL_PLAYER));
	obj->position = pos;
	position = pos;
	vec = _vec;
	scale = 1.0f;
	Math::Vector3 rColor = {
		static_cast<float>((rand() % 11)) / 10.0f,
		static_cast<float>((rand() % 11)) / 10.0f,
		static_cast<float>((rand() % 11)) / 10.0f
	};
	obj->color = rColor;
	a = 1.0f;
	obj->alpha = a;
}

SphereEff::~SphereEff()
{
	delete obj;
	obj = nullptr;
}

void SphereEff::Update()
{
	position -= vec;
	a -= 0.01f;
	obj->position = position;
	obj->scale = { scale,scale ,scale };
	obj->rotation.z += 1.5f;
	obj->alpha = a;
	obj->Update();
}

void SphereEff::Draw()
{
	obj->Draw();
}
