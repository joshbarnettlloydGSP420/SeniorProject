#pragma once

#include <Windows.h>
#include "InputManager.h"
#include "MenuMain.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"
//#include "Timer.h"


enum GAME_STATE
{
	QUIT			= 0,
	MAIN_MENU		= 1,
	OPTIONS_MENU	= 2,
	GAME			= 3,
	PAUSE_MENU		= 4,
};


////////////////////////////////////////////////////////////////////////
/// The GameStateManager will change the state that the game is 
/// currently in to:
///		* Game
///		* Main Menu
///		* Options Menu
///		* Pause Menu
////////////////////////////////////////////////////////////////////////
class GameStateManager
{
private:
	// Needed Variables
	IDirect3DDevice9*		m_pD3DDevice;
	HWND*					hwnd;
	D3DPRESENT_PARAMETERS*	D3Dpp;

	// Create variables to classes
	InputManager*			input;
	MenuMain*				mainMenu;
	OptionsMenu*			optionsMenu;
	PauseMenu*				pauseMenu;
	//Game*					game;
	
	// Create a GAME_STATE variable
	GAME_STATE	activeGameState;

public:
	GameStateManager(void);
	~GameStateManager(void);

	void Init(HWND* wndHandle,  D3DPRESENT_PARAMETERS* D3dpp, HINSTANCE hInst, IDirect3DDevice9* device);
	void Update( float dt);
	void Render();

	void onResetDevice();
	void onLostDevice();
};

