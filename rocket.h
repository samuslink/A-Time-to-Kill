#ifndef _ROCKET_H
#define _ROCKET_H

#include <windows.h>
#include"explosion.h"
#include"terrain.h"
#include"player.h"
#include"camera.h"
#include"object.h"
#include"vector.h"

class CRocket : public CEntity
{
private:
	void SetupExplosionTexture();

protected:
	void OnAnimate(scalar_t deltaTime);
	void OnCollision(CObject *collisionObject);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	float pitch;
	float distanceTravel;
	CVector forward;
	bool isExplosion;

	CTexture *explosionTex;
	CExplosion *explosion;

	CRocket();
	~CRocket();

	void Load();
	void Unload();

};

#endif