#pragma once

#include "Mesh.h"
#include "HavokCore.h"

// Enum for deciding what Shape the Object is in Havok
enum HavokPlayerShape
{
	PLAYERNONE			=	0,		// Hav
	PLAYERSPHERE		=	1,		// Havok Sphere
	PLAYERBOX			=	2,		// Havok Box
	PLAYERCAPSULE		=	3		// Havok Capsule
};

class Object_Player
{
private:
	void createSphereObject(hkpWorld* world);
	void createBoxObject(hkpWorld* world);
	void createCapsuleObject(hkpWorld* world);
	void stateMachineInit();

public:

	//////////////////////////////////////////////////////////////////////////
	// Base																	//
	//////////////////////////////////////////////////////////////////////////
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
	
	//////////////////////////////////////////////////////////////////////////
	// Havok																//
	//////////////////////////////////////////////////////////////////////////
	// Rigid Body
	short						shape;
	hkpCharacterRigidBody*		objectBody;
	hkpCharacterRigidBodyCinfo	bodyInfo;
	hkReal						mass;	
	hkVector4					shapeSize;
	hkpCharacterInput			input;

	// State Machine
	hkpCharacterState*			state;
	hkpCharacterStateManager*	manager;
	hkpCharacterContext*		context;

	// 

	//////////////////////////////////////////////////////////////////////////
	// Constructor, Destructor, and Methods									//
	//////////////////////////////////////////////////////////////////////////
	Object_Player(void);
	~Object_Player(void);

	void Update(float deltaTime);

	void convertPosition();

	hkVector4 velocityCalc(float dt);

	void createHavokObject(hkpWorld* world);

	void characterInputOutput();

	void gunShot();

	bool collisionCheck(hkpRigidBody* rigidBody);
};

