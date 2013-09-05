#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <windows.h>
#include <iostream>
#include <dshow.h>
<<<<<<< HEAD
#include "DirectInput.h"
=======
#include "InputManager.h"
>>>>>>> origin/MartinezWorking

#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")

// Macro to release COM objects fast and safely
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}

class BaseMenu
{
protected:
	////////////////////////////////////////////////////////////////////////
	// D3D Variables
	////////////////////////////////////////////////////////////////////////
	IDirect3DDevice9*		m_pD3DDevice;		// Device for menus

	//////////////////////////////////////////////////////////////////////////
	// Font Variables
	//////////////////////////////////////////////////////////////////////////
	ID3DXFont*	m_pD3DFont;			// Font Object
	char		menuPrint[30];		// Holds the text that will be witten on screen
	D3DXCOLOR	option;				// variable to changeduring selection

	//////////////////////////////////////////////////////////////////////////
	// Sprite Variables
	//////////////////////////////////////////////////////////////////////////
	ID3DXSprite*		m_pD3DSprite;		// Sprite Object
	ID3DXSprite*		backgroundSprite;	// Sprite for background
	IDirect3DTexture9*	backgroundTexture;	// Texture to use for background
	D3DXIMAGE_INFO		m_imageInfo;		// File details of a texture
	RECT				m_rect;				// RECT for the menu background
	LPCSTR				backgroundFileName;	// name of file for background

	////////////////////////////////////////////////////////////////////////
	// Istance of gameState
	////////////////////////////////////////////////////////////////////////


	int buttonSound;
	int menuItemSelected;		// Hold the menu selection			

<<<<<<< HEAD
	DirectInput* myInput;
=======
	InputManager* myInput;
>>>>>>> origin/MartinezWorking

public:
	BaseMenu(void);
	virtual ~BaseMenu(void);

<<<<<<< HEAD
	bool Init(DirectInput* input, IDirect3DDevice9* m_pD3DDevice);
=======
	bool Init(InputManager* input, IDirect3DDevice9* m_pD3DDevice);
>>>>>>> origin/MartinezWorking
	void Update();
	void Render();

	void onLostDevice();
	void onResetDevice();
};

