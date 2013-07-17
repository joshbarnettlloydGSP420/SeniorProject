#include "Sprite2D.h"

Sprite2D::Sprite2D(void)
{
}

Sprite2D::~Sprite2D(void)
{
}

bool Sprite2D::loadSprite(IDirect3DDevice9* m_pD3DDevice, LPCSTR filename)
{
	device = m_pD3DDevice;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Loading Textures																						 //
	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	D3DXCreateTextureFromFileEx(device, "test.tga", 0, 0, 0, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), 
		&m_imageInfo, 0, &m_pTexture[1]);

	return true;
}

void Sprite2D::render(ID3DXSprite* m_pD3DSprite)
{
	// Set Transform

	D3DXMatrixIdentity(&transMatrix);
	D3DXMatrixIdentity(&scaleMatrix);
	D3DXMatrixIdentity(&rotationMatrix);
	D3DXMatrixIdentity(&worldMatrix);

	D3DXMatrixScaling(&scaleMatrix, 1.0f, 1.0f, 0.0f);
	D3DXMatrixRotationZ(&rotationMatrix, D3DXToRadian(0.0f));
	D3DXMatrixTranslation(&transMatrix, 100.0f, 300.0f, 0.0f);

	D3DXMatrixMultiply(&scaleMatrix, &scaleMatrix, &rotationMatrix);
	D3DXMatrixMultiply(&worldMatrix, &scaleMatrix, &transMatrix);

	// Set Transform for the object m_pD3DSprite
	m_pD3DSprite->SetTransform(&worldMatrix);

	// Draw the texture with the sprite object
	m_pD3DSprite->Draw(m_pTexture[1], 0, 
		&D3DXVECTOR3(m_imageInfo.Width * 0.5f, m_imageInfo.Height * 0.5f, 0.0f), 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}