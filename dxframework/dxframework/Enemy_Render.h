#pragma once

//////////////////////////////////////////////////////////////////////////
// DirectX 9 headers and library files								    //
//////////////////////////////////////////////////////////////////////////
#include <d3d9.h>
#include <d3dx9.h>
#include "Mesh.h"
#include "Object_Player.h"

class Enemy_Render
{
private:
	IDirect3DDevice9* device;

	// Handles
	D3DXHANDLE						hTech[10];
	D3DXHANDLE						hWVP;
	HANDLE*							pSharedHandle;

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

	// Vertex Declaration
	IDirect3DVertexDeclaration9*	vertexDec;

	// Buffers
	ID3DXBuffer*					adjBuffer;
	ID3DXBuffer*					matBuffer;
	ID3DXBuffer*					effBuffer;

public:
	Enemy_Render(void);
	~Enemy_Render(void);

	void Init( IDirect3DDevice9* m_pD3DDevice, IDirect3DVertexDeclaration9* d3dVertexDecl );
	void Render( Object_Player* enemy );
	void LoadMesh(LPCSTR fileName, Mesh* meshObject);
};

