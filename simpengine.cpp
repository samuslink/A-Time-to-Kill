#define WIN32_LEAN_AND_MEAN    
#define WIN32_EXTRA_LEAN    
   
#include "simpengine.h"    

scalar_t pastposition;
scalar_t futureposition;
float timerelapsed;
int count = 0;
void CSimpEngine::OnPrepare()   
{   
    glEnable(GL_DEPTH_TEST);   
    glEnable(GL_SMOOTH);   
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
    glLoadIdentity();
}   
   
void CSimpEngine::OnMouseDownL(float x, float y)    
{
	if(!gameWorld->IsGameDone())
	{
		gameWorld->player->FireWeapon();
	}
}   

void CSimpEngine::OnMouseDownR(float x, float y)
{
	if(!gameWorld->IsGameDone())
	{
		gameWorld->player->FireAuxWeapon();
	}
}
void CSimpEngine::OnKeyDown(int nVirtKey)   
{   
    switch (nVirtKey)   
    {   
    case VK_UP:   
        gameCamera->velocity += CVector(0,0,2.0);
		gameGun->velocity += CVector(0,0,2.0);
        break;   
    case VK_DOWN:   
        gameCamera->velocity += CVector(0,0,-2.0); 
		gameGun->velocity += CVector(0,0,-2.0); 
        break;   
    case VK_RIGHT:   
        gameCamera->velocity += CVector(1.0, 0.0, 0.0);   
		gameGun->velocity += CVector(1.0, 0.0, 0.0);
        break;   
    case VK_LEFT:   
        gameCamera->velocity += CVector(-1.0, 0.0, 0.0); 
		gameGun->velocity += CVector(-1.0,0.0,0.0);
        break;  
	case VK_SPACE:
		pastposition = gameCamera->position.y;
		timerelapsed = timer->GetElapsedSeconds(1);
		futureposition = gameCamera->velocity.y + (9.8 * timerelapsed);
		while(gameCamera->position.y > futureposition)
		{
			if((count == 0) || (count % 100 == 0))
			{
			gameCamera->position.y += gameCamera->velocity.y;
			gameCamera->velocity.y += -1;
			gameGun->position.y += gameCamera->velocity.y;
			gameGun->velocity.y += -1;
			}
			count++;
		}
		count = 0;
		while(gameCamera->position.y < pastposition)
		{
			if((count == 0) || (count % 100 == 0))
			{
			gameCamera->position.y += gameCamera->velocity.y;
			gameCamera->velocity.y += 1;
			gameGun->position.y += gameCamera->velocity.y;
			gameGun->velocity.y += 1;
			}
			count++;
		}
		count = 0;
		break;
    case VK_ESCAPE:   
        SendMessage(hWnd,WM_CLOSE,0,0);   
        break;   
    case VK_ADD:   
        mouseSensitivity += 0.05f;   
        break;   
    case VK_SUBTRACT:   
        mouseSensitivity -= 0.05f;   
        if (mouseSensitivity < 0.05)   
            mouseSensitivity = 0.05;   
        break;   
    default:   
        break;   
    }   
}   
   
void CSimpEngine::OnMouseMove(int deltaX, int deltaY)   
{
    gameCamera->yaw += deltaX*mouseSensitivity;   
    gameCamera->pitch -= deltaY*mouseSensitivity;
	gameWorld->gun->Animate(gameCamera->yaw, gameCamera->pitch);
}   
   
void CSimpEngine::OnMouseMove(int x, int y, int centerX, int centerY)   
{   
    static float oldX;   
    static float oldY;   
    static float yaw = 0.0f;   
    static float pitch = 0.0f;   
    float mX, mY;   
    mX = (float)x;   
    mY = (float)y;   
    if (mX < centerX/2)   
	{
        gameCamera->yaw -= 0.25f*mouseSensitivity; 
		gameGun->yaw -= 0.25f*mouseSensitivity;
	}
    if (mX > centerX/2)
	{
        gameCamera->yaw += 0.25f*mouseSensitivity;
		gameGun->yaw += 0.25f*mouseSensitivity;
	}
    if (mY < centerY/2)   
	{
        gameCamera->pitch += 0.25f*mouseSensitivity; 
		gameGun->pitch += 0.25f*mouseSensitivity;
	}
    if (mY > centerY/2)   
	{
        gameCamera->pitch -= 0.25f*mouseSensitivity;
		gameGun->pitch -= 0.25f*mouseSensitivity;
	}
    oldX = mX;   
    oldY = mY;   
}  
