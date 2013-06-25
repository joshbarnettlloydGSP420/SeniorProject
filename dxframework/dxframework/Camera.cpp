#include "Camera.h"


Camera::Camera(void)
{
}

Camera::~Camera(void)
{
}

bool Camera::create(LPDIRECT3DDEVICE9& device, float nearView, float farView)
{
	// The position of our camera
	position = D3DXVECTOR3(0.0f, 1.0f, 2.0f);

	// The lookat target of our camera
	target = position + D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// Up vector
	upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// the aspect ratio of the screen
	float aspect = 1.333f; 

	// Setup the Projection Matrix
    D3DXMatrixLookAtLH(&viewMatrix, 
						&position, 
						&target, 
						&upVec);

	// Apply the view in the scene
	device->SetTransform(D3DTS_VIEW, &viewMatrix);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projectionMatrix,									// Return Projection Matrix
								D3DXToRadian(0.0f),						// Field of View
								aspect,										// Aspect Ratio
								nearView,										// Near Plane
								farView);


    // Set the Projection
	device->SetTransform(D3DTS_PROJECTION, &projectionMatrix);

	// thats a thing
	device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

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



