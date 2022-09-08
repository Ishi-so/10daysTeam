#pragma once

class GameScene;

class SceneState {
protected:
	SceneState() {}
public:
	// �R�s�[�֎~
	SceneState(const SceneState&) = delete;
	SceneState& operator=(const SceneState&) = delete;

	// ���z�f�X�g���N�^
	virtual ~SceneState() = default;
public: // �p��
	virtual void Initialize() = 0;// ������
	virtual void Update() = 0;//�@�X�V
	virtual void Draw() = 0;// �`��

public: // Setter�֐�
	void SetGameScene(GameScene* p_game_scene) { this->p_game_scene = p_game_scene; }
protected: // �ÓI�����o�ϐ�
	static GameScene* p_game_scene;

};