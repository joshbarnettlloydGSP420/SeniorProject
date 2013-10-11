#include "Level_Tutorial.h"


Level_Tutorial::Level_Tutorial(void)
{
}


Level_Tutorial::~Level_Tutorial(void)
{
}

void Level_Tutorial::Init( IDirect3DDevice9* m_pD3DDevice, RenderObject* m_pRender)
{
	InitRooms();
}

void Level_Tutorial::Update( float dt, Object_Player* player, gunType bulletColor)
{

}

void Level_Tutorial::Render(HWND hwnd, D3DXMATRIX veiwMat, D3DXMATRIX projMat)
{

}

void Level_Tutorial::InitRooms()
{
	hkpRigidBody* rigidBody;
	hkpRigidBodyCinfo bodyInfo;

	Foyer.enemiesDead = true;
	Foyer.puzzleSolved = false;
	Foyer.playerInRoom = false;

	// Box Parameters
	hkVector4 halfExtents(hkVector4(Foyer.roomSize.x, Foyer.roomSize.y, Foyer.roomSize.z, 0.0f));

	// Create Box Based on Parameters
	hkpBoxShape* boxShape = new hkpBoxShape(halfExtents);

	// Set The Object's Properties
	bodyInfo.m_shape = boxShape;
	bodyInfo.m_position.set(Foyer.roomPos.x, Foyer.roomPos.y, Foyer.roomPos.z);
	bodyInfo.m_motionType = hkpMotion::MOTION_FIXED;

	// Create Rigid Body
	rigidBody = new hkpRigidBody(bodyInfo);

	rigidBody->getCollidable()->getShape()->getAabb(rigidBody->getTransform(), 0.0f, Foyer.boundingArea);
}