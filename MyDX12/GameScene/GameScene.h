#pragma once
#include "../Struct/Math/Vector3.h"
#include <vector>

class DebugCamera;
class LightGroup;
class Circle;
class Tessellation;
class SceneState;
class Player; // ��

class GameScene {
private:// �ÓI�����o
	static const int debugTextTexNumber = 0;
	static const int debugJISTextTexNumber = 1;

private:// �����o
	LightGroup* lightGroup = nullptr;
	DebugCamera* d_camera = nullptr;
	SceneState* state = nullptr;// Scene
	
	Math::Vector3 cameraPos;
	float cameRad = 0.0f;

	Circle* circle = nullptr;

	// Game�n
	Player* m_player = nullptr;// �v���C���[�N���X
	std::vector<std::vector<int>>mapData = {};

public:
	static GameScene* Create();

	GameScene();
	~GameScene();

	bool Initialize();// ������

	void Update();// �X�V

	void Draw();// �`��

	void ChangeState(SceneState* different_state);// �V�[���̐؂�ւ�
};