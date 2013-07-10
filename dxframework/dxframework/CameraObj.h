#pragma once

#include <d3dx9.h>

class CameraObj
{
public:
	CameraObj(void);
	~CameraObj(void);

	void createCamera(float farPlane, float nearPlane, float aspect, float FOV);
	void updateCamera();

	
	void setLook(D3DXVECTOR3 lookingAt, D3DXVECTOR3& position, D3DXVECTOR3& up);
	void setPosition(D3DXVECTOR3 eyePosition);
	void setUp(D3DXVECTOR3 upVector);

	void followPoint();
	void buildView();
	void buildFrustum();

	// Frustum Planes for Culling
	D3DXPLANE Frustum[6];

	// Basic 
	D3DXVECTOR3		eyePos;
	D3DXVECTOR3		lookAt;
	D3DXVECTOR3		upVec;

	D3DXMATRIX		viewMat;
	D3DXMATRIX		projMat;
	D3DXMATRIX		viewProjMat;
};

