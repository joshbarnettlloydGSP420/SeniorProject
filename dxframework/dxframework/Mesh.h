#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#pragma comment (lib, "D3dxof.lib")

class Mesh
{
private:
	IDirect3DDevice9* device;
	ID3DXMesh*	p_Mesh;
	std::vector<IDirect3DTexture9*> textures;
	std::vector<D3DXMATERIAL> materials;
	DWORD numMaterials;
	D3DXVECTOR3 position, rotation, scale;
	D3DXMATRIX world;

	// Buffers
	ID3DXBuffer*					adjBuffer;
	ID3DXBuffer*					matBuffer;
	ID3DXBuffer*					effBuffer;

	// Vertex Declaration
	IDirect3DVertexDeclaration9*	d3dVertexDecl;

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

	// Handles
	D3DXHANDLE						hTech[10];
	D3DXHANDLE						hWVP;
	HANDLE*							pSharedHandle;

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

	// Basic
	IDirect3DVertexBuffer9*		mesh_vb;
	IDirect3DIndexBuffer9*		mesh_ib;

	// Vertex
	struct Vertex
	{
		D3DXVECTOR3				pos;
		D3DXVECTOR3				norm;
		D3DXVECTOR2				uv;
	};


	//////////////////////////////////////////////////////////////////////////
	// Shaders																//
	//////////////////////////////////////////////////////////////////////////
	ID3DXEffect*					fx[10];



public:
	Mesh(void);
	~Mesh(void);

	void ComputeWorld();
	void Init(LPCSTR fileName, IDirect3DDevice9* m_pD3DDevice);
	void Render();

	void Shutdown();

	void SetPosition(D3DXVECTOR3 newPosition) { position = newPosition;};
	void SetRotation(D3DXVECTOR3 newRotation) { rotation = newRotation;};
	void SetScaling (D3DXVECTOR3 newScale) { scale = newScale;};

};

