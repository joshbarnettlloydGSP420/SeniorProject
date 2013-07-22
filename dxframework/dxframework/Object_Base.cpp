#include "Object_Base.h"


Object_Base::Object_Base(void)
{
	objectMesh = new Mesh();
	position = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	mass = 5.0f;
	shape = BOX;
}


Object_Base::~Object_Base(void)
{
}

void Object_Base::Update(float deltaTime)
{
	convertPosition(&bodyInfo.m_position, &position);

}

void Object_Base::convertPosition(hkVector4* phyPosition, D3DXVECTOR4* m_Position)
{
	D3DXVECTOR4 temp = D3DXVECTOR4(0, 0, 0, 0);

	temp.x = (float)phyPosition->getComponent(0);
	temp.y = (float)phyPosition->getComponent(1);
	temp.z = (float)phyPosition->getComponent(2);
	temp.w = (float)phyPosition->getComponent(3);

	*m_Position = temp;
}

// This is a switch that will auto create an Havok Object based on its shape
void Object_Base::createHavokObject(hkpWorld* world)
{
	// Create Object Based on Shape
	switch(shape)
	{
		case SPHERE:
			createSphereObject(world);
			break;

		case BOX:
			createBoxObject(world);
			break;

		case CAPSULE:
			createCapsuleObject(world);
			break;

		case NONE:
			break;
	}
}

void Object_Base::createSphereObject(hkpWorld* world)
{
	// Sphere Parameters
	hkReal radius = (scale.x + scale.z) / 2;

	// Create Sphere Based on Parameters
	hkpSphereShape* sphereShape = new hkpSphereShape(radius);

	// Set The Object's Properties
	bodyInfo.m_shape = sphereShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	bodyInfo.m_friction = 1.0f;
	bodyInfo.m_restitution = 0.2f;

	// Calculate Mass Properties
	hkMassProperties massProperties;

	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(sphereShape, mass, massProperties);
	
	// Set Mass Properties
	bodyInfo.setMassProperties(massProperties);

	// Create Rigid Body
	hkpRigidBody* rigidBody = new hkpRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	sphereShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(rigidBody);
}

void Object_Base::createBoxObject(hkpWorld* world)
{
	// Box Parameters
	hkVector4 halfExtents(scale.x, scale.y, scale.z);

	// Create Box Based on Parameters
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;

	// Calculate Mass Properties
	hkMassProperties massProperties;
	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(boxShape, mass, massProperties);

	// Set Mass Properties
	bodyInfo.setMassProperties(massProperties);

	// Create Rigid Body
	hkpRigidBody* rigidBody = new hkpRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	boxShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(rigidBody);
}

void Object_Base::createCapsuleObject(hkpWorld* world)
{
	// Capsule Parameters
	hkVector4	vertexA(position.x, position.y + (scale.y / 2), position.z, 0);	// Top
	hkVector4	vertexB(position.x, position.y - (scale.y / 2), position.z, 0);	// Bottom
	hkReal		radius	=	(scale.x + scale.z) / 2;							// Radius

	// Create Capsule Based on Parameters
	hkpCapsuleShape* capsuleShape = new hkpCapsuleShape(vertexA, vertexB, radius);

	// Set The Object's Properties
	bodyInfo.m_shape = capsuleShape;
	bodyInfo.m_position.set(position.x, position.y, position.z, 0.0f);
	bodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;

	// Calculate Mass Properties
	hkMassProperties massProperties;

	hkpInertiaTensorComputer::computeShapeVolumeMassProperties(capsuleShape, mass, massProperties);
	
	// Set Mass Properties
	bodyInfo.setMassProperties(massProperties);

	// Create Rigid Body
	hkpRigidBody* rigidBody = new hkpRigidBody(bodyInfo);

	// No longer need the reference on the shape, as the rigidbody owns it now
	capsuleShape->removeReference();

	// Add Rigid Body to the World
	world->addEntity(rigidBody);
}
