#include "DirectInput.h"

DirectInput* gDInput = 0;


DirectInput::DirectInput(HWND hWnd, HINSTANCE hInst)
{
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	ZeroMemory(&mMouseState, sizeof(mMouseState));

	DirectInput8Create(hInst, DIRECTINPUT_VERSION,
            IID_IDirectInput8, (void**)&mDInput, 0);

	mDInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, 0);
	mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	mKeyboard->SetCooperativeLevel(hWnd, 
								   DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

	mKeyboard->Acquire();
	
	mDInput->CreateDevice(GUID_SysMouse, &mMouse, 0);
	mMouse->SetDataFormat(&c_dfDIMouse2);
	mMouse->SetCooperativeLevel(hWnd, 
								   DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	
	mMouse->Acquire();

}


DirectInput::~DirectInput(void)
{
	ReleaseCOM(mDInput)

	mKeyboard->Unacquire();
	mMouse->Unacquire();

	ReleaseCOM(mKeyboard);
	ReleaseCOM(mMouse);
}


void DirectInput::poll()
{
	// Poll Keyboard
	ZeroMemory(mKeyboardState, sizeof(mKeyboardState));
	HRESULT hr = mKeyboard->GetDeviceState(sizeof(mKeyboardState),
										   (void**)&mKeyboardState);

	if(FAILED(hr))
	{
		// Keyboard lost, zero out keyboard data structure.
		ZeroMemory(mKeyboardState, sizeof(mKeyboardState));

		// Try to acquire for next time we poll.
		hr = mKeyboard->Acquire();
	}

		// Poll Mouse
	hr = mMouse->GetDeviceState(sizeof(mMouseState),
										   (void**)&mMouseState);

	if(FAILED(hr))
	{
		// Mouse lost, zero out Mouse data structure.
		ZeroMemory(&mMouseState, sizeof(mMouseState));

		// Try to acquire for next time we poll.
		hr = mMouse->Acquire();
	}

}

// Accessors
bool DirectInput::keyDown(short key)
{
      return (mKeyboardState[key] & 0x80) != 0;
}

bool DirectInput::mouseButtonDown(int button)
{
      return (mMouseState.rgbButtons[button] & 0x80) != 0;
}

float DirectInput::mouseDX()
{
      return (float)mMouseState.lX;
}

float DirectInput::mouseDY()
{
      return (float)mMouseState.lY;
}

float DirectInput::mouseDZ()
{
      return (float)mMouseState.lZ;
}
