#include "Base/Library.h"
#include "Input/KeyInput.h"
#include <iostream>

// �^�[�Q�b�g��Debug�̎�
#ifdef _DEBUG
int main()
// �^�[�Q�b�g��Debug�łȂ���
#else

// Windows �A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	XIIlib::Library* dxXii = nullptr;
	dxXii = new XIIlib::Library();
	dxXii->Initialize();

	while (true)
	{
		// ���b�Z�[�W����
		if (dxXii->Message()) { break; }

		// ���͏��� : �X�V
		dxXii->InputUpdate();
		// ESC�������甲����
		if (XIIlib::KeyInput::GetInstance()->Trigger(DIK_ESCAPE))break;

		// �X�V�ƕ`��
		dxXii->Play();
	}
	// �e����
	std::cout << "����I�����܂���!!" << std::endl;
	delete dxXii;

	return 0;
}

// �䗯��push