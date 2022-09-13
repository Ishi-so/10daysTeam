#include "PlayerEffectManager.h"
#include "SphereEff.h"
#include <algorithm>

PlayerEffectManager::PlayerEffectManager() {}

PlayerEffectManager::~PlayerEffectManager()
{
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
	vcon.reserve(sizeof(SphereEff*) * 100);
}

void PlayerEffectManager::Add(const Math::Vector3& v, const Math::Vector3& pos)
{
	vcon.push_back(std::make_shared<SphereEff>(pos, v));
}

void PlayerEffectManager::Update()
{
	if (vcon.size() == 0)return;
	for (auto& u : vcon) {
		u->Update();
	}

	// アルファ値が0以下の物を排除
	auto removeIt = std::remove_if(vcon.begin(), vcon.end(), [](std::shared_ptr<SphereEff>& itr)
		{
			return itr->GetAlpha() <= 0.5f;
		}
	);

	vcon.erase(removeIt, vcon.end());
}

void PlayerEffectManager::Draw()
{
	for (auto& u : vcon) {
		u->Draw();
	}
}

void PlayerEffectManager::AllClear()
{
	if (vcon.size() == 0)return;
	vcon.clear();
}
