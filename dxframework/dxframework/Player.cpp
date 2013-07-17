#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::Init( HavokCore* havok )
{
	objectBase = new Object_Base();
	objectBase->Init();
	objectBase->setPosition(D3DXVECTOR4(0.0f, 15.0f, 0.0f, 0.0f));
	objectBase->setShape( CAPSULE );

	objectBase->createHavokObject( havok->getWorld() );
}

void Player::Update( float dt)
{
	objectBase->Update(dt);
}

void Player::Render()
{

}