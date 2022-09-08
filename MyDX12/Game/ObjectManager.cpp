#include "ObjectManager.h"

ObjectManager::ObjectManager(){}

ObjectManager::~ObjectManager(){}

void ObjectManager::DeadUnit()
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

	if (mAddObjs.size() != 0)
	{
		for (auto& m : mAddObjs)
		{
			m.get()->Update();
			mObjs.push_back(std::move(m));
		}

		mAddObjs.clear();
	}
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

