#define WIN32_LEAN_AND_MEAN    
#define WIN32_EXTRA_LEAN    
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

#include <stdlib.h>
#include "engine.h"  
#include "Timer.h"
#include "camera.h"    
#include "world.h"
#include "gun.h"

bool grounded = true;
int mousex = 0;
int mousey = 0;
int oldmousex = 0;
int oldmousey = 0;
int mouseDeltaX = 0;
int mouseDeltaY = 0;
void CEngine::CheckInput(float deltaTime)   
{ 
	INPUT *buffer = new INPUT;
    static float buttonDelta = 0.0f; 
    // ����ʱ��ֱ����һ����갴������    
    buttonDelta -= deltaTime;   
    if (buttonDelta < 0.0f)   
        buttonDelta = 0.0f;   
    // ���������豸    
    //inputSystem->Update();
    // ��ȡ���������˶�    
    //inputSystem->GetMouseMovement(mouseDeltaX, mouseDeltaY); 
	if(buffer->type == INPUT_MOUSE)
	{
		oldmousex = mousex;
		oldmousey = mousey;
		mousex = buffer->mi.dx;
		mousey = buffer->mi.dy;
		mouseDeltaX = mousex - oldmousex;
		mouseDeltaY = mousey - oldmousey;
		OnMouseMove(mouseDeltaX,mouseDeltaY);
		//SendMessage(hWnd,WM_MOUSEMOVE,0,0);
	}
		//SendMessage(hWnd,WM_MOUSEMOVE,m_state.lY,m_state.lX);
	//OnMouseMove(mouseDeltaX, mouseDeltaY); 
	//SendMessage(hWnd,WM_MOUSEMOVE,m_state.lX,m_state.lY);
	//if(inputSystem->KeyDown(DIK_W))
    if (KEY_DOWN(0x57))   
        OnKeyDown(VK_UP);   
    //if (inputSystem->KeyDown(DIK_S)) 
	if(KEY_DOWN(0x53))
        OnKeyDown(VK_DOWN);   
    //if (inputSystem->KeyDown(DIK_A))  
	if(KEY_DOWN(0x41))
        OnKeyDown(VK_LEFT);   
    //if (inputSystem->KeyDown(DIK_D)) 
	if(KEY_DOWN(0x44))
        OnKeyDown(VK_RIGHT);   
    //if (inputSystem->KeyDown(DIK_ADD))
	if(KEY_DOWN(VK_ADD))
        OnKeyDown(VK_ADD);   
    //if (inputSystem->KeyDown(DIK_SUBTRACT)) 
	if(KEY_DOWN(VK_SUBTRACT))
        OnKeyDown(VK_SUBTRACT);   
    //if (inputSystem->KeyDown(DIK_ESCAPE))
	if(KEY_DOWN(VK_ESCAPE))
        OnKeyDown(VK_ESCAPE);   
	if(KEY_DOWN(VK_SPACE)&&(grounded == true))
	{
		grounded = false;
		OnKeyDown(VK_SPACE);
		grounded = true;
	}
    //if (inputSystem->ButtonDown(0)) 
	if((GetKeyState(VK_LBUTTON)& 0x80) != 0)
    {   
        if (buttonDelta == 0.0f)   
        {   
            OnMouseDownL(0,0);   
            buttonDelta = 0.5f;   
        }   
    }   
}   
   
void CEngine::GameCycle(float deltaTime)   
{   
    CCamera *camera = OnGetCamera();    // ��ȡ�����   
	CGun *gun = OnGetGun();
    CWorld *world = OnGetWorld();       // ��ȡ����    
   // if (useDInput)   
		CheckInput(deltaTime);   
    // Ϊÿ֡����opengl����    
    OnPrepare();   
    world->Prepare();   
    // �ƶ�/���������    
    camera->Animate(deltaTime);
    // �ƶ�/�������    
    world->Animate(deltaTime);   
    // ���ƶ���    
    world->Draw(camera);   
    // ����������    
    SwapBuffers(hDC);   
}   
   
// Windows��Ϣѭ��    
LRESULT CEngine::EnterMessageLoop()   
{
	//RECT r;
    //  Message Loop   
    MSG msg;   
    timer = new CHiResTimer;   
    // ��ʱ����ʼ��    
    timer->Init();   
    for (;;)   
    {      
        GameCycle(timer->GetElapsedSeconds(1));  
		SetWindowText(hWnd,"A Time To Kill");
        while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))   
        {   
            if (!GetMessage (&msg, NULL, 0, 0))   
            {   
                delete timer;   
                return msg.wParam;   
            }   
            TranslateMessage (&msg);   
            DispatchMessage (&msg);   
        }
		//GetWindowRect(hWnd,&r);
		//ClipCursor(&r);
    }   
    delete timer;   
    return msg.wParam;   
}  
