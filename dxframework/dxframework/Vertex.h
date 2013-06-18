#include <d3dx9.h>

void InitAllVertexDeclarations();
void DestroyallVertexDeclarations();

//////////////////////////////////////////////////////////////////////////
//Vertex with Position													//
//////////////////////////////////////////////////////////////////////////
struct VertexPos
{
	VertexPos():pos(0.0f, 0.0f, 0.0f){}
	VertexPos(float x, float y, float z):pos(x, y, z){}
	VertexPos(const D3DXVECTOR3& v):pos(v){}

	D3DXVECTOR3 pos;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//Vertex with Position and Color										//
//////////////////////////////////////////////////////////////////////////
struct VertexCol
{
	VertexCol():pos(0.0f, 0.0f, 0.0f), col(0x00000000){}
	VertexCol(float x, float y, float z, D3DCOLOR c):pos(x, y, z), col(c){}
	VertexCol(const D3DXVECTOR3& v, D3DCOLOR c):pos(v), col(c){}

	D3DXVECTOR3 pos;
	D3DCOLOR	col;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//Vertex with Position and Normal										//
//////////////////////////////////////////////////////////////////////////
struct VertexPN
{
	VertexPN():pos(0.0f, 0.0f, 0.0f), norm(0.0f, 0.0f, 0.0f){}
	VertexPN(float x, float y, float z, float nx, float ny, float nz):pos(x, y, z), norm(nx, ny, nz){}
	VertexPN(const D3DXVECTOR3& v, const D3DXVECTOR3& n):pos(v), norm(n){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;

	static IDirect3DVertexDeclaration9* Decl;
};

//////////////////////////////////////////////////////////////////////////
//Vertex with Position, Normal, and TextureCoor							//
//////////////////////////////////////////////////////////////////////////
struct VertexPNT
{
	VertexPNT():pos(0.0f, 0.0f, 0.0f), norm(0.0f, 0.0f, 0.0f), tex0(0.0f, 0.0f){}
	VertexPNT(float x, float y, float z, float nx, float ny, float nz, float u, float v):pos(x, y, z), norm(nx, ny, nz), tex0(u, v){}
	VertexPNT(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2 uv):pos(v), norm(n), tex0(uv){}

	D3DXVECTOR3 pos;
	D3DXVECTOR3 norm;
	D3DXVECTOR2 tex0;

	static IDirect3DVertexDeclaration9* Decl;
};