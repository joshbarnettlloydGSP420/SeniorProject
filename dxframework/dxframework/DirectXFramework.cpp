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
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &viewMat);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projMat,									// Return Projection Matrix
								D3DXToRadian(65.0f),						// Field of View
								(float)screenWidth / (float)screenHeight,	// Aspect Ratio
								1.0f,										// Near Plane
								1000.0f);


	// Apply the projection matrix in the scene
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &projMat);

	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Loading Textures																						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DXCreateSprite(m_pD3DDevice, &m_pD3DSprite);

	// create a TEXTURE object
	D3DXCreateTextureFromFileEx(m_pD3DDevice, "Metal_Texture.jpg", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &m_pTexture[0]);

	D3DXCreateTextureFromFileEx(m_pD3DDevice, "test.tga", 0, 0, 0, 0,
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
	Player = new Object_Base();
	Player->position = D3DXVECTOR4(0.0f, 15.0f, 0.0f, 0.0f);
	Player->shape = CAPSULE;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load Shader Effects																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// Toon Effects Shader
	ID3DXBuffer* ErrorMessage = 0;
	D3DXCreateEffectFromFile(m_pD3DDevice,
							"ToonColored.fx",
							0,
							0,
							D3DXSHADER_DEBUG,
							0,
							&fx[0],
							&ErrorMessage);
	if( ErrorMessage )
	{
		char error[256];
		ZeroMemory( error, 256 );
		strcpy_s( error, (char*)ErrorMessage->GetBufferPointer() );
		MessageBox(0, (LPCSTR)error, "Shader Error", MB_OK );
	}

	hTech[0] = fx[0]->GetTechniqueByName("ToonColored");


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create 3D Mesh From X																				 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Load Test Mesh
	loadMesh("Dwarf.X", &Player->objectMesh);


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// Create Havok Object																					 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Havok
	havok = new HavokCore(true);

	// Locking is necessary to make sure no two threads are trying to change the world at the same time
	havok->getWorld()->lock();

	Player->createHavokObject(havok->getWorld());
	createGroundBox(havok->getWorld());	
	
	havok->getWorld()->unlock();

}

void CDirectXFramework::Update(float dt)
{
	havok->stepSimulation(dt);
	Player->Update(dt);
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
		D3DXMatrixScaling(&scaleMat, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationYawPitchRoll(&rotMat, 0.0f, 0.0f, 0.0f);
		D3DXMatrixTranslation(&transMat, Player->position.x, Player->position.y, Player->position.z);
		D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
		D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);

		D3DXMatrixInverse(&invTransMat, 0, &worldMat);
		D3DXMatrixTranspose(&invTransMat, &invTransMat);

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
	D3DXMatrixTranslation(&transMat, 100.0f, 300.0f, 0.0f);
	D3DXMatrixMultiply(&scaleMat, &scaleMat, &rotMat);
	D3DXMatrixMultiply(&worldMat, &scaleMat, &transMat);
	// Set Transform for the object m_pD3DSprite
	m_pD3DSprite->SetTransform(&worldMat);



	// Draw the texture with the sprite object
	m_pD3DSprite->Draw(m_pTexture[1], 0, &D3DXVECTOR3(m_imageInfo.Width * 0.5f, 
		m_imageInfo.Height * 0.5f, 0.0f), 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));


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
	char message[256];
	sprintf( message,"Team Madness" );
	m_pD3DFont->DrawText(0, message, -1, &rect, 
                  DT_TOP | DT_LEFT | DT_NOCLIP, 
                  D3DCOLOR_ARGB(255, 255, 255, 255));



	// EndScene, and Present the back buffer to the display buffer
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);


	//*************************************************************************

}

void CDirectXFramework::Shutdown()
{
	//*************************************************************************
	// Release COM objects in the opposite order they were created in

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

void CDirectXFramework::loadMesh(LPCSTR fileName, Mesh** meshObject)
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

void CDirectXFramework::createGroundBox(hkpWorld* world)
{
	// Create a ground area
	hkVector4 halfExtents(20.0f, 2.0f, 30.0f);
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set its properties
	hkpRigidBodyCinfo ci;
	ci.m_shape = boxShape;
	ci.m_position = hkVector4(0.0f, 0.0f, 0.0f);
	ci.m_motionType = hkpMotion::MOTION_FIXED;

	// Create the rigid body
	hkpRigidBody* rigidBody = new hkpRigidBody(ci);

	// No longer need the reference on the boxShape, as the rigidBody now owns it
	boxShape->removeReference();

	// Remove reference and add the rigidbody to the world
	world->addEntity(rigidBody)->removeReference();

}

void CDirectXFramework::playerUpdate(float dt)
{
	// Need to sync it
}