
#ifndef __SIMPENGINE 
#define __SIMPENGINE 
 
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN 
 
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 

#include "player.h"
#include "engine.h" 
#include "object.h" 
#include "camera.h" 
#include "terrain.h" 
#include "world.h" 
#include "gun.h"
 
class CSimpEngine : public CEngine 
{ 
private: 
	CCamera *gameCamera; 
	CWorld *gameWorld; 
	CGun *gameGun;
protected: 
	CCamera *OnGetCamera() { return gameCamera; } 
	CGun *OnGetGun(){return gameGun;}
	CWorld *OnGetWorld() { return gameWorld; } 
	void OnPrepare(); 
	void OnMouseDownL(float x, float y); 
	void OnMouseDownR(float x, float y);
	void OnMouseMove(int deltaX, int deltaY); 
	void OnMouseMove(int x, int y, int centerX, int centerY); 
	void OnKeyDown(int nVirtKey); 
public: 
	CSimpEngine()  
	{ 
		gameCamera = new CCamera; 
		gameWorld = new CWorld; 
		gameGun = new CGun;
	} 
	CSimpEngine(const char *szName, bool fscreen, int w, int h, int b) : 
		CEngine(szName, fscreen, w, h, b)  
	{ 
		gameCamera = new CCamera; 
		gameGun = new CGun;
		gameWorld = new CWorld(gameCamera); 
		gameCamera->centerX = centerX; 
		gameCamera->centerY = centerY; 
		gameGun->centerX = centerX;
		gameGun->centerY = centerY;
	} 
	~CSimpEngine()  
	{ 
		delete gameWorld; 
		delete gameCamera;
		gameWorld = NULL; 
		gameCamera = NULL; 
	} 
}; 
 
 
#endif