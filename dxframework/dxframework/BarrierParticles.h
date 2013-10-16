#include <crtdbg.h>
#include "DirectXFramework.h"
#include "InputManager.h"
#include <list>
#include <ctime>
#include <vector>
#include "CameraObj.h"


class Barrier : public PSystem
{
public:
	Barrier(const LPCWSTR fxName, 
		const std::string& techName, 
		const LPCWSTR texName, 
		const D3DXVECTOR3& accel, 
		const AABB& box,
		int maxNumParticles,
		float timePerParticle)
		: PSystem(fxName, techName, texName, accel, box, 
		maxNumParticles, timePerParticle)
	{}

	void initParticle(Particle& out, D3DXVECTOR3 pos, D3DXVECTOR3 iPos, D3DXVECTOR3 look)
	{

		out.initialPos = D3DXVECTOR3(getPosition().x, getPosition().y, getPosition().z);

		// Time particle is created relative to the global running
		// time of the particle system.
		out.initialTime = mTime;

		// Flare lives for 2-4 seconds.
		out.lifeTime   = GetRandomFloat(0.1f, 2.0f);

		// Initial size in pixels.
		out.initialSize  = GetRandomFloat( .1f, 1.0f);

		// Give a very small initial velocity to give the flares
		// some randomness.
		GetRandomVec(out.initialVelocity);

		// Scalar value used in vertex shader as an amplitude factor.
		out.mass = GetRandomFloat(1.0f, 2.0f);

		// Start color at 50-100% intensity when born for variation.
		out.initialColor = GetRandomFloat(0.5f, 1.0f)*WHITE;

		// Generate random particle on the ring in polar coordinates:
		// random radius and random angle.
		float r = GetRandomFloat(10.0f, 14.0f);
		float t = GetRandomFloat(0, 2.0f*D3DX_PI);

		// Convert to Cartesian coordinates.
		out.initialPos.x = r*cosf(t) / 3.5;
		out.initialPos.y = r*sinf(t) / 3.5;

		// Random depth value in [-1, 1] (depth of the ring)
		out.initialPos.z = GetRandomFloat(-1.0f, 1.0f);

	}

};
