#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"
#include "XInput.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "XInput.lib")

/*enum DPAD{	GDPAD_UP = 0, GDPAD_UPRIGHT = 4500, GDPAD_RIGHT = 9000,
			GDPAD_DOWNRIGHT = 13500, GDPAD_DOWN = 18000, DOWNLEFT = 22500,
			GDPAD_LEFT = 27000, GDPAD_UPLEFT = 31500 };*/

enum XBOX_DPAD{
	XDPAD_UP			= XINPUT_GAMEPAD_DPAD_UP,       
	XDPAD_DOWN			= XINPUT_GAMEPAD_DPAD_DOWN,     
	XDPAD_LEFT			= XINPUT_GAMEPAD_DPAD_LEFT,     
	XDPAD_RIGHT			= XINPUT_GAMEPAD_DPAD_RIGHT
};
enum XBOX_BUTTON{
	XBUTTON_START		= XINPUT_GAMEPAD_START,         
	XBUTTON_BACK		= XINPUT_GAMEPAD_BACK,          
	XBUTTON_LTHUMB		= XINPUT_GAMEPAD_LEFT_THUMB,    
	XBUTTON_RTHUMB		= XINPUT_GAMEPAD_RIGHT_THUMB,   
	XBUTTON_LSHOULDER	= XINPUT_GAMEPAD_LEFT_SHOULDER, 
	XBUTTON_RSHOULDER	= XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XBUTTON_A			= XINPUT_GAMEPAD_A,             
	XBUTTON_B			= XINPUT_GAMEPAD_B,             
	XBUTTON_X			= XINPUT_GAMEPAD_X,             
	XBUTTON_Y			= XINPUT_GAMEPAD_Y
};

class InputManager
{
public:
	///return the InputManger singleton object
	/*
		Returns a pointer to the InputManger object that
			is created with this class
	*/
	static InputManager* GetInputManager();

	//===================================================================================
	//keyboard/mouse methods=============================================================
	///Init******************************************************************************
	/*
		Initializes the input object, and creates the keyboard
			and mouse devices for use with PC games
	*/
	void Init(HWND* hWnd, HINSTANCE* hInst);

	///Update****************************************************************************
	/*
		Updates the current keyboard and mouse state's by polling
			the keyboard and mouse
	*/
	void Update();

	///CheckKeyboardKey******************************************************************
	/*
		Returns true if the specefied key is currently pressed down,
			otherwise, this method returns false if the key being
			passed as the parameter is not pressed
	*/
	bool CheckKeyboardKey( short key );

	///CheckKeyboardBufferedKey**********************************************************
	/*
		Returns true only during the frame in which the specified
			key went from being not pressed, to pressed. Returns
			false otherwise.
	*/
	bool CheckKeyboardBufferedKey( short key );

	///CheckMouseButton******************************************************************
	/*
		Returns true when the specified mouse button is being pressed.
			Otherwise, returns false if the key is not being pressed.

		0 = left Button
		1 = Right Button
		3 = Middle Button (Scroll Wheel)
		4-7 = side buttons
	*/
	bool CheckMouseButton( short button );

	///CheckMouseBufferedButton**********************************************************
	/*
		Returns true only during the frame that the specified mouse
			button went from being not pressed to pressed. Returns
			false otherwise

		0 = left Button
		1 = Right Button
		3 = Middle Button (Scroll Wheel)
		4-7 = side buttons
	*/
	bool CheckMouseBufferedButton( short button );

	///CheckMouseMoveX*******************************************************************
	/*
		Returns the change in movement in the X Directions for the mouse
			since the last frame.
	*/
	int  CheckMouseMoveX();

	///CheckMouseMoveY*******************************************************************
	/*
		Returns the change in movement in the Y direction for the mouse
			since the last frame.
	*/
	int  CheckMouseMoveY();

	///CheckMouseScroll******************************************************************
	/*
		Returns the Change in the mouse scroll wheel for the mouse
			since the last frame
	*/
	int  CheckMouseScroll();

	///GetMousePosX
	/*
		Returns the X position of the mouse relative to the top left corner of the window
	*/
	int GetMousePosX();
	int donothing(){}

	void SetWindowDimensions( float width, float height );

	///GetMousePosY
	/*
		Returns the Y position of the mouse relative to the top right corner of the window
	*/
	int GetMousePosY();

	///Shutdown**************************************************************************
	/*
		Shuts down the directInput object for the InputManager class.
	*/
	void Shutdown();

	////===================================================================================
	////gamepad methods====================================================================
	/////InitGamepad***********************************************************************
	///*
	//	Initializes the gamepad object if there is one attatched,
	//		and returns true, if it succeded, otherwise, returns
	//		false if no gamepad was initialized.
	//*/
	//bool InitGamepad( HWND* hWnd );

	/////UpdateGamepad*********************************************************************
	///*
	//	Updates the current gamepad state by polling the joystick.
	//		If a gamepad is not plugged in, or is not initialized,
	//		then the method returns without polling
	//*/
	//HRESULT UpdateGamepad();

	/////CheckGamepadButton****************************************************************
	///*
	//	Returns true if the specified button on the gamepad is 
	//		currently being pressed. Returns false otherwise.
	//		Also returns false, if the gamepad is not plugged in
	//		or is not initialized.
	//*/
	//bool CheckGamepadButton( BYTE button );

	/////CheckGamepadBufferedButton********************************************************
	///*
	//	Returns true only during the fram in which the specified
	//		button on the gamepad went from being not pressed to 
	//		presed. Returns false otherwise.
	//*/
	//bool CheckGamepadBufferedButton( BYTE button );

	/////CheckGamepadDpad******************************************************************
	///*
	//	Returns true if the specified dpad direction on the gamepad
	//		is currently being pressed, returns false otherwise.
	//*/
	//bool CheckGamepadDpad( DPAD direction );

	/////CheckGamepadBufferedDpad**********************************************************
	///*
	//	Returns true only during the frame in which the specified
	//		button on the gamepad went from being not pressed to 
	//		pressed. Returns false otherwise.,
	//*/
	//bool CheckGamepadBufferedDpad( DPAD direction );

	/////CheckGamepadLX********************************************************************
	///*
	//	Returns how far the left analog stick on the gamepad is being
	//		moved in the X direction, if it is moved passed the deadzone.

	//	Returns -100 to 100
	//*/
	//int  CheckGamepadLX();

	/////CheckGamepadLY********************************************************************
	///*
	//	Returns how far the left analog stick on the gamepad is being
	//		moved in the Y direction, if it is moved passed the deadzone.

	//	Returns -100 to 100
	//*/
	//int  CheckGamepadLY();

	/////CheckGamepadRX********************************************************************
	///*
	//	Returns how far the right analog stick on the gamepad is being
	//		moved in the X direction, if it is moved passed the deadzone.

	//	Returns -100 to 100
	//*/
	//int  CheckGamepadRX();

	/////CheckGamepadRY********************************************************************
	///*
	//	Returns how far the right analog stick on the gamepad is being
	//		moved in the Y direction, if it is moved passed the deadzone.

	//	Returns -100 to 100
	//*/
	//int  CheckGamepadRY();

	/////ShutdownGamepad*******************************************************************
	///*
	//	Shuts down the gamepad.
	//*/
	//void ShutdownGamepad();

	//===================================================================================
	//xbox 360 controller methods========================================================
	///UpdateXboxController**************************************************************
	/*
		updates the xbox controller state for the specified controller 
			number if the xbox controller is currently plugged in, 
			otherwise this method just returns and does nothing.
	*/
	void UpdateXboxController( BYTE controllerNum );

	///CheckXboxControllerConnected
	/*
		Checks whether the the specified xbox controller is connected, returns
			true if the controller is connected, returns false otherwise.
	*/
	bool CheckXboxControllerConnected( BYTE controllerNum );

	///CheckXboxButton*******************************************************************
	/*
		Returns true if the specified button is pressed on the specified
			controller number. Otherwise returns false
	*/
	bool CheckXboxButton( BYTE controllerNum, XBOX_BUTTON button );

	///CheckXboxBufferedButton***********************************************************
	/*
		Returns true only during the frame that the specified button
			on the specified controller number went from being 
			not pressed to pressed. Otherwise, returns false.
	*/
	bool CheckXboxBufferedButton( BYTE controllerNum, XBOX_BUTTON button );

	///CheckXboxDpad*********************************************************************
	/*
		Returns true if the specified dpad button is currently
			pressed on the specified controller number. Otherwise,
			returns false,
	*/
	bool CheckXboxDpad( BYTE controllerNum, XBOX_DPAD dpad );

	///CheckXboxBufferedDpad*************************************************************
	/*
		Returns true only during the frame that the specified
			dpad button on the specified controller number
			went from being not pressed to pressed. Otherwise,
			returns true.
	*/
	bool CheckXboxBufferedDpad( BYTE controllerNum, XBOX_DPAD dpad );

	///CheckXboxLStickX******************************************************************
	/*
		Returns the amount that the X axis on the left analog
			stick has moved on the specified controller number,
			if it has moved passed the dead zone.

		Returns -99 to 99
	*/
	short CheckXboxLStickX( BYTE controllerNum );

	///CheckXboxLStickY******************************************************************
	/*
		Returns the amount that the Y axis on the left analog
			stick has moved on the specified controller number,
			if it has moved passed the dead zone.

		Returns -99 to 99
	*/
	short CheckXboxLStickY( BYTE controllerNum );

	///CheckXboxRStickX******************************************************************
	/*
		Returns the amount that the X axis on the Right analog
			stick has moved on the specified controller number,
			if if has moved passed the dead zone.

		Returns -99 to 99
	*/
	short CheckXboxRStickX( BYTE controllerNum );

	///CheckXboxRStickY******************************************************************
	/*
		Returns the amount that the Y axis on the Right analog
			stick has moved on the specified controller number
			if it has moved passed the dead zone.

		Returns -99 to 99
	*/
	short CheckXboxRStickY( BYTE controllerNum );

	///CheckXboxLTrigger*****************************************************************
	/*
		Returns the amount that the left trigger on the specified
			xbox controller has moved, if it has moved passed the 
			dead zone.

		Returns 0 to 255
	*/
	short CheckXboxLTrigger( BYTE controllerNum );

	///CheckXboxRTrigger*****************************************************************
	/*
		Returns the amount that the right trigger on the specified
			xbox controller has moved, if it has moved passed the
			dead zone.

		Returns 0 to 255
	*/
	short CheckXboxRTrigger( BYTE controllerNum );

	///VibrateXboxController*************************************************************
	/*
		Sets the vibration values for the left and right motors
			on the specified xbox controller number.

		Valid left/right values 0 - 65500
	*/
	void VibrateXboxController( BYTE controllerNum, int left = 0, int right = 0 );

private:
	static InputManager* Controller;
	InputManager(void){}

	friend BOOL CALLBACK enumCallBack( const DIDEVICEINSTANCE* instance, VOID* context );
	friend BOOL CALLBACK enumAxesCallback( const DIDEVICEOBJECTINSTANCE* instance, VOID* context );

	IDirectInput8*			dInput;

	//Keyboard/Mouse attributes================================================
	//=========================================================================
	IDirectInputDevice8*	keyboard;
	IDirectInputDevice8*	mouse;
	char					buffer[256];
	bool					isPressed[256];
	DIMOUSESTATE2			mouseState;
	bool					mousePressed[8];
	int						MouseX, MouseY;

	//gamepad attributes=======================================================
	//=========================================================================
	IDirectInputDevice8*	gamepad;
	DIJOYSTATE2				gamepadState;
	bool					gamepadIsPressed[12];
	bool					gamepadDpadPressed[8];

	//xbox 360 controller attributes===========================================
	//=========================================================================
	XINPUT_STATE			xboxControllerState[4];
	DWORD					xboxControllerResult[4];
	bool					XBUTTON_START_PRESSED[4],
							XBUTTON_BACK_PRESSED[4],
							XBUTTON_LTHUMB_PRESSED[4],
							XBUTTON_RTHUMB_PRESSED[4],
							XBUTTON_LSHOULDER_PRESSED[4],
							XBUTTON_RSHOULDER_PRESSED[4],
							XBUTTON_A_PRESSED[4],
							XBUTTON_B_PRESSED[4],
							XBUTTON_X_PRESSED[4],
							XBUTTON_Y_PRESSED[4];
	bool					XDPAD_UP_PRESSED[4],
							XDPAD_DOWN_PRESSED[4],
							XDPAD_LEFT_PRESSED[4],
							XDPAD_RIGHT_PRESSED[4];
	char					xTriggerDeadZone;

	//dead zone for both the gamepad and xbox controller sticks================
	//=========================================================================
	char					deadZone;

	short ScreenWidth, ScreenHeight;
};