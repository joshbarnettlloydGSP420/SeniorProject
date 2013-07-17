#include "Enemy_Base.h"


Enemy_Base::Enemy_Base(void)
{
}


Enemy_Base::~Enemy_Base(void)
{
}

void Enemy_Base::Init(IDirect3DDevice9* m_pD3DDevice)
{
	device = m_pD3DDevice;

	// Set the Initial position of the enemy if none is specified.
	movement = new Enemy_Movement();
	movement->setPosition( D3DXVECTOR4( 0, 0, 0, 0 ));
	movement->setVelocity( D3DXVECTOR4( 0, 0, 0, 0 ));
	 
	// Initial state of the enemy is alive.
	isDead = false;

	// Initialize the 3D model of the enemy.
	model = new Model();
	model->loadModel( device, "GirRobot.X");
}


void Enemy_Base::Update( float dt )
{
	// movement->Update();
}

void Enemy_Base::Render()
{
	//model->setPosition( D3DXVECTOR4( 0, 0, 0, 0));
	model->setPosition( movement->GetPosition());
	model->setScale( D3DXVECTOR3( 0.005, 0.005, 0.005));
	model->render( device );
}