#ifndef __WORLD_H
#define __WORLD_H


/*
	WORLD.H

  	The CWorld class

	Author: Kevin Hawkins
	Date: 3/29/2001
	Description: The CWorld class represents the game world
			   of the engine. All objects, the terrain,
			   audio system, ambient world music and sound,
			   and the camera are held here.


*/

#include <typeinfo.h>			// for RTTI
#include <windows.h>
#include "gui.h"
#include "player.h"
#include "sod.h"
#include "ogro.h"
#include "entity.h"
#include "md2.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "tree.h"
#include "gun.h"

#define MAX_ENEMIES 30

class CWorld
{
private:
	int numOgros, numSods;
	int screenWidth, screenHeight;

protected:
	void OnAnimate(float deltaTime);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	HWND hwnd;

	CTerrain *terrain;			// the terrain
	CCamera *camera;			// the camera
	CPlayer *player;			// the player
	CGun *gun;                  //the gun for the player
	CGUI *gui;

	bool gameDone;

	COgroEnemy *ogroEnemy;		// ogro enemies
	CSodEnemy *sodEnemy;		// sod enemies
	CTexture texture;
	float timeStart;
	float timeElapsed;

	CWorld();
	CWorld(CCamera *c);
	~CWorld();

	// initialize terrain, load objects and put in container
	void LoadWorld();
	void UnloadWorld();

	int CountObjectTypes(const type_info &classID);

	// do physics calculations for all objects in the world
	// including collisions
	void Animate(float deltaTime);

	// render all objects in the world
	void Draw(CCamera *camera);
	void Prepare() { OnPrepare(); }

	void FadeScreen();
	void SetScreen(int width, int height);

	bool IsGameDone() { return 0;}//gameDone; }  //HOW COULD THIS SCREW IT UP?!?
	void QuitGame() { gameDone = true; }
	int GetOgros() { return numOgros; }
	int GetSods() { return numSods; }
};


#endif

