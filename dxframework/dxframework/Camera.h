#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);

	bool create(LPDIRECT3DDEVICE9& device, float nearView, float farView);
	void setLookAt(D3DXVECTOR3 newTarget);
	void setPosition(D3DXVECTOR3 newPosition);
	void resetView();
	// GET AND SET VIEW MATRIX

	// THEN MAKE THESE PRIVATE
	D3DXMATRIX viewMatrix; //the view matrix
	D3DXMATRIX projectionMatrix; // the projection matrix
	D3DXVECTOR3 target;		// Camera Target
	D3DXVECTOR3 position;		// Position of camera
	D3DXVECTOR3 upVec;
	float nearClip;
	float farClip;
	LPDIRECT3DDEVICE9 myDevice;
};
