#include "OptionsMenu.h"


OptionsMenu::OptionsMenu(void)
{
}


OptionsMenu::~OptionsMenu(void)
{
}

<<<<<<< HEAD
bool OptionsMenu::Init( DirectInput* input, IDirect3DDevice9* m_pD3DDevice, HWND* wndHandle, D3DPRESENT_PARAMETERS* D3dpp)
=======
bool OptionsMenu::Init(InputManager* input, IDirect3DDevice9* m_pD3DDevice, HWND* wndHandle, D3DPRESENT_PARAMETERS* D3dpp)
>>>>>>> origin/MartinezWorking
{
	BaseMenu::Init( input, m_pD3DDevice );
	hwnd = wndHandle;

	return true;
}

void OptionsMenu::Update()
{
	BaseMenu::Update();

<<<<<<< HEAD
	if ( myInput->keyDown(DIK_RETURN))
	{
		/*if ( menuItemSelected == 1)
		{		
			optionsState = o_FULLSCREEN;
		}
		else*/ if ( menuItemSelected == 1)
		{
=======
	if ( menuItemSelected < 1)
		menuItemSelected = 2;
	if ( menuItemSelected > 2)
		menuItemSelected = 1;

	if ( myInput->keyDown(DIK_RETURN))
	{
			if ( menuItemSelected == 1)
			{
>>>>>>> origin/MartinezWorking
			optionsState = o_CREDITS;
			InitVideo(L"Temp.wmv");
			videoControl->Run();

			videoEvent->GetEvent(&evCode, &eventParam1, &eventParam2, 0);

			// wait for the video to finish, or wait until the user hits Enter/Return Key
			if(myInput->keyDown( DIK_SPACE) || (evCode == EC_COMPLETE) ) 
			{
				optionsState = o_OPTIONS_MENU;
				DestroyVideo();
			}
<<<<<<< HEAD
		}
=======
			}
>>>>>>> origin/MartinezWorking
		else if ( menuItemSelected == 2)
		{
			optionsState = o_QUIT_TO_MAIN;
		}
	}
}

void OptionsMenu::Render()
{
	// Call the base menu's render method to initialize some variables
	BaseMenu::Render();

	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Print Main Menu at the top of the screen
	sprintf(menuPrint,"OPTIONS MENU");
	SetRect(&m_rect,120,130,600,500);  
	option = D3DCOLOR_ARGB(255,150,0,240);

	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

<<<<<<< HEAD
	/*sprintf(menuPrint,"Fullscreen");
	SetRect(&m_rect,120,330,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);*/

	sprintf(menuPrint,"Credits");
	SetRect(&m_rect,120,330,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
=======
	
	sprintf(menuPrint,"Credits");
	SetRect(&m_rect,120,330,600,500);
	if(menuItemSelected == 1)
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
>>>>>>> origin/MartinezWorking
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	sprintf(menuPrint,"Exit to Main Menu");
	SetRect(&m_rect,120,530,600,500);
	if(menuItemSelected == 2)
<<<<<<< HEAD
		option = D3DCOLOR_ARGB(255,255,0,255);
	else
		option = D3DCOLOR_ARGB(255,150,0,240);
=======
		option = D3DCOLOR_ARGB(255,255,0,0);
	else
		option = D3DCOLOR_ARGB(255,0,0,255);
>>>>>>> origin/MartinezWorking
	m_pD3DFont->DrawTextA(0,menuPrint,-1,&m_rect, DT_CENTER | DT_NOCLIP,option);

	m_pD3DSprite->End();
}

void OptionsMenu::InitVideo(LPCWSTR vidName)
{
	CoInitialize(NULL); 

	CoCreateInstance( CLSID_FilterGraph, NULL,
		CLSCTX_INPROC_SERVER, IID_IGraphBuilder,
		(void**)&videoGraph);

	videoGraph->QueryInterface(IID_IMediaControl,
		(void**)&videoControl);

	videoGraph->QueryInterface(IID_IMediaEvent,
		(void**)&videoEvent);

	// building a filter graph for our video
	videoGraph->RenderFile(vidName, NULL);

	//video window
	videoControl->QueryInterface(IID_IVideoWindow,
		(void**)&videoWindow);

	// setup the window
	videoWindow->put_Owner((OAHWND)hwnd);

	// Set the style
	videoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE);

	// Obtain the size of the window
	RECT WinRect;
	GetClientRect(*hwnd, &WinRect);

	// Set the video size to the size of the window
	videoWindow->SetWindowPosition(WinRect.left, WinRect.top, 
		WinRect.right, WinRect.bottom);
}

void OptionsMenu::DestroyVideo()
{
	videoControl->Stop();
	videoWindow->put_Visible(OAFALSE);
	SAFE_RELEASE(videoControl);
	SAFE_RELEASE(videoWindow);
	SAFE_RELEASE(videoGraph);
}