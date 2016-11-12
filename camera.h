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
	CVector initPosition, finalPosition;	// ��ʼλ�ú����λ��ʸ�� 
	CVector initLookAt, finalLookAt;	 
	CVector lookAtVel;			 
	CVector lookAtAccel; 
	void UpdateLookAt(); 
	void UpdateMoveTo();

public: 
	CVector position;			// �����λ�� 
	CVector velocity;			// ������ٶ� 
	CVector acceleration;		// ��������ٶ� 
	CVector lookAt;				// lookatʸ�� 
	CVector look;
	// ���ϡ���ǰ������ʸ�� 
	CVector up; 
	CVector forward; 
	CVector right; 
	// ƫ������б�Ƕ� 
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
	// ��y��������ת��ƫ���� 
	void RotateYaw(scalar_t radians); 
	void RotatePitch(scalar_t radians); 
	void RotateRoll(scalar_t radians); 
	// ����������� 
	void Animate(scalar_t deltaTime);

}; 
 
#endif
