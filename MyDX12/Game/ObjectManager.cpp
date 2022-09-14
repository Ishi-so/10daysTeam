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
	// �q�b�g�`�F�b�N�J�E���g
	int hitcheckCnt = 0;
	// �v���C���[�̊K�w�f�[�^��ۑ�
	std::vector<unsigned int> playerStratum = pPlayer->GetStratumData();
	
	// block�f�[�^�S��
	for (auto& obj : mObjs) {

		// �f�t�H�J���[�ɐݒ�
		obj->SetColor({ 1, 1, 1 });

		// �K�w�������ł����
		PropValueCheck(obj, playerStratum[0],hitcheckCnt);

		// 2�ڂ̊K�w��1�ڂ̊K�w�������Ȃ玟�ɍs��
		if (playerStratum[0] == playerStratum[1])continue;

		// 2�ڂ̊K�w�������ł����
		PropValueCheck(obj, playerStratum[1],hitcheckCnt);
	}

	// �q�b�g�J�E���g��0�Ȃ��
	if (hitcheckCnt <= 0)
	{
		// �N�Ƃ��������Ă��Ȃ�
		pPlayer->SetHitFlag(false);
	}
}

void ObjectManager::PropValueCheck(const std::shared_ptr<GameObj>& obj, const int stratum, int& count)
{
	// �����K�w�Ƃł��������蔻��
	if (obj->GetStratum() == stratum)
	{
		// collision���m�ł̓����蔻��(AABB Sphere)
		if (Math::HitCheck_AABB_Sphere(obj->GetCollisionData(), pPlayer->GetCollision()))
		{
			// �F��ԐF�ɕύX
			obj->SetColor({ 1, 0, 0 });
			// �����������̌ŗL�֐�
			pPlayer->HitUpdate(obj->GetAbility());
			// �J�E���g
			count++;
		}
	}
}

