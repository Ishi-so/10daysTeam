#include "ControllerInput.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace XIIlib;
const float ControllerInput::StickHalf = 16383.5f;
const float ControllerInput::StickCount = 32767.0f;
const float ControllerInput::StickMax = 65535.0f;


ControllerInput* ControllerInput::GetInstance()
{
	static ControllerInput instance;

	return &instance;
}

bool ControllerInput::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̐���
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);

	if (devJoystick != nullptr)
	{
		// �R���g���[���[�f�o�C�X�̐���	
		result = dinput->CreateDevice(GUID_Joystick, &devJoystick, NULL);

		// ���̓f�[�^�`���̃Z�b�g
		result = devJoystick->SetDataFormat(&c_dfDIJoystick); // �W���`��

		// �r�����䃌�x���̃Z�b�g
		result = devJoystick->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);

		// �f�o�C�X�̔\�͂��擾
		result = devJoystick->GetCapabilities(&diDevCaps);
	}

	return true;
}

void ControllerInput::Update()
{
	HRESULT result;

	{// �W���C�X�e�B�b�N(�R���g���[���[)
		if (devJoystick != nullptr)
		{
			result = devJoystick->Acquire();

			// �O��̓��͏���ۑ�
			joyStatePre = joyState;

			// �W���C�X�e�B�b�N�̓���
			result = devJoystick->GetDeviceState(sizeof(joyState), &joyState);
		}
	}
}

XIIlib::JoystickInput ControllerInput::GetJoystickData()
{
	JoystickInput inp;
	inp.lX = joyState.lX;
	inp.lY = joyState.lY;
	inp.rX = joyState.lZ;
	inp.rY = joyState.lRz;

	inp.cS = joyState.rgdwPOV[0];// 0��,90��,180��,270��
	return inp;
}

bool ControllerInput::PushJoyStick(int index)
{
	// 0�łȂ���Ή����Ă���
	if (joyState.rgbButtons[index] & 0x80)
	{
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool ControllerInput::TriggerJoyStick(int index)
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!joyStatePre.rgbButtons[index] && joyState.rgbButtons[index])
	{
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}