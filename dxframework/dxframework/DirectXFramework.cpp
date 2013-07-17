#include "DirectXFramework.h"


CDirectXFramework::CDirectXFramework(void)
{
	// Init or NULL objects before use to avoid any undefined behavior
	m_bVsync		= false;
	m_pD3DObject	= 0;
	m_pD3DDevice	= 0;

}

CDirectXFramework::~CDirectXFramework(void)
{
	// If Shutdown is not explicitly called correctly, call it when 
	// this class is destroyed or falls out of scope as an error check.
	Shutdown();
}

void CDirectXFramework::Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed)
{
	m_hWnd = hWnd;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Direct3D Foundations - D3D Object, Present Parameters, and D3D Device								 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Create the D3D Object
	m_pD3DObject = Direct3DCreate9(D3D_SDK_VERSION);

	//RECT
	// Find the width and height of window using hWnd and GetWindowRect()
	RECT windowSizeRect;
	GetWindowRect(hWnd, &windowSizeRect);
	screenWidth = windowSizeRect.right - windowSizeRect.left;
	screenHeight = windowSizeRect.bottom - windowSizeRect.top;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Presentation paramters for creating the D3D9 device													 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DPRESENT_PARAMETERS D3Dpp;
	ZeroMemory(&D3Dpp, sizeof(D3Dpp));						// NULL the structure's memory

	D3Dpp.hDeviceWindow					= hWnd;																		// Handle to the focus window
	D3Dpp.Windowed						= bWindowed;																// Windowed or Full-screen boolean
	D3Dpp.AutoDepthStencilFormat		= D3DFMT_D24S8;																// Format of depth/stencil buffer, 24 bit depth, 8 bit stencil
	D3Dpp.EnableAutoDepthStencil		= TRUE;																		// Enables Z-Buffer (Depth Buffer)
	D3Dpp.BackBufferCount				= 1;																		// Change if need of > 1 is required at a later date
	D3Dpp.BackBufferFormat				= D3DFMT_X8R8G8B8;															// Back-buffer format, 8 bits for each pixel
	D3Dpp.BackBufferHeight				= screenHeight;																// Make sure resolution is supported, use adapter modes
	D3Dpp.BackBufferWidth				= screenWidth;																// (Same as above)
	D3Dpp.SwapEffect					= D3DSWAPEFFECT_DISCARD;													// Discard back-buffer, must stay discard to support multi-sample
	D3Dpp.PresentationInterval			= m_bVsync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;	// Present back-buffer immediately, unless V-Sync is on								
	D3Dpp.Flags							= D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;										// This flag should improve performance, if not set to NULL.
	D3Dpp.FullScreen_RefreshRateInHz	= bWindowed ? 0 : D3DPRESENT_RATE_DEFAULT;									// Full-screen refresh rate, use adapter modes or default
	D3Dpp.MultiSampleQuality			= 0;																		// MSAA currently off, check documentation for support.
	D3Dpp.MultiSampleType				= D3DMULTISAMPLE_NONE;														// MSAA currently off, check documentation for support.

	// Check device capabilities
	DWORD deviceBehaviorFlags = 0;
	m_pD3DObject->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	// Determine vertex processing mode
	if(m_D3DCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		// Hardware vertex processing supported? (Video Card)
		deviceBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;	
	}
	else
	{
		// If not, use software (CPU)
		deviceBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING; 
	}

	// If hardware vertex processing is on, check pure device support
	if(m_D3DCaps.DevCaps & D3DDEVCAPS_PUREDEVICE && deviceBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
	{
		deviceBehaviorFlags |= D3DCREATE_PUREDEVICE;	
	}

	// Create the D3D Device with the present parameters and device flags above
	m_pD3DObject->CreateDevice(D3DADAPTER_DEFAULT,		// which adapter to use, set to primary
								D3DDEVTYPE_HAL,			// device type to use, set to hardware rasterization
								hWnd,					// handle to the focus window
								deviceBehaviorFlags,	// behavior flags
								&D3Dpp,					// presentation parameters
								&m_pD3DDevice);			// returned device pointer
	
	//////////////////////////////////////////////////////////////////////////
	// Create an instance of the GameStateManager
	//////////////////////////////////////////////////////////////////////////
	gSM.Init(&hWnd, &D3Dpp, hInst, m_pD3DDevice);
}

void CDirectXFramework::Update(float dt)
{
	gSM.Update(dt);
}

void CDirectXFramework::Render()
{
	gSM.Render();
}

void CDirectXFramework::Shutdown()
{
	//*************************************************************************
	// Release COM objects in the opposite order they were created in

	// 3DDevice	
	SAFE_RELEASE(m_pD3DDevice);

	// 3DObject
	SAFE_RELEASE(m_pD3DObject);
	//*************************************************************************

}

void CDirectXFramework::enableFullScreenMode( bool enable )
{
	// Switch to full screen mode.
	if(enable)
	{
		// Are we already in full screen mode?
		if( !D3Dpp.Windowed )
			return;
		// Get the current screen resolution.
		int width  = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);
		D3Dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		D3Dpp.BackBufferWidth  = width;
		D3Dpp.BackBufferHeight = height;
		D3Dpp.Windowed         = false;
		// Change the window style to a more full screen
		// friendly style.
		SetWindowLongPtr(m_hWnd, GWL_STYLE, WS_POPUP);
		// If we call SetWindowLongPtr, MSDN states that we need
		// to call SetWindowPos for the change to take effect.
		// In addition, we need to call this function anyway
		// to update the window dimensions.
		SetWindowPos(m_hWnd, HWND_TOP, 0, 0,
			width, height, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
	}

	// Switch to windowed mode.
	else
	{
		// Are we already in windowed mode?
		if(  D3Dpp.Windowed )
			return;
		// Default to a client rectangle of 800x600.
		RECT R = {0, 0, 800, 600};
		AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
		D3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		D3Dpp.BackBufferWidth  = 800;
		D3Dpp.BackBufferHeight = 600;
		D3Dpp.Windowed         = true;
		// Change the window style to a more windowed
		// friendly style.
		SetWindowLongPtr(m_hWnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);
		// If we call SetWindowLongPtr, MSDN states that we
		// need to call SetWindowPos for the change to take effect.
		// In addition, we need to call this function anyway to
		// update the window dimensions.
		SetWindowPos(m_hWnd, HWND_TOP, 100, 100,
			R.right, R.bottom, SWP_NOZORDER | SWP_SHOWWINDOW | SWP_FRAMECHANGED);
	}

	// Reset the device with the changes
	onLostDevice();
	m_pD3DDevice->Reset(&D3Dpp);
	onResetDevice();
}

bool CDirectXFramework::isDeviceLost()
{
	// Returns true if lost, false otherwise

	// get the state of the graphics device
	HRESULT hr = m_pD3DDevice->TestCooperativeLevel();

	// if the device is lost and cannot be reset yet, then sleep
	// for a bit and we'll try again on the next message loop cycle
	if ( hr == D3DERR_DEVICELOST )
	{
		Sleep(20);
		return true;
	}
	// Driver error, exit
	else if ( hr == D3DERR_DRIVERINTERNALERROR )
	{
		MessageBox( 0, "Internal Driver Error... Exiting", 0, 0);
		PostQuitMessage(0);
		return true;
	}
	// the device is lost but we can reset and restore it.
	else if ( hr == D3DERR_DEVICENOTRESET )
	{
		onLostDevice();
		HRESULT(m_pD3DDevice->Reset(&D3Dpp));
		onResetDevice();
		// not lost anymore
		return false;
	}
	else
		// not lost anymore
		return false;
}

