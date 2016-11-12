#ifndef __ROCKET2_H
#define __ROCKET2_H

/*
	
	FILENAME
	What is in this file?
	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: XX/XX/XXXX
	Description:

*/

#include <windows.h>
#include "explosion2.h"
#include "terrain.h"
#include "player.h"
#include "camera.h"
#include "object.h"
#include "vector.h"
//#include "sod.h"
//#include "ogro.h"

class CRocket2 : public CEntity
{
private:
	void SetupExplosionTexture();

protected:
	void OnAnimate(scalar_t deltaTime);
	void OnCollision(CObject *collisionObject);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	// direction rocket points
	float pitch;
	float distanceTravel;	// distance rocket has travelled
	CVector forward;		// forward vector of rocket (for pitch/dir)
	bool isExplosion;

	CTexture *explosionTex;
	CExplosion2 *explosion;

	CRocket2();
	~CRocket2();

	void Load();
	void Unload();

};

#endif

