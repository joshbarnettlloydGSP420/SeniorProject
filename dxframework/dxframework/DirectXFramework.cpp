#include "DirectXFramework.h"

//CDirectXFramework* gd3dApp   = 0;
IDirect3DDevice9* m_pD3DDevice = 0;
//CameraObj* gCamera = 0;

CDirectXFramework::CDirectXFramework(void)
{
	// Init or NULL objects before use to avoid any undefined behavior
	m_bVsync		= false;
	m_pD3DObject	= 0; // *handle* naming it gd3dApp for the sake of not having to change more stuff
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
	// create a vertex format
	D3DVERTEXELEMENT9 elems[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};
	m_pD3DDevice->CreateVertexDeclaration( elems, &d3dVertexDecl );

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Render																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	render = new RenderObject();
	render->Init( m_pD3DDevice, m_pD3DSprite);
	//render->CreateVertexElement();
	render->SetVertexDecl( d3dVertexDecl);
	render->MaterialSettings();
	render->LoadShaderEffects( L"TestShader.txt", 0);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating Enemies																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*redGhost = new Enemy_Base(100, 50, 15, D3DXVECTOR4( 45, 2.5,5, 0.0), L"RedGhostTexture.jpg", 0);
	redGhost->Init( m_pD3DDevice, render);

	blueGhost = new Enemy_Base(100, 35, 10, D3DXVECTOR4( -5, 2.5,30, 0.0), L"BlueGhostTexture.jpg", 0);
	blueGhost->Init( m_pD3DDevice, render);

	yellowGhost = new Enemy_Base(100, 20, 5, D3DXVECTOR4( -35, 2.5,5, 0.0), L"YellowGhostTexture.jpg", 0);
	yellowGhost->Init( m_pD3DDevice, render);

	greenGhost = new Enemy_Base(100, 20, 20, D3DXVECTOR4( 10, 2.5,-10, 0.0), L"GreenGhostTexture.jpg", 0);
	greenGhost->Init( m_pD3DDevice, render);*/
	baseGhost = new Enemy_Base(100, 50, 15, D3DXVECTOR4( 45, 2.5,5, 0.0));
	baseGhost->Init( m_pD3DDevice, render);


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating Light																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	ZeroMemory(&light, sizeof(light));

	light.Type							= D3DLIGHT_DIRECTIONAL;
	light.Ambient						= D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	light.Diffuse						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Specular						= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Position						= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	light.Range							= 5.0f;
	light.Attenuation0					= 0.0f;
	light.Attenuation1					= 0.05f;
	light.Attenuation2					= 0.0f;

	m_pD3DDevice->SetLight(0, &light);
	m_pD3DDevice->LightEnable(0, true);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Material Settings																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	ZeroMemory(&m_pMaterial[0], sizeof(m_pMaterial[0]));
	m_pMaterial[0].Ambient				= D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	m_pMaterial[0].Diffuse				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterial[0].Emissive				= D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_pMaterial[0].Specular				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pMaterial[0].Power				= 30.0f;


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creating Camera																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	gCamera = new CameraObj();
	gCamera->createCamera(1000.0f, 1.0f, 1.3333f, ((float)screenWidth / (float)screenHeight));
	// Initialize View Matrix
	eyePos								= D3DXVECTOR3(0.0f, 1.0f, -2.0f);	// Camera Position
	lookAt								= eyePos + D3DXVECTOR3(0.0f, 0.0f, 1.0f);	// Position camera is viewing
	upVec								= D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// Rotational orientation

	// Easily calculate the view matrix with 3 intuitive vectors
	D3DXMatrixLookAtLH(&viewMat,											// Returned viewMat
						&eyePos,											// Eye Position
						&lookAt,											// LookAt Position
						&upVec);											// Up Vector

	// Apply the view matrix in the scene
	//m_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projMat,									// Return Projection Matrix
								D3DXToRadian(65.0f),						// Field of View
								(float)screenWidth / (float)screenHeight,	// Aspect Ratio
								1.0f,										// Near Plane
								1000.0f);


	// Apply the projection matrix in the scene
	//m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &projMat);

	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	//camera = new CameraObj();
	//camera->createCamera(5000.0f, 0.01f, 1.3333f, D3DXToRadian(45.0f));


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Loading Textures																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	// create a TEXTURE object
	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"Metal_Texture.jpg", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &m_pTexture[0]);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, L"test.tga", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &m_pTexture[1]);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Font COM Object																				 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// create a FONT object
	D3DXCreateFont(m_pD3DDevice, 30, 0, FW_BOLD, 0, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Delicious-Roman"), 
		&m_pD3DFont);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object Inits																							 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	Player = new Object_Player();
	Player->position = D3DXVECTOR4(0.0f, 5.0f, -8.0f, 0.0f);
	Player->shape = CAPSULE;

	Mansion = new Object_Base();
	Mansion->position = D3DXVECTOR4(0.0f, 5.0f, 10.0f, 0.0f);
	Mansion->shape = BOX;
	Mansion->weight = UNMOVABLE;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load Shader Effects																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Toon Effects Shader
	ID3DXBuffer* ErrorMessage = 0;
	D3DXCreateEffectFromFile(m_pD3DDevice,
							//"ToonColored.fx",
							L"TestShader.txt",
							0,
							0,
							D3DXSHADER_DEBUG,
							0,
							&fx[0],
							&ErrorMessage);
	if( ErrorMessage )
	{
		char error[512];
		ZeroMemory( error, 256 );
		strcpy_s( error, (char*)ErrorMessage->GetBufferPointer() );
		MessageBox(0, (LPCWSTR)error, L"Shader Error", MB_OK );
	}

	//hTech[0] = fx[0]->GetTechniqueByName("ToonColored");
	hTech[0] = fx[0]->GetTechniqueByName("tech0");


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create 3D Mesh From X																				 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Load Test Mesh
	loadMesh(L"FlippedY.X", &Player->objectMesh);
	loadMesh(L"RoomWithWalls.X", &Mansion->objectMesh);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create 3D Mesh From X																				 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Input Manager Init
	m_pDInput = new InputManager();
	m_pDInput->init(hInst,hWnd);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Havok Object																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Havok
	havok = new HavokCore(true);

	// Locking is necessary to make sure no two threads are trying to change the world at the same time
	havok->getWorld()->lock();

	Player->createHavokObject(havok->getWorld());
	for(short i = 0; i < ARRAYSIZE(Player->bullets); i++)
	{
		Player->createBulletHavokObject(havok->getWorld(), D3DXVECTOR3(i * 20, -120, 0.0f), i);
	}
	Mansion->createHavokObject(havok->getWorld());

	// Mansion
	createGroundBox(havok->getWorld(), 85.0f, 2.0f, 50.0f, 0.0f, 0.0f, 10.0f);	// Floor
	createGroundBox(havok->getWorld(), 100.0f, 20.0f, 2.0f, 0.0f, 0.0f, -40.0f);	// Front
	createGroundBox(havok->getWorld(), 100.0f, 20.0f, 2.0f, 0.0f, 0.0f, 57.0f);	// Back
	createGroundBox(havok->getWorld(), 2.0f, 20.0f, 50.0f, 85.0f, 0.0f, 10.0f); // Right
	createGroundBox(havok->getWorld(), 2.0f, 20.0f, 50.0f, -80.0f, 0.0f, 10.0f);// Left
	createGroundBox(havok->getWorld(), 25.0f, 20.0f, 1.0f, 5.0f, 0.0f, 12.0f);	// middle

	// enemies
	/*redGhost->createHavokObject( havok->getWorld());
	blueGhost->createHavokObject( havok->getWorld());
	yellowGhost->createHavokObject( havok->getWorld());
	greenGhost->createHavokObject( havok->getWorld());*/
	
	
	havok->getWorld()->unlock();

	/// YOU FORGOT TO INIT YOU'RE VERTEX DECLARATIONS...
	/// you digital dummy :)
	InitAllVertexDeclarations();

	//Gamestate
	gameState = new GameStateManager();
	gameState->Init(&hWnd,&D3Dpp,hInst,m_pD3DDevice);
}

HWND CDirectXFramework::getMainWnd()
{
	return m_hWnd;
}

void CDirectXFramework::Update(float dt)
{
	if(gameState->activeGameState == GAME)
	{
	havok->stepSimulation(dt);

	havok->getWorld()->lock();

	Player->Update(dt, eyePos, lookAt, havok->getWorld());
	Mansion->Update(dt);

	// enemies update
	/*yellowGhost->Update( dt, Player->position);
	if ( yellowGhost->GetIsDead() == true)
		greenGhost->Update( dt, Player->position);
	if ( greenGhost->GetIsDead() == true)
		blueGhost->Update( dt, Player->position);
	if ( blueGhost->GetIsDead() == true)
		redGhost->Update( dt, Player->position);*/
	baseGhost->Update( dt, Player->position);

	havok->getWorld()->unlock();
	

	UpdateCamera(dt);
	playerControls(dt);
	}
	gameState->Update(dt);
}

void CDirectXFramework::Render(float dt)
{
	// If the device was not created successfully, return
	if(!m_pD3DDevice)
		return;
	//*************************************************************************

	m_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,125,255),1.0f,0);
	//////////////////////////////////////////////////////////////////////////
	// All draw calls between swap chain's functions, and pre-render and post- 
	// render functions (Clear and Present, BeginScene and EndScene)
	//////////////////////////////////////////////////////////////////////////

	// Clear the back buffer, call BeginScene()
	m_pD3DDevice->BeginScene();
	//////////////////////////////////////////////////////////////////////////
	// Draw 3D Objects (for future labs - not used in Week #1)
	//////////////////////////////////////////////////////////////////////////

	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixIdentity(&transMat);

if(gameState->activeGameState == GAME)
{
	m_pD3DDevice->SetStreamSource(0, mesh_vb, 0, sizeof(Vertex));
	m_pD3DDevice->SetIndices(mesh_ib);
	m_pD3DDevice->SetVertexDeclaration(d3dVertexDecl);

	fx[0]->SetTechnique(hTech[0]);

	UINT numPasses = 0;
	fx[0]->Begin(&numPasses, 0);

	for(UINT i = 0; i < numPasses; ++i)
	{
		fx[0]->BeginPass(i);

		// Mesh Matrix
		D3DXMatrixScaling(&scaleMat, 0.04f, 0.04f, 0.0f);
		//D3DXMatrixRotationYawPitchRoll(&rotMat, Player->rotation.x, Player->rotation.y, Player->rotation.z);
		D3DXMatrixRotationYawPitchRoll(&rotMat, Player->rotation.x / (360 * dt * 100.0f), 0.0f, 0.0f);
	    D3DXMatrixTranslation(&transMat, Player->position.x-1.55, Player->position.y-1.6, Player->position.z-5.0f); //x-1.55 is the value for gun to be directly in the center of the camera
		D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);
		//D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		D3DXMatrixInverse(&invTransMat, 0, &worldMat);
		D3DXMatrixTranspose(&invTransMat, &invTransMat);

		D3DXMATRIX wvp = worldMat * viewMat * projMat;
		D3DXMATRIX wvpit;
		D3DXMatrixInverse(&wvpit, 0, &wvp);
		D3DXMatrixTranspose(&wvpit, &wvpit);

		fx[0]->SetMatrix("WVP", &wvp);
		fx[0]->SetMatrix("WVPIT", &wvpit);
		fx[0]->SetMatrix("World", &worldMat);
		fx[0]->SetMatrix("View", &viewMat);
		fx[0]->SetMatrix("Projection", &projMat);
		fx[0]->SetMatrix("WorldInverseTranspose", &invTransMat);

		for( short e = 0; e < Player->objectMesh->numMaterials; ++e )
		{
			fx[0]->SetTexture("gTexture", Player->objectMesh->textures[e]);
			fx[0]->CommitChanges();
			Player->objectMesh->p_Mesh->DrawSubset(e);
		}

		fx[0]->EndPass();
	}
	fx[0]->End();


	fx[0]->SetTechnique(hTech[0]);

	numPasses = 0;
	fx[0]->Begin(&numPasses, 0);

	for(UINT i = 0; i < numPasses; ++i)
	{
		fx[0]->BeginPass(i);

		// Mesh Matrix
		D3DXMatrixScaling(&scaleMat, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotMat, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&transMat, Mansion->position.x, Mansion->position.y - 8.0f, Mansion->position.z);
		D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);
		//D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		D3DXMatrixInverse(&invTransMat, 0, &worldMat);
		D3DXMatrixTranspose(&invTransMat, &invTransMat);

		D3DXMATRIX wvp = worldMat * viewMat * projMat;
		D3DXMATRIX wvpit;
		D3DXMatrixInverse(&wvpit, 0, &wvp);
		D3DXMatrixTranspose(&wvpit, &wvpit);

		fx[0]->SetMatrix("WVP", &wvp);
		fx[0]->SetMatrix("WVPIT", &wvpit);
		fx[0]->SetMatrix("World", &worldMat);
		fx[0]->SetMatrix("View", &viewMat);
		fx[0]->SetMatrix("Projection", &projMat);
		fx[0]->SetMatrix("WorldInverseTranspose", &invTransMat);

		/*for( short e = 0; e < Mansion->objectMesh->numMaterials; ++e )
		{
			fx[0]->SetTexture("gTexture", m_pTexture[0]);
			fx[0]->CommitChanges();
			Mansion->objectMesh->p_Mesh->DrawSubset(e);
		}*/

		fx[0]->SetTexture("gTexture", m_pTexture[0]);
		fx[0]->CommitChanges();
		Mansion->objectMesh->p_Mesh->DrawSubset(0);

		fx[0]->EndPass();
	}
	fx[0]->End();

	//yellowGhost->Render( m_hWnd, viewMat, projMat);
	////if ( yellowGhost->GetIsDead() == true)
	//	greenGhost->Render( m_hWnd, viewMat, projMat);
	////if ( greenGhost->GetIsDead() == true)
	//	blueGhost->Render( m_hWnd, viewMat, projMat);
	////if ( blueGhost->GetIsDead() == true)
	//	redGhost->Render(m_hWnd, viewMat, projMat);
	baseGhost->Render( m_hWnd, viewMat, projMat);

	Player->mPSys->draw(m_hWnd, eyePos, viewMat * projMat); // bullet draw

	//////////////////////////////////////////////////////////////////////////
	// Draw 2D sprites
	//////////////////////////////////////////////////////////////////////////
	// Note: You should only be calling the sprite object's begin and end once, 
	// with all draw calls of sprites between them

	// Call Sprite's Begin to start rendering 2D sprite objects

	//////////////////////////////////////////////////////////////////////////
	// Matrix Transformations to control sprite position, scale, and rotate
	// Set these matrices for each object you want to render to the screen
	//////////////////////////////////////////////////////////////////////////

	/*
	//drawing the sprite
	*/
	//we can specify flags that determine how subsequent sprites will be rendered. 
	//A common flag here is to say that our sprites are going to be rendered with 
	//alpha blending available D3DXSPRITE_ALPHABLEND. 
	m_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Scaling scaleMat
	// Rotation on Z axis, value in radians, converting from degrees rotMat
	// Translation transMat
	// Multiply scale and rotation, store in scale
	// Multiply scale and translation, store in world worldMat

	// Set Transform

	D3DXMatrixIdentity(&transMat);
	D3DXMatrixIdentity(&scaleMat);
	D3DXMatrixIdentity(&rotMat);
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixScaling(&scaleMat, 1.0f, 1.0f, 0.0f);
	D3DXMatrixRotationZ(&rotMat, D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&transMat, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);
	// Set Transform for the object m_pD3DSprite
	m_pD3DSprite->SetTransform(&worldMat);



	// Draw the texture with the sprite object
	//m_pD3DSprite->Draw(m_pTexture[1], 0, &D3DXVECTOR3(m_imageInfo.Width * 0.5f, 
	//	m_imageInfo.Height * 0.5f, 0.0f), 0,
	//	D3DCOLOR_ARGB(255, 255, 255, 255));
}

gameState->Render(m_pD3DSprite);
	// End drawing 2D sprites
	m_pD3DSprite->End();

	//////////////////////////////////////////////////////////////////////////
	// Draw Text
	//////////////////////////////////////////////////////////////////////////

	// Calculate RECT structure for text drawing placement, using whole screen
	RECT rect;
	GetWindowRect(m_hWnd, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// Draw Text, using DT_TOP, DT_RIGHT for placement in the top right of the
	// screen.  DT_NOCLIP can improve speed of text rendering, but allows text
	// to be drawn outside of the rect specified to draw text in.
	/*char debugMessage[256];
	sprintf( debugMessage, "X: %f\nY: %f\nZ: %f", 
		eyePos.x, eyePos.y, eyePos.z );*/

	/*char message[256];
	sprintf( message,"Team Madness" );
	m_pD3DFont->DrawText(0, debugMessage, -1, &rect, 
                  DT_TOP | DT_LEFT | DT_NOCLIP, 
                  D3DCOLOR_ARGB(255, 255, 255, 255));*/



	// EndScene, and Present the back buffer to the display buffer
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);


	//*************************************************************************

}

void CDirectXFramework::Shutdown()
{
	//*************************************************************************
	// Release COM objects in the opposite order they were created in

	if(gCamera)
	{
		delete gCamera;
		gCamera = 0;
	}

	// Texture
	//SAFE_RELEASE(m_pTexture)

	// Sprite
	SAFE_RELEASE(m_pD3DSprite)

	// Font
	SAFE_RELEASE(m_pD3DFont)

	// 3DDevice	
	SAFE_RELEASE(m_pD3DDevice)

	// 3DObject
	SAFE_RELEASE(m_pD3DObject)
	//*************************************************************************

}

void CDirectXFramework::loadMesh(LPCWSTR fileName, Mesh** meshObject)
{
	// Create a Temp Mesh
	Mesh* temp = new Mesh();

	// Load Mesh to Temp
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, m_pD3DDevice, &adjBuffer, &matBuffer, &effBuffer, &temp->numMaterials, &temp->p_Mesh);

	// Vertex Declarations
	D3DVERTEXELEMENT9 elems[65];
	UINT numElems = 0;
	d3dVertexDecl->GetDeclaration( elems, &numElems );

	ID3DXMesh* t = 0;

	temp->p_Mesh->CloneMesh( D3DXMESH_MANAGED, elems, m_pD3DDevice, &t );
	temp->p_Mesh->Release();
	temp->p_Mesh = t;

	temp->p_Mesh->Optimize(D3DXMESH_MANAGED,
									(DWORD*)adjBuffer->GetBufferPointer(),
									0, 0, 0,
									&temp->p_Mesh);
	
	// Compute Normals (Doesn't Always Look Good)
	//D3DXComputeNormals( temp->p_Mesh, NULL );
	
	// Check for Materials already in the Mesh
	if( matBuffer )
	{
		D3DXMATERIAL* mat = (D3DXMATERIAL*)matBuffer->GetBufferPointer();
		temp->textures.clear();
		temp->textures.reserve( temp->numMaterials );

		short nummaterials = temp->GetNumMaterials();

		for( short i = 0; i < temp->GetNumMaterials(); ++i )
		{
			temp->textures.push_back( NULL );

			if( mat[i].pTextureFilename != 0 )
			{
				D3DXCreateTextureFromFileA( m_pD3DDevice, (LPCSTR)mat[i].pTextureFilename, &temp->textures[i] );
			}
		}
	}
	// Else it will just appear black (with Toon Shading)

	// Load Mesh Object with the temp variables
	*meshObject = temp;
}


void CDirectXFramework::createGroundBox(hkpWorld* world, float scaleX, float scaleY, float scaleZ, float posX, float posY, float posZ)
{
	// Create a ground area
	hkVector4 halfExtents(scaleX, scaleY, scaleZ);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set its properties
	hkpRigidBodyCinfo ci;
	ci.m_shape = boxShape;
	ci.m_position = hkVector4(posX, posY, posZ);
	ci.m_motionType = hkpMotion::MOTION_FIXED;
	ci.m_friction = 1.0f;

	// Create the rigid body
	hkpRigidBody* rigidBody = new hkpRigidBody(ci);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();

	// Remove reference and add the rigidbody to the world
	world->addEntity(rigidBody)->removeReference();

}

void CDirectXFramework::UpdateCamera(float dt)
{
	D3DXVECTOR3 tempPos;
	D3DXMATRIX	tempRot;
	D3DXVECTOR3 tempChange;

	D3DXMatrixIdentity(&tempRot);

	D3DXMatrixRotationY(&tempRot, D3DXToRadian(Player->rotation.x));

	tempPos = D3DXVECTOR3(0.0f, 0.5f, -1.0f);

	D3DXVec3TransformCoord(&tempChange, &tempPos, &tempRot);
	// Initialize View Matrix
	eyePos								= D3DXVECTOR3(0.0f, 0.5f, 0.0f ) + D3DXVECTOR3(Player->position.x, Player->position.y, Player->position.z);		// Camera Position
	lookAt								= D3DXVECTOR3(Player->position.x, Player->position.y, Player->position.z) + tempChange;							// Position camera is viewing
	upVec								= D3DXVECTOR3(0.0f, 1.0f, 0.0f);																				// Rotational orientation


	// Easily calculate the view matrix with 3 intuitive vectors
	D3DXMatrixLookAtLH(&viewMat,											// Returned viewMat
						&eyePos,											// Eye Position
						&lookAt,											// LookAt Position
						&upVec);											// Up Vector

	// Apply the view matrix in the scene
	//m_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projMat,									// Return Projection Matrix
								D3DXToRadian(65.0f),						// Field of View
								(float)screenWidth / (float)screenHeight,	// Aspect Ratio
								1.0f,										// Near Plane
								1000.0f);


	// Apply the projection matrix in the scene
	//m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &projMat);

	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
}

void CDirectXFramework::playerControls(float dt)
{
	m_pDInput->getInput();

	//OMFG@W0RKINGP3WP3W
	static float delay = 0.0f;
	/*if( gDInput->keyDown(DIK_SPACE) && delay <= 0.0f)|
	{												   |
		delay = 0.3f;								   |
		Player->mPSys->addParticle();				   | this is the same as the one below, only using spacebar to shoot
	}												   |
	delay -= dt;									   |*/	

	if( m_pDInput->isButtonDown(0) && delay <= 0.0f)
	{
		delay = 0.3f;
		Player->mPSys->addParticle(eyePos, eyePos, lookAt);
	}
	delay -= dt;

	//switching from green to blue bullets
	if( m_pDInput->keyPress(DIK_C) )
	{
		if(type == green)
		type = blue;
		else if(type == blue)
			type = red;
		else if(type == red)
			type = green;

		Player->changeGunType(type);
	}

	if( m_pDInput->keyPress(DIK_V) )
	{
		if(type == green)
		type = red;
		else if(type == blue)
			type = green;
		else if(type == red)
			type = blue;

		Player->changeGunType(type);
	}
	/************end of cycling stuff*/
	// Moving Forward and Backward
	if(m_pDInput->keyDown(DIK_W))
	{	
		D3DXVECTOR3 direction; // where player is going to move
		D3DXVec3Normalize(&direction, &(eyePos - lookAt));
		Player->velUD = -5.0f * direction.z; // speed (how fast) * direction (which way)
		Player->velLR = 5.0f * direction.x;
	}
	else if(m_pDInput->keyDown(DIK_S))
	{	
		D3DXVECTOR3 direction;
		D3DXVec3Normalize(&direction, &(eyePos - lookAt));
		Player->velUD = 5.0f * direction.z;
		Player->velLR = -5.0f * direction.x;
	}

	// Moving Right and Left
	else if(m_pDInput->keyDown(DIK_D))
	{
		D3DXVECTOR3 direction;
		D3DXVec3Cross(&direction, &(eyePos - lookAt), &upVec);
		D3DXVec3Normalize(&direction, &direction);
		Player->velLR = -5.0f * direction.x;
		Player->velUD = 5.0f * direction.z;

	}
	else if(m_pDInput->keyDown(DIK_A))
	{	
		D3DXVECTOR3 direction;
		D3DXVec3Cross(&direction, &(eyePos - lookAt), &upVec);
		D3DXVec3Normalize(&direction, &direction);
		Player->velLR = 5.0f * direction.x;
		Player->velUD = -5.0f * direction.z;
	}

	else if(!m_pDInput->keyDown(DIK_W) && !m_pDInput->keyDown(DIK_S) || 
		(!m_pDInput->keyDown(DIK_D) && !m_pDInput->keyDown(DIK_A)))
	{
		Player->velUD = 0.0f;
		Player->velLR = 0.0f;
	}
	/*else if(!m_pDInput->keyDown(DIK_D) && !m_pDInput->keyDown(DIK_A))
	{
		Player->velLR = 0.0f;
	}*/

	if(m_pDInput->keyDown(DIK_SPACE))
	{
		Player->wantJump = true;
		Player->jumpTimer = 0.0f;
	}
	else if(!m_pDInput->keyDown(DIK_SPACE))
	{
		Player->wantJump = false;
	}

	Player->rotation.x += m_pDInput->getMouseMovingX();

	Player->rotation.y += m_pDInput->getMouseMovingY();

	if(Player->rotation.x >= 360.0f)
		Player->rotation.x = 0.0f;
	else if(Player->rotation.x <= 0.0f)
		Player->rotation.x = 360.0f;
}
