#pragma once

#include "Mesh.h"
#include "HavokCore.h"
#include "PSystem.h"

// Enum for deciding what Shape the Object is in Havok
enum HavokPlayerShape
{
	PLAYERNONE			=	0,		// Hav
	PLAYERSPHERE		=	1,		// Havok Sphere
	PLAYERBOX			=	2,		// Havok Box
	PLAYERCAPSULE		=	3		// Havok Capsule
};

enum gunType{green, red, blue};

class Object_Player
{
private:
	AABB psysBox;
	D3DXMATRIX psysWorld;

	void createSphereObject(hkpWorld* world);
	void createBoxObject(hkpWorld* world);
	void createCapsuleObject(hkpWorld* world);
	void stateMachineInit();

public:
	// Variables
	D3DXVECTOR4					position;
	D3DXVECTOR3					rotation;
	D3DXVECTOR3					scale;
	int							health;
	bool						isAlive;
	bool						wantJump;

	// Physics
	float						velUD;
	float						velLR;
	float						jumpTimer;

	// Mesh
	Mesh*						objectMesh;
	
	// Havok

	// Rigid Body
	short						shape;
	hkpCharacterRigidBody*		objectBody;
	hkReal						mass;	
	hkVector4					shapeSize;
	hkpCharacterInput			input;
	hkQuaternion				hk_rotation;
	
	// Movement

	// State Machine
	hkpCharacterState*			state;
	hkpCharacterStateManager*	manager;
	hkpCharacterContext*		context;

	// bullet
	PSystem*					mPSys;
	hkpRigidBody*				bullets[20];

	// Constructor, Destructor, and Methods
	Object_Player();
	~Object_Player(void);

	void Update(float deltaTime, D3DXVECTOR3 eyePos, D3DXVECTOR3 lookAt, hkpWorld* world);

	void convertPosition();

	hkVector4 velocityCalc(float dt);

	void createHavokObject(hkpWorld* world);

	void createBulletHavokObject(hkpWorld* world, D3DXVECTOR3 bulletPos, short bulletNum);

	void characterInputOutput(D3DXVECTOR3 lookAt);

	void gunShot();

	void changeGunType(gunType type);

	bool collisionCheck(hkpRigidBody* rigidBody);

	void getBulletPos(hkpWorld* world, float deltaTime);
};