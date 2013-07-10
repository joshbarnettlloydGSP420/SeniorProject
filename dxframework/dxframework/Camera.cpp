#include "Camera.h"


Camera::Camera(void)
{
	// The position of our camera
	eyePos = D3DXVECTOR3(0.0f, 1.0f, 2.0f);

	// The lookat target of our camera
	lookAt = eyePos + D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	// Up vector
	upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera(void)
{
}

bool Camera::create(IDirect3DDevice9* device, D3DXMATRIX view, D3DXMATRIX projection, int screenWidth, int screenHeight, float nearView, float farView)
{

	// the aspect ratio of the screen
	float aspect = 1.333f; 

	// Setup the Projection Matrix
    D3DXMatrixLookAtLH(&view, 
						&eyePos, 
						&lookAt, 
						&upVec);

	// Apply the view in the scene
	//device->SetTransform(D3DTS_VIEW, &view);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projection,									// Return Projection Matrix
								D3DXToRadian(0.0f),							// Field of View
								aspect,										// Aspect Ratio
								nearView,									// Near Plane
								farView);									// Far Plane


    // Set the Projection
	//device->SetTransform(D3DTS_PROJECTION, &projection);

	// thats a thing
	//device->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	return true;
}
		
//void Camera::setPosition(D3DXVECTOR3 newPosition)
//{
//	position = newPosition;
//	resetView();
//}
//
//void Camera::setLookAt(D3DXVECTOR3 newTarget)
//{
//	target = newTarget;	
//	resetView();
//} 
//
//void Camera::resetView(){
//	//Setup the View
//	D3DXMatrixLookAtLH(&viewMatrix, 
//						&position,		//camera's position
//						&target,		//camera's target
//						&D3DXVECTOR3(0.0f, 1.0f, 0.0f));// the up direction
//	//Set the View
//	myDevice->SetTransform(D3DTS_VIEW, &viewMatrix);
//}

void Camera::Update(IDirect3DDevice9* device, D3DXMATRIX view, D3DXMATRIX projection, D3DXVECTOR4 target, int screenWidth, int screenHeight, float dt)
{
		// Initialize View Matrix
	eyePos								= D3DXVECTOR3(target.x, target.y + 1.5f, target.z - 2.0f);	// Camera Position
	lookAt								= D3DXVECTOR3(target.x, target.y, target.z + 1.0f);			// Position camera is viewing
	upVec								= D3DXVECTOR3(0.0f, 1.0f, 0.0f);							// Rotational orientation

	// Easily calculate the view matrix with 3 intuitive vectors
	D3DXMatrixLookAtLH(&view,											// Returned viewMat
						&eyePos,											// Eye Position
						&lookAt,											// LookAt Position
						&upVec);											// Up Vector

	// Apply the view matrix in the scene
	//device->SetTransform(D3DTS_VIEW, &view);

	// Initialize perspective projection matrix, this creates view frustum
	D3DXMatrixPerspectiveFovLH(&projection,									// Return Projection Matrix
								D3DXToRadian(65.0),							// Field of View
								(float)screenWidth / (float)screenHeight,	// Aspect Ratio
								1.0f,										// Near Plane
								1000.0f);


	// Apply the projection matrix in the scene
	//device->SetTransform(D3DTS_PROJECTION, &projection);
}

