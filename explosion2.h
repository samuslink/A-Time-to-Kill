/****************************************************************************
 Snowstorm.h  Particle system representing a snowstorm
 
 Author   :   Dave Astle
 Date     :   3/17/2001

 Written for OpenGL Game Programming
*****************************************************************************/
#ifndef __EXPLOSION2_H_INCLUDED__
#define __EXPLOSION2_H_INCLUDED__


/********************************* Includes *********************************/
#include "particlesystem.h"


/*************************** Constants and Macros ***************************/
const CVector PARTICLE_VELOCITY2  (2.0f, 4.0f, 2.0f);
const CVector VELOCITY_VARIATION2  (9.0f, 9.0f, 9.0f);
const CVector PARTICLE_ACCELERATION2  (0.0f, -10.0f, 0.0f);
const float     PARTICLE_SIZE2      = 1.0f;
const float     SIZE_VARIATION2     = 5.0f;

#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)

/***************************** Data structures ******************************/
class CExplosion2 : public CParticleSystem
{
public:
  CExplosion2(int maxParticles, CVector origin, float spread, GLuint texture);

  void  Update(float elapsedTime);
  void  Render();

  bool  IsDead() { return m_numParticles == 0; }

protected:
  void    InitializeParticle(int index);
  float   m_spread;

  GLuint  m_texture;     // explosion texture
};



#endif // __EXPLOSION2_H_INCLUDED__