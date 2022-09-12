#include "PlayerEffectManager.h"
#include "InstBill.h"
#include <algorithm>

PlayerEffectManager::PlayerEffectManager() {}

PlayerEffectManager::~PlayerEffectManager()
{
	delete iBill;
}

PlayerEffectManager* PlayerEffectManager::Create()
{
	PlayerEffectManager* pPlayerEffectManager = new PlayerEffectManager();
	if (pPlayerEffectManager == nullptr) {
		return nullptr;
	}
	pPlayerEffectManager->Initialize();
	return pPlayerEffectManager;
}

void PlayerEffectManager::Initialize()
{
	//vcon.reserve(sizeof(DataAset) * 10);
	iBill = InstBill::Create("");
}

void PlayerEffectManager::Add(float c, float s, const Math::Vector3& v, const Math::Vector3& pos)
{
	float cR = static_cast<float>((rand() % 11)) / 10.0f;
	float cG = static_cast<float>((rand() % 11)) / 10.0f;
	float cB = static_cast<float>((rand() % 11)) / 10.0f;
	const float dColor = 255.0f;
	DataAset data = { pos,v,
		s,						// addScale
		0.1f,					// scale
		dColor * cR,dColor * cG,dColor * cB	// color
	};

	vcon.push_back(data);
}

void PlayerEffectManager::Update()
{
	if (vcon.size() == 0)return;
	for (auto& u : vcon) {
		u.position += u.vec;
		u.scale += u.addScale;
		u.color += u.addColor;
		u.a += -2.55f;
	}

	// アルファ値が0以下の物を排除
	auto removeIt = std::remove_if(vcon.begin(), vcon.end(), [](DataAset& itr)
		{
			return itr.a <= 25.5f * 5.0f;
		}
	);

	vcon.erase(removeIt, vcon.end());

	for (auto& u : vcon) {
		iBill->DrawBillBox(u.position, u.scale, u.color, u.color, u.color, u.a);
	}
}

void PlayerEffectManager::Draw()
{
	iBill->Update();

	InstBill::PreDraw();
	iBill->Draw();
	InstBill::PostDraw();
}

void PlayerEffectManager::AllClear()
{
	if (vcon.size() == 0)return;
	vcon.clear();
}
