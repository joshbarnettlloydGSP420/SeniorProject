#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <string>

class Sprite2D
{
public:
	Sprite2D(void);
	virtual ~Sprite2D(void);

	bool loadSprite(IDirect3DDevice9* m_pD3DDevice, LPCSTR filename);

	void render(ID3DXSprite* m_pD3DSprite);
	void setPosition(int x, int y);

private:
	//////////////////////////////////////////////////////////////////////////
	// Sprite Variables														//
	//////////////////////////////////////////////////////////////////////////
	IDirect3DTexture9*				m_pTexture[10];		// Texture Object for a sprite
	D3DXIMAGE_INFO					m_imageInfo;	// File details of a texture

	//////////////////////////////////////////////////////////////////////////
	// Matricies															//
	//////////////////////////////////////////////////////////////////////////
	D3DXMATRIX	viewMatrix;
	D3DXMATRIX	projMatrix;
	D3DXMATRIX	invTransMatrix;
	D3DXMATRIX	transMatrix;				// the translation matrix
	D3DXMATRIX	rotationMatrix;				// the rotation matrix
	D3DXMATRIX	scaleMatrix;				// the scale matrix
	D3DXMATRIX	worldMatrix;				// the world matirx

	IDirect3DDevice9* device;
};
