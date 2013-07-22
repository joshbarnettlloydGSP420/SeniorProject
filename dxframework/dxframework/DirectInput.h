#pragma once
//////////////////////////////////////////////////////////////////////////
// Direct X 9.0c Headers and Library Files								//
//////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <Windows.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// Safe Release Macro
#define ReleaseCOM(x) if(x){x->Release(); x = 0;};

class DirectInput
{
public:
	DirectInput(HWND hWnd, HINSTANCE hInst);
	~DirectInput();

	void poll();
	bool keyDown(short key);
	bool mouseButtonDown(int button);
	float mouseDX();
	float mouseDY();
	float mouseDZ();

	typedef struct DIMOUSESTATE2 {
		LONG lX;
		LONG lY;
		LONG lZ;
		BYTE rgbButtons[8];
	} DIMOUSESTATE2, *LPDIMOUSESTATE2;


private:
	// Functions
	DirectInput(const DirectInput& rhs);
	DirectInput& operator=(const DirectInput& rhs);

	// Variables
	IDirectInput8*       mDInput;
	IDirectInputDevice8* mKeyboard;
	char                 mKeyboardState[256];
	IDirectInputDevice8* mMouse;
	DIMOUSESTATE2        mMouseState; 
};

extern DirectInput* gDInput;
