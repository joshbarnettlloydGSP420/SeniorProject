#include "Enemy_Movement.h"


Enemy_Movement::Enemy_Movement(void)
{
	orientation = 0.0f;
	velocity = D3DXVECTOR4(0, 0, 0, 0);
	rotation = 0.0f;
}

Enemy_Movement::Enemy_Movement(D3DXVECTOR4 position, D3DXVECTOR4 velocity, float orientation, float rotation)
{
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
	this->rotation = rotation;
}

Enemy_Movement::~Enemy_Movement(void)
{
}

void Enemy_Movement::Update()
{
	// update position and orientation
	position += velocity;
	orientation += rotation;
}

float Enemy_Movement::GetNewOrientation( float currentOrientation, D3DXVECTOR4 velocity)
{
	float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	if ( length > 0)
		return (float) atan2(velocity.x, -velocity.y);
	else
		return currentOrientation;
}

float Enemy_Movement::GetOrientation(){	return orientation; }
D3DXVECTOR4 Enemy_Movement::GetOrientationAsVector() {	return D3DXVECTOR4((float) sin(orientation), -(float) cos(orientation), 0, 0);}
void Enemy_Movement::SetOrientation(float newOrientation) { orientation = newOrientation ;}
D3DXVECTOR4 Enemy_Movement::GetPosition() { return position;}
void Enemy_Movement::setPosition( D3DXVECTOR4 newPosition) { position = newPosition; }
void Enemy_Movement::setVelocity(D3DXVECTOR4 newVelocity) {velocity = newVelocity; }
D3DXVECTOR4 Enemy_Movement::GetVelocity(){ return velocity; }
float Enemy_Movement::GetVelocityLength() {return (float) sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));}
void Enemy_Movement::NormalizeVelocity()
{
	float length = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	velocity.x /= length;
	velocity.y /= length;
}
float Enemy_Movement::GetRotation(){ return rotation;}
void Enemy_Movement::SetRotation( float newRotation) { rotation = newRotation; }