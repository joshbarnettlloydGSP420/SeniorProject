#include "InputManager.h"

InputManager* InputManager::Controller = NULL;

InputManager* InputManager::GetInputManager()
{
	if( Controller )
		return Controller;
	else
	{
		Controller = new InputManager();
		return Controller;
	}
}

BOOL CALLBACK enumCallBack( const DIDEVICEINSTANCE* instance, VOID* context )
{
	HRESULT hr;

	InputManager* t_input = InputManager::GetInputManager();

	hr = t_input->dInput->CreateDevice( instance->guidInstance,
		&(t_input->gamepad), NULL );

	if( FAILED( hr ) )
		return DIENUM_CONTINUE;

	return DIENUM_STOP;
}

BOOL CALLBACK enumAxesCallback( const DIDEVICEOBJECTINSTANCE* instance, VOID* context )
{
	HWND hDlg = (HWND)context;

	DIPROPRANGE propRange;
	propRange.diph.dwSize		= sizeof(DIPROPRANGE);
	propRange.diph.dwHeaderSize	= sizeof(DIPROPHEADER);
	propRange.diph.dwHow		= DIPH_BYID;
	propRange.diph.dwObj		= instance->dwType;
	propRange.lMin				= -100;
	propRange.lMax				= +100;

	InputManager* t_input = InputManager::GetInputManager();
	if( FAILED( t_input->gamepad->SetProperty(
		DIPROP_RANGE, &propRange.diph ) ) )
		return DIENUM_STOP;

	return DIENUM_CONTINUE;
}

//keyboard/mouse methods=======================================================
//=============================================================================

void InputManager::Init( HWND* hWnd, HINSTANCE* hInst )
{
	SetCursorPos( 0, 0 );
	MouseX = 0;
	MouseY = 0;
	keyboard = NULL;
	mouse = NULL;
	dInput = NULL;
	gamepad = NULL;
	ZeroMemory( &gamepadState, sizeof(gamepadState) );
	gamepadState.rgdwPOV[0] = -1;
	deadZone = 25;

	//xTriggerDeadZone = 50;

	DirectInput8Create( (*hInst), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&dInput, NULL );

	dInput->CreateDevice( GUID_SysKeyboard, &keyboard, NULL );
	keyboard->SetCooperativeLevel( (*hWnd), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	keyboard->SetDataFormat( &c_dfDIKeyboard );

	dInput->CreateDevice( GUID_SysMouse, &mouse, NULL );
	mouse->SetCooperativeLevel( (*hWnd), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
	mouse->SetDataFormat( &c_dfDIMouse2 );

	RECT r;
	GetWindowRect( *hWnd, &r );
	ScreenWidth = (short)(r.right - r.left);
	ScreenHeight = (short)(r.bottom - r.top);

	keyboard->Acquire();
	mouse->Acquire();
}

void InputManager::Update()
{
	HRESULT result;
	ZeroMemory( buffer, sizeof(buffer) );

	result = keyboard->GetDeviceState( sizeof(buffer), (LPVOID)&buffer );
	if( FAILED( result ) )
	{
		result = keyboard->Acquire();
		while( result == DIERR_INPUTLOST )
			result = keyboard->Acquire();

		if( SUCCEEDED( result ) )
			keyboard->GetDeviceState( sizeof(buffer), buffer );
	}

	ZeroMemory( &mouseState, sizeof(mouseState) );

	result = mouse->GetDeviceState( sizeof(DIMOUSESTATE2), &mouseState );
	if( FAILED( result ) )
	{
		result = mouse->Acquire();
		while( result == DIERR_INPUTLOST )
			result = mouse->Acquire();

		if( SUCCEEDED( result ) )
		{
			mouse->GetDeviceState( sizeof(DIMOUSESTATE2), &mouseState );
		}
	}

	MouseX += mouseState.lX;
	MouseY += mouseState.lY;

	if( MouseX < 0 ) MouseX = 0;
	if( MouseX > ScreenWidth ) MouseX = ScreenWidth;
	if( MouseY < 0 ) MouseY = 0;
	if( MouseY > ScreenHeight ) MouseY = ScreenHeight;

	for( byte i = 0; i < 4; ++i )
		UpdateXboxController( i );
}

bool InputManager::CheckKeyboardKey( short key )
{
	if( buffer[key] & 0x80 ) 
		return true;
	else
		return false;
}

bool InputManager::CheckKeyboardBufferedKey( short key )
{
	if( CheckKeyboardKey( key ) )
	{
		if( !isPressed[key] )
		{
			isPressed[key] = true;
			return true;
		}else
		{
			return false;
		}
	}else
	{
		isPressed[key] = false;
		return false;
	}
}

bool InputManager::CheckMouseButton( short button )
{
	if( mouseState.rgbButtons[button] & 0x80 )
		return true;
	else
		return false;
}

bool InputManager::CheckMouseBufferedButton( short button )
{
	if( CheckMouseButton( button ) )
	{
		if( !mousePressed[button] )
		{
			mousePressed[button] = true;
			return true;
		}else
		{
			return false;
		}
	}else
	{
		mousePressed[button] = false;
		return false;
	}
}

int  InputManager::CheckMouseMoveX()
{
	return mouseState.lX;
}

int  InputManager::CheckMouseMoveY()
{
	return mouseState.lY;
}

int  InputManager::CheckMouseScroll()
{
	return mouseState.lZ;
}

int  InputManager::GetMousePosX()
{
	return MouseX;
}

int  InputManager::GetMousePosY()
{
	return MouseY;
}

void InputManager::Shutdown()
{
	if( mouse )
	{
		mouse->Unacquire();
		mouse->Release();
		mouse = NULL;
	}
	
	if( keyboard )
	{
		keyboard->Unacquire();
		keyboard->Release();
		keyboard = NULL;
	}

	if( dInput )
	{
		dInput->Release();
		dInput = NULL;
	}

	delete Controller;
}

//Gamepad Methods==============================================================
//=============================================================================
//
//bool InputManager::InitGamepad( HWND* hWnd )
//{
//	HRESULT hr;
//
//	gamepad = NULL;
//	ZeroMemory( &gamepadState, sizeof(gamepadState) );
//	gamepadState.rgdwPOV[0] = -1;
//
//	if( FAILED( hr = dInput->EnumDevices( DI8DEVCLASS_GAMECTRL,
//		enumCallBack, NULL, DIEDFL_ATTACHEDONLY ) ) )
//		return false;
//
//	if( gamepad == NULL )
//		return false;
//
//	if( FAILED( hr = gamepad->SetDataFormat( &c_dfDIJoystick2 ) ) )
//		return false;
//
//	if( FAILED( hr = gamepad->SetCooperativeLevel( (*hWnd),
//		DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
//		return false;
//
//	DIDEVCAPS capabilities;
//	capabilities.dwSize = sizeof( DIDEVCAPS );
//	if( FAILED( hr = gamepad->GetCapabilities( &capabilities ) ) )
//		return false;
//
//	if( FAILED( hr = gamepad->EnumObjects( enumAxesCallback,
//		NULL, DIDFT_AXIS ) ) )
//		return false;
//
//	return true;
//}
//
//HRESULT InputManager::UpdateGamepad()
//{
//	HRESULT hr;
//
//	ZeroMemory( &gamepadState, sizeof( DIJOYSTATE2 ) );
//	gamepadState.rgdwPOV[0] = -1;
//
//	if( gamepad == NULL )
//		return S_OK;
//
//	hr = gamepad->Poll();
//	if( FAILED( hr ) )
//	{
//		hr = gamepad->Acquire();
//		if( hr == DIERR_INPUTLOST )
//			gamepad->Acquire();
//
//		if( (hr == DIERR_INVALIDPARAM) || (hr == DIERR_NOTINITIALIZED) )
//			return E_FAIL;
//
//		if( hr == DIERR_OTHERAPPHASPRIO )
//			return S_OK;
//	}
//
//	if( FAILED( hr = gamepad->GetDeviceState(
//		sizeof(DIJOYSTATE2), &gamepadState ) ) )
//		return hr;
//
//	return S_OK;
//}
//
//bool InputManager::CheckGamepadButton( BYTE button )
//{
//	if( gamepadState.rgbButtons[button] )
//		return true;
//	else
//		return false;
//}
//
//bool InputManager::CheckGamepadBufferedButton( BYTE button )
//{
//	if( CheckGamepadButton( button ) )
//	{
//		if( !gamepadIsPressed[button] )
//		{
//			gamepadIsPressed[button] = true;
//			return true;
//		}else
//		{
//			return false;
//		}
//	}else
//	{
//		gamepadIsPressed[button] = false;
//		return false;
//	}
//}
//
//bool InputManager::CheckGamepadDpad( DPAD direction )
//{
//	if( gamepadState.rgdwPOV[0] == direction )
//		return true;
//	else
//		return false;
//}
//
//bool InputManager::CheckGamepadBufferedDpad( DPAD direction )
//{
//	short t = (short)direction / 4500;
//	if( CheckGamepadDpad( direction ) )
//	{
//		if( !gamepadDpadPressed[t] )
//		{
//			gamepadDpadPressed[t] = true;
//			return true;
//		}else
//		{
//			return false;
//		}
//	}else
//	{
//		gamepadDpadPressed[t] = false;
//		return false;
//	}
//}
//
//int  InputManager::CheckGamepadLX()
//{
//	if( abs(gamepadState.lX) > deadZone )
//		return gamepadState.lX;
//	else
//		return 0;
//}
//
//int  InputManager::CheckGamepadLY()
//{
//	if( abs(gamepadState.lY) > deadZone )
//		return gamepadState.lY;
//	else
//		return 0;
//}
//
//int  InputManager::CheckGamepadRX()
//{
//	if( abs(gamepadState.lZ) > deadZone )
//		return gamepadState.lZ;
//	else
//		return 0;
//}
//
//int  InputManager::CheckGamepadRY()
//{
//	if( abs(gamepadState.lRz) > deadZone )
//		return gamepadState.lRz;
//	else
//		return 0;
//}
//
//void InputManager::ShutdownGamepad()
//{
//	if( gamepad )
//	{
//		gamepad->Unacquire();
//		gamepad->Release();
//		gamepad = NULL;
//	}
//}

//xbox 360 controller methods==================================================
//=============================================================================

void InputManager::UpdateXboxController( BYTE controllerNum )
{
	ZeroMemory( &xboxControllerState[controllerNum], sizeof(XINPUT_STATE) );

	xboxControllerResult[controllerNum] = XInputGetState(
		(DWORD)controllerNum, &xboxControllerState[controllerNum] );
}

bool InputManager::CheckXboxControllerConnected( BYTE controllerNum )
{
	if( xboxControllerResult[controllerNum] != ERROR_SUCCESS )
		return false;

	return true;
}

bool InputManager::CheckXboxButton( BYTE controllerNum, XBOX_BUTTON button )
{
	if( xboxControllerResult[controllerNum] != ERROR_SUCCESS )
		return false;

	if( xboxControllerState[controllerNum].Gamepad.wButtons & button )
		return true;

	return false;
}

bool InputManager::CheckXboxBufferedButton( BYTE controllerNUM, XBOX_BUTTON button )
{
	if( xboxControllerResult[controllerNUM] != ERROR_SUCCESS )
		return false;

	switch( button )
	{
	case XBUTTON_START:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_START_PRESSED[controllerNUM] )
				{
					XBUTTON_START_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_START_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_BACK:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_BACK_PRESSED[controllerNUM] )
				{
					XBUTTON_BACK_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_BACK_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_LTHUMB:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_LTHUMB_PRESSED[controllerNUM] )
				{
					XBUTTON_LTHUMB_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_LTHUMB_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_RTHUMB:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_RTHUMB_PRESSED[controllerNUM] )
				{
					XBUTTON_RTHUMB_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_RTHUMB_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_LSHOULDER:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_LSHOULDER_PRESSED[controllerNUM] )
				{
					XBUTTON_LSHOULDER_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_LSHOULDER_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_RSHOULDER:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_RSHOULDER_PRESSED[controllerNUM] )
				{
					XBUTTON_RSHOULDER_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_RSHOULDER_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_A:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_A_PRESSED[controllerNUM] )
				{
					XBUTTON_A_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_A_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_B:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_B_PRESSED[controllerNUM] )
				{
					XBUTTON_B_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_B_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_X:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_X_PRESSED[controllerNUM] )
				{
					XBUTTON_X_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_X_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;
	case XBUTTON_Y:
		{
			if( CheckXboxButton( controllerNUM, button ) )
			{
				if( !XBUTTON_Y_PRESSED[controllerNUM] )
				{
					XBUTTON_Y_PRESSED[controllerNUM] = true;
					return true;
				}else
				{
					return false;
				}
			}else
			{
				XBUTTON_Y_PRESSED[controllerNUM] = false;
				return false;
			}
		}
		break;

	default:
		return false;
		break;
	}
}

bool InputManager::CheckXboxDpad( BYTE controllerNum, XBOX_DPAD dpad )
{
	if( xboxControllerResult[controllerNum] != ERROR_SUCCESS )
		return false;

	if( xboxControllerState[controllerNum].Gamepad.wButtons & dpad )
		return true;

	return false;
}

bool InputManager::CheckXboxBufferedDpad( BYTE controllerNum, XBOX_DPAD dpad )
{
	if( xboxControllerResult[controllerNum] != ERROR_SUCCESS )
		return false;

	switch( dpad )
	{
	case XDPAD_UP:
		if( CheckXboxDpad( controllerNum, dpad ) )
		{
			if( !XDPAD_UP_PRESSED[controllerNum] )
			{
				XDPAD_UP_PRESSED[controllerNum] = true;
				return true;
			}else
			{
				return false;
			}
		}else
		{
			XDPAD_UP_PRESSED[controllerNum] = false;
			return false;
		}
		break;
	case XDPAD_DOWN:
		if( CheckXboxDpad( controllerNum, dpad ) )
		{
			if( ! XDPAD_DOWN_PRESSED[controllerNum] )
			{
				XDPAD_DOWN_PRESSED[controllerNum] = true;
				return true;
			}else
			{
				return false;
			}
		}else
		{
			XDPAD_DOWN_PRESSED[controllerNum] = false;
			return false;
		}
		break;
	case XDPAD_LEFT:
		if( CheckXboxDpad( controllerNum, dpad ) )
		{
			if( ! XDPAD_LEFT_PRESSED[controllerNum] )
			{
				XDPAD_LEFT_PRESSED[controllerNum] = true;
				return true;
			}else
			{
				return false;
			}
		}else
		{
			XDPAD_LEFT_PRESSED[controllerNum] = false;
			return false;
		}
		break;
	case XDPAD_RIGHT:
		if( CheckXboxDpad( controllerNum, dpad ) )
		{
			if( ! XDPAD_RIGHT_PRESSED[controllerNum] )
			{
				XDPAD_RIGHT_PRESSED[controllerNum] = true;
				return true;
			}else
			{
				return false;
			}
		}else
		{
			XDPAD_RIGHT_PRESSED[controllerNum] = false;
			return false;
		}
		break;
	default:
		return false;
		break;
	}
}

short InputManager::CheckXboxLStickX( BYTE controllerNum )
{
	char t = xboxControllerState[controllerNum].Gamepad.sThumbLX / 328;
	if( abs( t ) > deadZone )
		return (short)t;

	return 0;
}

short InputManager::CheckXboxLStickY( BYTE controllerNum )
{
	char t = xboxControllerState[controllerNum].Gamepad.sThumbLY / 328;
	if( abs( t ) > deadZone )
		return (short)t;

	return 0;
}

short InputManager::CheckXboxRStickX( BYTE controllerNum )
{
	char t = xboxControllerState[controllerNum].Gamepad.sThumbRX / 328;
	if( abs( t ) > deadZone )
		return (short)t;

	return 0;
}

short InputManager::CheckXboxRStickY( BYTE controllerNum )
{
	char t = xboxControllerState[controllerNum].Gamepad.sThumbRY / 328;
	if( abs( t ) > deadZone )
		return (short)t;

	return 0;
}

short InputManager::CheckXboxLTrigger( BYTE controllerNum )
{
	BYTE t = xboxControllerState[controllerNum].Gamepad.bLeftTrigger;
	if( t > xTriggerDeadZone )
		return (short)t;

	return 0;
}

short InputManager::CheckXboxRTrigger( BYTE controllerNum )
{
	BYTE t = xboxControllerState[controllerNum].Gamepad.bRightTrigger;
	if( t > xTriggerDeadZone )
		return (short)t;

	return 0;
}

void InputManager::VibrateXboxController( BYTE controllerNum, int left, int right )
{
	XINPUT_VIBRATION v;

	ZeroMemory( &v, sizeof( XINPUT_VIBRATION ) );

	v.wLeftMotorSpeed = left;
	v.wRightMotorSpeed = right;

	XInputSetState( controllerNum, &v );
}

void InputManager::SetWindowDimensions( float width, float height )
{
	ScreenWidth = width;
	ScreenHeight = height;
}