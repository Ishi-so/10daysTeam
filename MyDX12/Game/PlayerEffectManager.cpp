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
	vcon.reserve(sizeof(DataAset) * 100);
	iBill = InstBill::Create("");
}

void PlayerEffectManager::Add(const Math::Vector3& v, const Math::Vector3& pos)
{
	float cR = static_cast<float>((rand() % 11)) / 10.0f;
	float cG = static_cast<float>((rand() % 11)) / 10.0f;
	float cB = static_cast<float>((rand() % 11)) / 10.0f;
	const float dColor = 255.0f;
	DataAset data = { pos,v,
		{cR * dColor,cG * dColor,cB * dColor},				// color
		0.04f,						// addScale
		0.1f,					// scale
		255.0f					// alpha
	};

	vcon.push_back(data);
}

void PlayerEffectManager::Update()
{
	if (vcon.size() == 0)return;
	for (auto& u : vcon) {
		u.position += u.vec;
		u.scale += u.addScale;
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
		iBill->DrawBillBox(u.position, u.scale, u.color.x, u.color.y, u.color.z, u.a);
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
