#pragma once

//////////////////////////////////////////////////////////////////////////
// DirectX 9 headers and library files								    //
//////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "HavokCore.h"
#include "DirectInput.h"
#include "Object_Base.h"
#include "Object_Player.h"
#include "CameraObj.h"



// Macro to release COM objects fast and safely
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}


// Enums

class CDirectXFramework
{
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

	//////////////////////////////////////////////////////////////////////////
	// Screen Variables														//
	//////////////////////////////////////////////////////////////////////////
	bool						m_bFullscreen;
	bool						FPSDisplay;

	int							screenWidth;
	int							screenHeight;

	//////////////////////////////////////////////////////////////////////////
	// Input Manager														//
	//////////////////////////////////////////////////////////////////////////
	DirectInput*				m_pDInput;


	//////////////////////////////////////////////////////////////////////////
	// Camera																//
	//////////////////////////////////////////////////////////////////////////
	CameraObj*						camera;

	//////////////////////////////////////////////////////////////////////////
	// Structs																//
	//////////////////////////////////////////////////////////////////////////
	
	// Vertex
	struct Vertex
	{
		D3DXVECTOR3				pos;
		D3DXVECTOR3				norm;
		D3DXVECTOR2				uv;
	}tempPos;

	//////////////////////////////////////////////////////////////////////////
	// Shape Variables														//
	//////////////////////////////////////////////////////////////////////////

	UINT						Length;

	// Basic
	IDirect3DVertexBuffer9*		mesh_vb;
	IDirect3DIndexBuffer9*		mesh_ib;

	// Cube
	Vertex						cubeVerts[24];
	WORD						cubeIndic[36];
	IDirect3DVertexBuffer9*		cube_vb;
	IDirect3DIndexBuffer9*		cube_ib;

	// Pyrimid
	Vertex						pyrmVerts[16];
	WORD						pyrmIndic[18];
	IDirect3DVertexBuffer9*		pyrm_vb;
	IDirect3DIndexBuffer9*		pyrm_ib;

	// Triangle
	IDirect3DVertexBuffer9*		tri_vb;
	IDirect3DIndexBuffer9*		tri_ib;


	//////////////////////////////////////////////////////////////////////////
	// 3D Variables													        //
	//////////////////////////////////////////////////////////////////////////

	// Lights
	D3DLIGHT9						light;

	// Camera
	D3DXVECTOR3						eyePos;
	D3DXVECTOR3						lookAt;
	D3DXVECTOR3						upVec;

	float							mCameraRotation;
	float							mCameraRadius;
	float							mCameraHeight;

	// Handles
	D3DXHANDLE						hTech[10];
	D3DXHANDLE						hWVP;
	HANDLE*							pSharedHandle;

	// Vertex Declaration
	IDirect3DVertexDeclaration9*	d3dVertexDecl;

	// Double Words
	DWORD							fillMode;
	DWORD							Usage;
	DWORD							FVF;
	DWORD							mNumGridVertices;
	DWORD							mNumGridTriangles;

	// Pool
	D3DPOOL							Pool;

	// Materials
	D3DMATERIAL9					m_pMaterial[10];
	DWORD							numMaterials;

	// Buffers
	ID3DXBuffer*					adjBuffer;
	ID3DXBuffer*					matBuffer;
	ID3DXBuffer*					effBuffer;

	// Mesh
	ID3DXMesh*						testMesh;


	//////////////////////////////////////////////////////////////////////////
	// Shaders																//
	//////////////////////////////////////////////////////////////////////////
	ID3DXEffect*					fx[10];

	//////////////////////////////////////////////////////////////////////////
	// Matricies															//
	//////////////////////////////////////////////////////////////////////////
	D3DXMATRIX						transMat;
	D3DXMATRIX						rotMat;
	D3DXMATRIX						scaleMat;
	D3DXMATRIX						worldMat;
	D3DXMATRIX						viewMat;
	D3DXMATRIX						projMat;
	D3DXMATRIX						invTransMat;

	//////////////////////////////////////////////////////////////////////////
	// Font Variables														//
	//////////////////////////////////////////////////////////////////////////
	ID3DXFont*						m_pD3DFont;			// Font Object

	//////////////////////////////////////////////////////////////////////////
	// Sprite Variables														//
	//////////////////////////////////////////////////////////////////////////
	ID3DXSprite*					m_pD3DSprite;		// Sprite Object
	IDirect3DTexture9*				m_pTexture[10];		// Texture Object for a sprite
	D3DXIMAGE_INFO					m_imageInfo;		// File details of a texture

	//////////////////////////////////////////////////////////////////////////
	// Havok																//
	//////////////////////////////////////////////////////////////////////////
	HavokCore*						havok;

	// Timer
	hkStopwatch						stopWatch;
	hkReal							lastTime;

	//////////////////////////////////////////////////////////////////////////
	// Objects																//
	//////////////////////////////////////////////////////////////////////////
	Object_Player*					Player;

	Object_Base*					Mansion;


public:

	CDirectXFramework(void);
	~CDirectXFramework(void);

	HWND getMainWnd();

	void Init(HWND& hWnd, HINSTANCE& hInst, bool bWindowed);

	void Update(float dt);

	void Render(float dt);

	void Shutdown();

	void loadMesh(LPCSTR fileName, Mesh** meshObject);

	void createGroundBox(hkpWorld* world);

	void UpdateCamera(float dt);

	void playerControls(float dt);
};
