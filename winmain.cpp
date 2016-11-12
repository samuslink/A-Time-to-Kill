#define WIN32_MEAN_AND_LEAN    
#define WIN32_EXTRA_LEAN    
   
#include <windows.h>    

#include "oglwindow.h"      // OpenGL窗口类    
#include "vector.h"    
#include "engine.h"         // 引擎类    
#include "simpengine.h"    
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib, "dsound.lib")
//#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
HINSTANCE hInstmain;
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)   
{
	hInstmain = hInst;
    int loopRet;   
    CoInitialize(NULL);   
    if (!COGLWindow::RegisterWindow(hInst))   
    {   
        MessageBox(NULL, "Failed to register window class", "Error", MB_OK);   
        return -1;   
    }   
    CSimpEngine *engine = NULL;   
    try   
    {      
        engine = new CSimpEngine("OpenGL Game", FALSE, 800, 600, 16);   
        loopRet = engine->EnterMessageLoop();   
        delete engine;   
        return loopRet;   
    }   
    catch(char *sz)   
    {      
        MessageBox(NULL, sz, 0, 0);   
        delete engine;   
    }   
    CoUninitialize();   
    return -1;   
}  
