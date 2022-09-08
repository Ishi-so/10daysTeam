#pragma once
// プロトタイプ宣言
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
		// コンストラクタ
		Library();
		// デストラクタ
		~Library();
		// 初期化
		bool Initialize();
		// メッセージ
		bool Message();
		// 入力処理の更新
		void InputUpdate();

		// ゲーム部分
		void Play();
	};
}