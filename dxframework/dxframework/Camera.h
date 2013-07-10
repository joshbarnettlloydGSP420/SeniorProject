#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);

	bool create(IDirect3DDevice9* device, D3DXMATRIX view, D3DXMATRIX projection, int screenWidth, int screenHeight, float nearView, float farView);
	/*void setLookAt(D3DXVECTOR3 newTarget);
	void setPosition(D3DXVECTOR3 newPosition);*/
	void Update(IDirect3DDevice9* device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR4 target, int screenWidth, int screenHeight, float dt);
	/*void resetView();*/
	// GET AND SET VIEW MATRIX

	// THEN MAKE THESE PRIVATE
	D3DXVECTOR3 lookAt;			// Camera Target
	D3DXVECTOR3 eyePos;			// Position of camera
	D3DXVECTOR3 upVec;
	float nearClip;
	float farClip;
	LPDIRECT3DDEVICE9 myDevice;
};
