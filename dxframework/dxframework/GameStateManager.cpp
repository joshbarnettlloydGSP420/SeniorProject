#include "GameStateManager.h"


GameStateManager::GameStateManager(void)
{
}


GameStateManager::~GameStateManager(void)
{
}

void GameStateManager::Init( HWND* wndHandle,  D3DPRESENT_PARAMETERS* D3dpp, HINSTANCE hInst, IDirect3DDevice9* device)
{
	m_pD3DDevice = device;
	hwnd = wndHandle;
	D3Dpp = D3dpp;


	// Create a new input manager
	input = new InputManager();
	input->init(hInst, *wndHandle);

	// Create a new menu
	mainMenu = new MenuMain();
	mainMenu->Init( input, m_pD3DDevice );

	// Set the active game state to the Main Menu
	activeGameState = MAIN_MENU;
}

void GameStateManager::Update( float dt )
{
	switch ( activeGameState )
	{
		///////////////////////////////////////////////////////////////////////
	case QUIT:
		{
			// Quit the Application
			activeGameState = QUIT;
			PostQuitMessage(0);
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case MAIN_MENU:
		{
			// Call the main menu and return menu selection
			mainMenu->Update();
			switch ( mainMenu->GetState() )
			{
			case 1:	// Quit
				{
					activeGameState = QUIT;
					break;
				}
			case 2:	// Options Menu
				{
					// delete the main menu
					delete mainMenu;

					// create a new options menu
					optionsMenu = new OptionsMenu();
					optionsMenu->Init( input, m_pD3DDevice, hwnd, D3Dpp);

					// switch the game state to the options menu
					activeGameState = OPTIONS_MENU;
					break;
				}
			case 3:	// Game Start
				{
					// delete the main menu
					delete mainMenu;

					// create a new game
					game = new Game();
					game->Init( input, m_pD3DDevice, hwnd);

					activeGameState = GAME;
					break;
				}
			}
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case OPTIONS_MENU:
		{
			// Add optionsMenu update function
			optionsMenu->Update();

			switch ( optionsMenu->GetState() )
			{
			case 1: // Exit to main menu
				{
					// delete the options menu
					delete optionsMenu;

					// Create a new menu
					mainMenu = new MenuMain();
					mainMenu->Init( input, m_pD3DDevice );

					// Change the active game state to the main menu
					activeGameState = MAIN_MENU;
					break;
				}
			case 2: // Switch Fullscreen / Windowed mode
				{
					// TODO: Put full screen stuff here

					optionsMenu->ResetState(0);
					break;
				}
			case 3:	// Play credits
				{
					break;
				}
			}
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case GAME:
		{
			// Game's update function
			game->Update( dt );

			if ( input->keyDown( DIK_P))
			{
				// create a pause menu
				pauseMenu = new PauseMenu();
				pauseMenu->Init( input, m_pD3DDevice);

				activeGameState = PAUSE_MENU;
			}

			break;
		}
		///////////////////////////////////////////////////////////////////////
	case PAUSE_MENU:
		{
			// Pause menu Update
			pauseMenu->Update();

			switch ( pauseMenu->GetState() )
			{
			case 1: // Resume Game
				{
					// delete the pause menu
					delete pauseMenu;

					activeGameState = GAME;
					break;
				}
			case 2:	// Restart the game
				{
					// delete game and pause menu
					delete game;
					delete pauseMenu;

					// create a new game
					game = new Game();
					game->Init( input, m_pD3DDevice, hwnd);

					activeGameState = GAME;

					break;
				}
			case 3: // Quit to the main menu
				{
					// delete game and pause menu
					delete game;
					delete pauseMenu;

					// initialize a new main menu
					mainMenu = new MenuMain();
					mainMenu->Init( input, m_pD3DDevice);
					 
					activeGameState = MAIN_MENU;
					break;
				}
			}
			break;
		}

	}
}

void GameStateManager::Render()
{
	// If the device was not created successfully, return
	if(!m_pD3DDevice)
		return;

	//////////////////////////////////////////////////////////////////////////
	// All draw calls between swap chain's functions, and pre-render and post- 
	// render functions (Clear and Present, BeginScene and EndScene)
	//////////////////////////////////////////////////////////////////////////
	m_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f), 1.0f, 0);

	// Clear the back buffer, call BeginScene()
	m_pD3DDevice->BeginScene();

	switch ( activeGameState )
	{
		///////////////////////////////////////////////////////////////////////
	case MAIN_MENU:
		{
			// Render the Main Menu
			mainMenu->Render();
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case GAME:
		{
			// Render the game
			game->Render();
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case OPTIONS_MENU:
		{
			// Render the Options Menu
			optionsMenu->Render();
			break;
		}
		///////////////////////////////////////////////////////////////////////
	case PAUSE_MENU:
		{
			// Render the Pause menu
			pauseMenu->Render();
			break;
		}
	}

	// EndScene, and Present the back buffer to the display buffer
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(0, 0, 0, 0);
}

void GameStateManager::onResetDevice()
{
	if ( optionsMenu )
		optionsMenu->onResetDevice();
	else if ( mainMenu )
		mainMenu->onResetDevice();
}

void GameStateManager::onLostDevice()
{
	if ( optionsMenu )
		optionsMenu->onLostDevice();
	else if ( mainMenu )
		mainMenu->onLostDevice();
}