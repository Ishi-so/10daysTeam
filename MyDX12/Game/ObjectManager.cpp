#include "ObjectManager.h"
#include "Player.h"
#include "../Struct/TypeCollision.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager(){}

void ObjectManager::DeadObject()
{
	auto removeIt = std::remove_if(mObjs.begin(), mObjs.end(), [&](std::shared_ptr<GameObj> itr)
		{
			return itr->GetIsActive() == false;
		}
	);

	mObjs.erase(removeIt, mObjs.end());
}

ObjectManager* ObjectManager::GetInstance()
{
	static ObjectManager instance;
	return &instance;
}

void ObjectManager::Initialize()
{
	
}

void ObjectManager::Update()
{
	for (auto& obj : mObjs)
	{
		obj->Update();
	}

	HitCheck();

	if (mAddObjs.size() != 0)
	{
		for (auto& m : mAddObjs)
		{
			m.get()->Update();
			mObjs.push_back(std::move(m));
		}

		mAddObjs.clear();
	}

	DeadObject();
}

void ObjectManager::Draw()
{
	for (auto& obj : mObjs)
	{
		obj->Draw();
	}
}

void ObjectManager::AddObject(const std::shared_ptr<GameObj>& upObject)
{
	upObject.get()->Init();
	mAddObjs.push_back(std::move(upObject));
}

void ObjectManager::AllDestroy()
{
	mObjs.clear();
}

void ObjectManager::HitCheck()
{
	std::vector<unsigned int> playerStratum = pPlayer->GetStratumData();
	
	// blockデータ全て
	for (auto& obj : mObjs) {
		// 階層が同じであれば
		PropValueCheck(obj, playerStratum[0]);

		// 2つ目の階層と1つ目の階層が同じなら次に行く
		if (playerStratum[0] == playerStratum[1])continue;

		// 2つ目の階層が同じであれば
		PropValueCheck(obj, playerStratum[1]);
	}
	
}

void ObjectManager::PropValueCheck(const std::shared_ptr<GameObj>& obj, const int stratum)
{
	if (obj->GetStratum() == stratum)
	{
		// 同じ階層とでしか当たり判定
		if (Math::HitCheck_AABB_Sphere(obj->GetCollisionData(), pPlayer->GetCollision())) {
			obj->SetColor({ 1, 0, 0 });
			pPlayer->HitUpdate();
		}
		else {
			obj->SetColor({ 1, 1, 1 });
		}
	}
}

