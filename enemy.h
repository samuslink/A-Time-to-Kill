#ifndef _ENEMY_H
#define _ENEMY_H
#include"entity.h"
#include "vector.h"
#include<typeinfo.h>

class CPlayer;
class CTerrain;

enum AIState_t
{
	AI_UNCARING,
	AI_SCARED,
	AI_DEAD
};

class CEnemy : public CEntity
{
private:

protected:
	float distFromPlayer; // distance this enemy is from player
	float runSpeed; // speed of enemy when running
	AIState_t aiState; // state of enemy thought
	// we override this function to have specific enemy AI
	virtual void OnProcessAI() {}
	// handle collisions with other objects
	virtual void OnCollision(CObject *collisionObject) 
	{
		if(typeid(*collisionObject)==typeid(CEnemy))
		{
			modelState = MODEL_IDLE;
			velocity = CVector(0.0,0.0,0.0);
		}
		else if (typeid(*collisionObject)==typeid(CTerrain))
		{
			position.y = ((CTerrain*)collisionObject)->GetHeight(position.x,position.z) + size;
		}
		else
		{
		}
	}

public:
	CPlayer *player; // a reference to the player
	CEnemy() // constructor
	{
		isDead = false; // enemy starts off alive
		velocity = CVector(0.0, 0.0, 0.0); // velocity of enemy
		runSpeed = velocity.z; // speed of enemy is velocity’s ‘z’
		SetState(MODEL_IDLE); // enemy AI/model state - idle state
		direction = 0.0f; // point north
		player = NULL; // no player has been set
	}
	~CEnemy() {} // destructor
	void ProcessAI() { OnProcessAI(); } // process the enemy AI
	void SetPlayer(CPlayer *p) // set reference to player object
	{ player = p; }
};

#endif