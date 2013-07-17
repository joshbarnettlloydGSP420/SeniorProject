#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Enemy_Movement
{
private:
	D3DXVECTOR4	position;
	float		orientation;
	D3DXVECTOR4	velocity;
	float		rotation;

public:
	Enemy_Movement(void);
	~Enemy_Movement(void);
	Enemy_Movement(D3DXVECTOR4 position, D3DXVECTOR4 velocity, float orientation, float rotation);

	void Update();
	float GetNewOrientation(float currentOrientation, D3DXVECTOR4 velocity);

	float GetOrientation();
	D3DXVECTOR4 GetOrientationAsVector();
	void SetOrientation(float newOrientation);
	D3DXVECTOR4 GetPosition();
	void setPosition( D3DXVECTOR4 newPosition);
	void setVelocity(D3DXVECTOR4 newVelocity);
	D3DXVECTOR4 GetVelocity();
	float GetVelocityLength();
	void NormalizeVelocity();
	float GetRotation();
	void SetRotation( float newRotation);
};

