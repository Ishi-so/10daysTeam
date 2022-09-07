#include "Base/Library.h"
#include "Input/KeyInput.h"
#include <iostream>

// ターゲットがDebugの時
#ifdef _DEBUG
int main()
// ターゲットがDebugでない時
#else

// Windows アプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	XIIlib::Library* dxXii = nullptr;
	dxXii = new XIIlib::Library();
	dxXii->Initialize();

	while (true)
	{
		// メッセージ処理
		if (dxXii->Message()) { break; }

		// 入力処理 : 更新
		dxXii->InputUpdate();
		// ESC押したら抜ける
		if (XIIlib::KeyInput::GetInstance()->Trigger(DIK_ESCAPE))break;

		// 更新と描画
		dxXii->Play();
	}
	// 各種解放
	std::cout << "正常終了しました!!" << std::endl;
	delete dxXii;

	return 0;
}

// 比留間push