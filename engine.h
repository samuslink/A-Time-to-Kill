#ifndef __ENGINE_H 
#define __ENGINE_H 
 
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN 
 
#include "world.h" 
#include "oglwindow.h" 
#include "camera.h" 
#include "Timer.h" 
#include "gun.h"
 
#include <windows.h> 
#include <dinput.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
#include<dinput.h>
 
class CEngine : public COGLWindow 
{ 
private: 
 
protected: 
	CHiResTimer *timer;							// 高分辨率计时器 
 
	virtual void GameCycle(float deltaTime); 
	virtual void OnPrepare() {}					// 设置OpenGL 
	virtual CCamera *OnGetCamera() { return NULL; }	 
	virtual CGun *OnGetGun(){return NULL;}
	virtual CWorld *OnGetWorld() { return NULL; } 
	virtual void CheckInput(float deltaTime); 
public: 
	CEngine() {} 
	CEngine(const char *szName, bool fscreen, int w, int h, int b) :  
			COGLWindow(szName, fscreen, w, h, b) {} 
	~CEngine() {} 
	LRESULT EnterMessageLoop(); 
	DIMOUSESTATE m_state;
}; 
 
#endif

