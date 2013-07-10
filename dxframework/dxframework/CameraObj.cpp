#include "CameraObj.h"


CameraObj::CameraObj(void)
{
	D3DXMatrixIdentity( &viewMat );
	D3DXMatrixIdentity( &projMat );
	D3DXMatrixIdentity( &viewProjMat );

	eyePos = D3DXVECTOR3(0.0f, 1.0f, 2.0f);				// The position of our camera
	lookAt = eyePos + D3DXVECTOR3(0.0f, 0.0f, 1.0f);	// The lookat target of our camera
	upVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// Up vector
}


CameraObj::~CameraObj(void)
{

}

void CameraObj::createCamera(float farPlane, float nearPlane, float aspect, float FOV)
{
	D3DXMatrixPerspectiveFovLH(&projMat, FOV, aspect, nearPlane, farPlane);
	viewProjMat = viewMat * projMat;
}

void CameraObj::updateCamera()
{
	D3DXVec3Normalize(&lookAt, &lookAt);
	D3DXVec3Normalize(&eyePos, &eyePos);
	D3DXVec3Normalize(&upVec, &upVec);

	buildView();
	buildFrustum();

	D3DXMatrixMultiply(&viewProjMat, &viewMat, &projMat);
}

void CameraObj::setLook(D3DXVECTOR3 lookingAt, D3DXVECTOR3& position, D3DXVECTOR3& up)
{
	lookAt = lookingAt - position;
	D3DXVec3Normalize(&lookAt, &lookAt);

	setPosition(position);

	setUp(up);

}

void CameraObj::setPosition(D3DXVECTOR3 eyePosition)
{
	eyePos = D3DXVECTOR3(eyePosition.x, eyePosition.y + 1.5f, eyePosition.z - 2.0f);
}

void CameraObj::setUp(D3DXVECTOR3 upVector)
{
	upVec = upVector;
}

void CameraObj::followPoint()
{

}

void CameraObj::buildView()
{
	D3DXVECTOR3 right;
	D3DXVec3Cross( &right, &lookAt, &upVec);
	
	float x = -D3DXVec3Dot(&eyePos, &right);
	float y = -D3DXVec3Dot(&eyePos, &upVec);
	float z = -D3DXVec3Dot(&eyePos, &lookAt);

	viewMat(0,0) = right.x;
	viewMat(1,0) = right.y;
	viewMat(2,0) = right.z;
	viewMat(3,0) = x;
				 
	viewMat(0,1) = upVec.x;
	viewMat(1,1) = upVec.y;
	viewMat(2,1) = upVec.z;
	viewMat(3,1) = y;
				 
	viewMat(0,2) = lookAt.x;
	viewMat(1,2) = lookAt.y;
	viewMat(2,2) = lookAt.z;
	viewMat(3,2) = z;
				 
	viewMat(0,3) = 0.0f;
	viewMat(1,3) = 0.0f;
	viewMat(2,3) = 0.0f;
	viewMat(3,3) = 1.0f;

}

void CameraObj::buildFrustum()
{
	D3DXMATRIX vp = viewMat * projMat;

	D3DXVECTOR4 col0( vp(0,0), vp(1,0), vp(2,0), vp(3,0) );
	D3DXVECTOR4 col1( vp(0,1), vp(1,1), vp(2,1), vp(3,1) );
	D3DXVECTOR4 col2( vp(0,2), vp(1,2), vp(2,2), vp(3,2) );
	D3DXVECTOR4 col3( vp(0,3), vp(1,3), vp(2,3), vp(3,3) );
														 
	Frustum[0] = (D3DXPLANE)(col3 + col2);	// Near
	Frustum[1] = (D3DXPLANE)(col3 - col2);  // Far
	Frustum[2] = (D3DXPLANE)(col3 + col0);  // Left
	Frustum[3] = (D3DXPLANE)(col3 - col0);  // Right
	Frustum[4] = (D3DXPLANE)(col3 + col1);  // Top
	Frustum[5] = (D3DXPLANE)(col3 - col1);  // Bottom

	for( byte i = 0; i < 6; ++i)
		D3DXPlaneNormalize( &Frustum[i], &Frustum[i]);
}