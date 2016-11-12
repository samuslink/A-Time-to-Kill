#ifndef __CAMERA_H 
#define __CAMERA_H 
 
#define WIN32_LEAN_AND_MEAN 
#define WIN32_EXTRA_LEAN 
 
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
 
#include "vector.h" 

class CObject;

class CCamera
{ 
private: 
	CVector initPosition, finalPosition;	// 初始位置和最后位置矢量 
	CVector initLookAt, finalLookAt;	 
	CVector lookAtVel;			 
	CVector lookAtAccel; 
	void UpdateLookAt(); 
	void UpdateMoveTo();

public: 
	CVector position;			// 摄像机位置 
	CVector velocity;			// 摄像机速度 
	CVector acceleration;		// 摄像机加速度 
	CVector lookAt;				// lookat矢量 
	CVector look;
	// 向上、向前和向右矢量 
	CVector up; 
	CVector forward; 
	CVector right; 
	// 偏航和倾斜角度 
	float yaw; 
	float pitch; 
	int screenWidth, screenHeight; 
	int centerX, centerY; 
 
	CCamera(); 
	CCamera(int width, int height) {} 
	CCamera(CVector *look); 
	CCamera(CVector *pos, CVector *look); 
	~CCamera(); 
 
	void LookAt(CObject *object); 
	void LookAtNow(CObject *object); 
	void MoveTo(CObject *object); 
	void MoveToNow(CObject *object); 
	void MoveToNow(scalar_t x, scalar_t y, scalar_t z); 
	// 沿y轴向右旋转（偏航） 
	void RotateYaw(scalar_t radians); 
	void RotatePitch(scalar_t radians); 
	void RotateRoll(scalar_t radians); 
	// 进行物理计算 
	void Animate(scalar_t deltaTime);

}; 
 
#endif
