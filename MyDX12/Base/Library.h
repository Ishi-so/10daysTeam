#pragma once
// �v���g�^�C�v�錾
class WindowsApp;
class DirectX12;
class Sound;
class GameScene;

namespace XIIlib
{
	class KeyInput;

	class Library
	{
	private:
		WindowsApp* w_app;
		DirectX12* dx12;
		KeyInput* keyInput;
		GameScene* gameScene = nullptr;

	public:
		// �R���X�g���N�^
		Library();
		// �f�X�g���N�^
		~Library();
		// ������
		bool Initialize();
		// ���b�Z�[�W
		bool Message();
		// ���͏����̍X�V
		void InputUpdate();

		// �Q�[������
		void Play();
	};
}