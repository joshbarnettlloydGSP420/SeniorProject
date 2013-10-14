
#include <crtdbg.h>
#include "DirectXFramework.h"
#include "InputManager.h"
#include <list>
#include <ctime>
#include <vector>
#include "CameraObj.h"


class FireRing : public PSystem
{
public:
	FireRing(const LPCWSTR fxName, 
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
		//// Time particle is created relative to the global running
		//// time of the particle system.
		//out.initialTime = mTime;

		//// Flare lives for 2-4 seconds.
		//out.lifeTime   = GetRandomFloat(2.0f, 4.0f);

		//// Initial size in pixels.
		//out.initialSize  = GetRandomFloat(10.0f, 15.0f);



		//// Give a very small initial velocity to give the flares
		//// some randomness.
		//GetRandomVec(out.initialVelocity);

		//// Scalar value used in vertex shader as an amplitude factor.
		//out.mass = GetRandomFloat(0.5f, 1.0f);

		//// Start color at 50-100% intensity when born for variation.
		//out.initialColor = GetRandomFloat(0.5f, 1.0f)*WHITE;

		//// Generate random particle on the ring in polar coordinates:
		//// random radius and random angle.
		//float r = GetRandomFloat(10.0f, 14.0f);
		//float t = GetRandomFloat(0, 2.0f*D3DX_PI);

		//// Convert to Cartesian coordinates.
		//out.initialPos.x = r*cosf(t);
		//out.initialPos.y = r*sinf(t);

		//// Random depth value in [-1, 1] (depth of the ring)
		//out.initialPos.z = GetRandomFloat(-1.0f, 1.0f);
		// Generate about the origin.
		out.initialPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
 
		out.initialTime     = mTime;
		out.lifeTime        = GetRandomFloat(1.0f, 5.0f);
		out.initialColor    = WHITE;
		out.initialSize     = GetRandomFloat(1.0f, 12.0f);
		out.mass            = GetRandomFloat(0.8f, 1.2f);

		out.initialVelocity.x = GetRandomFloat(-0.5f, 0.5f);
		out.initialVelocity.y = GetRandomFloat(1.0f, 2.0f);
		out.initialVelocity.z = GetRandomFloat(-0.5f, 0.5f);

	}
};
