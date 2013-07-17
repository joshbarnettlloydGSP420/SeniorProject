#include "Camera.h"


Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

bool Camera::create(IDirect3DDevice9* device, float nearView, float farView, HWND* hWnd)
{
	myDevice = device;
	nearClip = nearView;//nearest point at which the objects stop rendering 
	farClip = farView;//farthest point at which the objects stop rendering

	//the position of our camera
	position.x = 0.0;
	position.y = 0.0f;
	position.z = 0.0f;

	//the lookat target of our camera
	target.x = 100.0f;
	target.y = 100.0f;
	target.z = 100.0f;

	//RECT
	// Find the width and height of window using hWnd and GetWindowRect()
	RECT windowSizeRect;
	GetWindowRect(*hWnd, &windowSizeRect);
	screenWidth = windowSizeRect.right - windowSizeRect.left;
	screenHeight = windowSizeRect.bottom - windowSizeRect.top;

	//Set the Projection
	myDevice->SetTransform(D3DTS_VIEW, &viewMatrix);

	//Setup the Projection Matrix
    D3DXMatrixPerspectiveFovLH(&projectionMatrix, 
		D3DX_PI / 4.0f, (float)screenWidth / (float)screenHeight, nearClip, farClip);

	// Apply the projection matrix in the scene
	myDevice->SetTransform(D3DTS_PROJECTION, &projectionMatrix);
	myDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	return true;
}
		
void Camera::setPosition(D3DXVECTOR3 newPosition)
{
	position = newPosition;
	resetView();
}

void Camera::setLookAt(D3DXVECTOR3 newTarget)
{
	target = newTarget;	
	resetView();
} 

void Camera::resetView(){
	//Setup the View
	D3DXMatrixLookAtLH(&viewMatrix, 
						&position,		//camera's position
						&target,		//camera's target
						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));// the up direction
	//Set the View
	myDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
}


