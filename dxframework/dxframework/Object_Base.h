#pragma once

#include "Mesh.h"
#include "HavokCore.h"

// Enum for deciding what Shape the Object is in Havok
enum HavokShape
{
	NONE		=	0,		// Hav
	SPHERE		=	1,		// Havok Sphere
	BOX			=	2,		// Havok Box
	CAPSULE		=	3		// Havok Capsule
};

float SIMULATION_STEP_TIME = 1.0f / 60.0f;

class Object_Base
{
private:
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

	// Mesh
	Mesh*						objectMesh;
	
	// Havok

	// Rigid Body
	short						shape;
	hkpCharacterRigidBody*		objectBody;
	hkReal						mass;	
	hkVector4					shapeSize;
	hkpCharacterInput			input;
	
	// Movement

	// State Machine
	hkpCharacterState*			state;
	hkpCharacterStateManager*	manager;
	hkpCharacterContext*		context;

	// 

	// Constructor, Destructor, and Methods
	Object_Base(void);
	~Object_Base(void);

	void Update(float deltaTime);

	void convertPosition();

	hkVector4 velocityCalc(float dt);

	void createHavokObject(hkpWorld* world);

	void charaterInputOutput();
};

