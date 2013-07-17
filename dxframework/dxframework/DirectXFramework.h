#pragma once

#include "GameStateManager.h"

//////////////////////////////////////////////////////////////////////////
// DirectX 9 headers and library files								    //
//////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dinput8.lib")

// Macro to release COM objects fast and safely
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}

class CDirectXFramework
{
private:

	GameStateManager			gSM;
	//////////////////////////////////////////////////////////////////////////
	// Application Variables												//
	//////////////////////////////////////////////////////////////////////////
	HWND						m_hWnd;			// Handle to the window
	bool						m_bVsync;		// Boolean for vertical syncing

	//////////////////////////////////////////////////////////////////////////
	// Direct3D Variables													//
	//////////////////////////////////////////////////////////////////////////
	IDirect3D9*					m_pD3DObject;	// Direct3D 9 Object
	IDirect3DDevice9*			m_pD3DDevice;	// Direct3D 9 Device
	D3DCAPS9					m_D3DCaps;		// Device Capabilities
	D3DPRESENT_PARAMETERS		D3Dpp;

	//////////////////////////////////////////////////////////////////////////
	// Screen Variables														//
	//////////////////////////////////////////////////////////////////////////
	bool						m_bFullscreen;
	bool						FPSDisplay;

	int							screenWidth;
	int							screenHeight;

public:
	//////////////////////////////////////////////////////////////////////////
	// Init and Shutdown are preferred to constructors and destructor,
	// due to having more control when to explicitly call them when global.
	//////////////////////////////////////////////////////////////////////////
	CDirectXFramework(void);
	~CDirectXFramework(void);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Init
	// Parameters:	HWND hWnd - Handle to the window for the application
	//				HINSTANCE hInst - Handle to the application instance
	//				bool bWindowed - Boolean to control windowed or full-screen
	// Return:		void
	// Description:	Ran once at the start.  Initialize DirectX components and 
	//				variables to control the application.  
	//////////////////////////////////////////////////////////////////////////
	void Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Update
	// Parameters:	float elapsedTime - Time that has elapsed since the last
	//					update call.
	// Return:		void
	// Description: Runs every frame, use dt to limit functionality called to
	//				a certain amount of elapsed time that has passed.  Used 
	//				for updating variables and processing input commands prior
	//				to calling render.
	//////////////////////////////////////////////////////////////////////////
	void Update(float dt);

	//////////////////////////////////////////////////////////////////////////
	// Name:		Render
	// Parameters:	float elapsedTime - Time that has elapsed since the last
	//					render call.
	// Return:		void
	// Description: Runs every frame, use dt to limit functionality called to
	//				a certain amount of elapsed time that has passed.  Render
	//				calls all draw call to render objects to the screen.
	//////////////////////////////////////////////////////////////////////////
	void Render();

	//////////////////////////////////////////////////////////////////////////
	// Name:		Shutdown
	// Parameters:	void
	// Return:		void
	// Description:	Runs once at the end of an application.  Destroy COM 
	//				objects and deallocate dynamic memory.
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	bool isDeviceLost();
	virtual void onLostDevice() {};
	virtual void onResetDevice() {};
	virtual bool checkDeviceCaps() { return true; };

	void enableFullScreenMode( bool enable);
};
