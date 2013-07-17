#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>

class Camera
{
public:
	Camera(void);
	~Camera(void);

	bool create(IDirect3DDevice9* device, float nearView, float farView, HWND* hWnd);
	void setLookAt(D3DXVECTOR3 newTarget);
	void setPosition(D3DXVECTOR3 newPosition);
	void resetView();

private:

	D3DXMATRIX viewMatrix; //the view matrix
	D3DXMATRIX projectionMatrix; // the projection matrix
	D3DXVECTOR3 target;		// Camera Target
	D3DXVECTOR3 position;		// Position of camera
	float nearClip;
	float farClip;
	IDirect3DDevice9* myDevice;

	int							screenWidth;
	int							screenHeight;
};
