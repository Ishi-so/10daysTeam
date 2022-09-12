#pragma once
#include <memory>
#include <vector>
#include "GameObj.h"

class Player;// �v���C���[

// �I�u�W�F�N�g�̊Ǘ��N���X
class ObjectManager {
private:
	ObjectManager();
	~ObjectManager();

	void DeadObject();// ���݂��Ă��Ȃ��I�u�W�F�N�g������
	
	std::vector<std::shared_ptr<GameObj>> mObjs;	// �Ǘ��I�u�W�F�N�g�R���e�i
	std::vector<std::shared_ptr<GameObj>> mAddObjs;// �ǉ����i�[�R���e�i

	Player* pPlayer = nullptr;
public:
	ObjectManager(const ObjectManager& obj) = delete;
	ObjectManager& operator = (const ObjectManager& obj) = delete;

	static ObjectManager* GetInstance();

	void Initialize(); // ������

	void Update(); // �X�V

	void Draw(); // �`��

	void AddObject(const std::shared_ptr<GameObj>& upObject); // ���j�b�g�̒ǉ�

	void AllDestroy();// �S�Ă��폜

	void SetPlayer(Player* p_player) { pPlayer = p_player; }// �v���C���[�̃f�[�^���R�s�[����

	void HitCheck();// ���菈��

	void PropValueCheck(const std::shared_ptr<GameObj>& obj,const int stratum);
};