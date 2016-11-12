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
    // 减少时间直到下一个鼠标按键按下    
    buttonDelta -= deltaTime;   
    if (buttonDelta < 0.0f)   
        buttonDelta = 0.0f;   
    // 更新输入设备    
    //inputSystem->Update();
    // 获取最近的鼠标运动    
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
    CCamera *camera = OnGetCamera();    // 获取摄像机   
	CGun *gun = OnGetGun();
    CWorld *world = OnGetWorld();       // 获取场景    
   // if (useDInput)   
		CheckInput(deltaTime);   
    // 为每帧进行opengl设置    
    OnPrepare();   
    world->Prepare();   
    // 移动/定向摄像机    
    camera->Animate(deltaTime);
    // 移动/定向对象    
    world->Animate(deltaTime);   
    // 绘制对象    
    world->Draw(camera);   
    // 交换缓冲区    
    SwapBuffers(hDC);   
}   
   
// Windows消息循环    
LRESULT CEngine::EnterMessageLoop()   
{
	//RECT r;
    //  Message Loop   
    MSG msg;   
    timer = new CHiResTimer;   
    // 记时器初始化    
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
