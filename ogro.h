#ifndef _OGRO_H
#define _OGRO_H
#include"enemy.h"
#include "sod.h"
#include<time.h>

class COgroEnemy : public CEnemy
{
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

public:
	COgroEnemy(){Load();}
	COgroEnemy(float x, float z){position.x = x; position.z = z; Load();}
	~COgroEnemy(){}

	void Load();
};

#endif