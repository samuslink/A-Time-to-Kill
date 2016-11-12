#ifndef _PLAYER_H
#define _PLAYER_H

#include <typeinfo.h>
#include<windows.h>

#include "gun.h"
#include "sod.h"
#include "ogro.h"
#include "rocket.h"
#include "rocket2.h"
#include "camera.h"
#include "object.h"
#include "terrain.h"

class CPlayer : public CObject
{
private:
	CCamera *camera;
	CTerrain *terrain;
	CGun *gun;

protected:
	void OnCollision(CObject *collisionObject)
	{
		if(typeid(*collisionObject) == typeid(CTerrain))
		{
			position.y = ((CTerrain*)collisionObject)->GetHeight(position.x,position.z) + size;
		}
		else if(typeid(*collisionObject)==typeid(COgroEnemy))
		{
			if(camera)
			{
				if(camera->velocity.z>0.0)
					camera->velocity = CVector(0.0,0.0,0.0);
			}
		}
		else if(typeid(*collisionObject)== typeid(CPlayer))
		{
		}
	}
	void OnPrepare()
	{
		if(camera)
		{
			position = camera->position;
			direction = camera->yaw;
			pitch = camera->pitch;
		}
		if(gun)
		{
			gun->position.x = camera->position.x - 0.4f;
			gun->position.y = camera->position.y;
			gun->position.z = camera->position.z;
			//gun->pitch = camera->pitch;
			//gun->yaw = camera->yaw;
			//gun->direction = direction;
			//gun->forward = camera->lookAt.UnitVector();

		}
	}
public:
	float direction;
	float pitch;

	CPlayer(){size = 7.0f;camera=NULL;terrain=NULL;}
	~CPlayer(){}


	void SetCamera(CCamera *c){camera=c;}
	void SetGun(CGun *g){gun = g;}
	void DetachCamera(){camera = NULL;}
	void SetTerrain(CTerrain *t){terrain=t;}

	void FireWeapon();
	void FireAuxWeapon();
};

#endif
