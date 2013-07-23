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

	// Physics
	float						velocity;

	// Mesh
	Mesh*						objectMesh;
	
	// Havok

	// Rigid Body
	short						shape;
	hkpRigidBodyCinfo			bodyInfo;
	hkReal						mass;	
	hkVector4					shapeSize;
	hkpCharacterInput			input;

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

	void createHavokObject(hkpWorld* world);
};

