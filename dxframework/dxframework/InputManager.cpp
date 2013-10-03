#include "InputManager.h"


InputManager::InputManager(void)
{
	dInput = NULL;
	mouseDevice = NULL;
	keyboardDevice = NULL;

	// Zero Fill the keyPressState
	// used to record keypresses
	for (int i = 0; i < 256; i++){
		keyPressState[i] = 0;
	}
}

InputManager::~InputManager(void)
{
	if (dInput) 
    { 
        if (mouseDevice) 
        { 
            mouseDevice->Unacquire(); 
            mouseDevice->Release();
            mouseDevice = NULL; 
        }
		if (keyboardDevice){
			keyboardDevice->Unacquire(); 
            keyboardDevice->Release();
            keyboardDevice = NULL; 
		}
        dInput->Release();
        dInput = NULL; 
    } 
}

bool InputManager::init(HINSTANCE hInst, HWND wndHandle)
{
	HRESULT hr;

	// Create a direct input object

    hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, 
                            IID_IDirectInput8, (void**)&dInput, NULL); 

	if FAILED(hr){ 
		return FALSE;
	}

    // Create a device for monitoring the mouse
    if FAILED(dInput->CreateDevice(GUID_SysMouse, &mouseDevice, NULL))
		return FALSE; 
	if FAILED(mouseDevice->SetDataFormat(&c_dfDIMouse))
		return FALSE; 
	

    if FAILED(mouseDevice->SetCooperativeLevel(wndHandle, DISCL_FOREGROUND | DISCL_EXCLUSIVE)) 
        return FALSE; 
		
    //if FAILED(mouseDevice->Acquire())
    //    return FALSE; 

	// Create a device for monitoring the keyboard
	if (FAILED(dInput->CreateDevice(GUID_SysKeyboard, &keyboardDevice, NULL)))
		return false;
	if (FAILED(keyboardDevice->SetDataFormat(&c_dfDIKeyboard)))
		return false;
	if (FAILED(keyboardDevice->SetCooperativeLevel(wndHandle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return false;
	if (FAILED(keyboardDevice->Acquire()))
		return false;

	return true;
}

void InputManager::getInput()
{
	HRESULT hr;

	hr = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE),(LPVOID)&mouseState); 
	if (FAILED (hr))
	{
		// try and reacquire the input device
		mouseDevice->Acquire();
	}

	keyboardDevice->GetDeviceState(sizeof(UCHAR[256]), (LPVOID)keyState);
	if (FAILED (hr))
	{
		// try and reacquire the input device
		keyboardDevice->Acquire();
	}
}

int InputManager::getMouseMovingX() 
{
	return mouseState.lX; 
}

int InputManager::getMouseMovingY() 
{
	return mouseState.lY; 
}

bool InputManager::isButtonDown(int button)
{
	//check the state of the button
	if (mouseState.rgbButtons[button] & 0x80){
		return true;
	} else {
		return false;
	}
}

bool InputManager::keyDown(DWORD key)
{
	//check the state of the key
	if (keyState[key] & 0x80){
		return true;
	} else {
		return false;
	}
}

bool InputManager::keyUp(DWORD key)
{
	//check the state of the key
	if (keyState[key] & 0x80){
		return false;
	} else {
		return true;
	}
}

bool InputManager::keyPress(DWORD key)
{

	//check for keydown
	if (keyDown(key))
	{
		keyPressState[key] = 1;
	}

	//check for key reaching the keydown state
	if (keyPressState[key] == 1)
	{
		//check for key release
		if (keyUp(key))
			keyPressState[key] = 2;
	}

	//check if key has been pressed and released
	if (keyPressState[key] == 2)
	{
		//reset the key status
		keyPressState[key] = 0;
		return true;
	}
	
	return false;
}
