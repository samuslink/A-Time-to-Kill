#ifndef _EXPLOSION_H_INCLUDED_
#define _EXPLOSION_H_INCLUDED_

#include"particlesystem.h"

const CVector PARTICLE_VELOCITY (0.0f,3.0f,0.0f);
const CVector VELOCITY_VARIATION (8.0f,8.0f,8.0f);
const CVector PARTICLE_ACCELERATION (0.0f,-5.0f,0.0f);
const float PARTICLE_SIZE = 5.0f;
const float SIZE_VARIATION = 2.0f;

#define FRAND (((float)rand()-(float)rand())/RAND_MAX)

class CExplosion : public CParticleSystem
{
public:
	CExplosion(int maxParticles, CVector origin, float  spread, GLuint texture);

	void Update(float elapsedTime);
	void Render();

	bool IsDead(){return m_numParticles==0;}

protected:
	void InitializeParticle(int index);
	float m_spread;

	GLuint m_texture;
};

#endif