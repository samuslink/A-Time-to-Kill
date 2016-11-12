#ifndef _GUN_H_
#define _GUN_H_

#include"entity.h"
#include"md2.h"
#include "object.h"
#include"camera.h"
#include "vector.h"
#include "Timer.h"

class CGun : public CEntity 
{
private:
	CVector lookAtVel;
	CVector lookAtAccel;
	CVector initPosition, finalPosition;
	CVector initLookAt, finalLookAt;
	void UpdateLookAt();
	void UpdateMoveTo();
protected:
	void OnDraw(CCamera *camera);
public:
	float pitch;
	float direction;
	float yaw;
	CVector forward;
	CVector lookAt;
	CVector up;
	CVector right;
	CVector velocity;
	CVector acceleration;
	CVector position;
	CTexture texture[1];
	int centerX, centerY;
	GLUquadricObj *quadratic;

	CGun()
	{
		Load();
		pitch = 0.0;
		yaw = 0.0;
		position = CVector(0.0, 0.0, 0.0);
		lookAt = CVector(0.0, 0.0, 1.0);
		forward = lookAt;
		up = CVector(0.0, 1.0, 0.0);
		right = CVector(1.0, 0.0, 0.0);
		velocity = CVector(0.0, 0.0, 0.0);
		acceleration = CVector(0.0, 0.0, 0.0);
	}
	CGun(float x, float z){position.x = x; position.z = z; Load();}
	~CGun(){};
    CGun(CVector *look);
	CGun(CVector *pos, CVector *look);
	void LookAtNow(CObject *object); 
    void LookAt(CObject *object);
	void MoveTo(CObject *object); 
	void MoveToNow(CObject *object); 
	void MoveToNow(scalar_t x, scalar_t y, scalar_t z);
    void RotateYaw(scalar_t radians); // rotation along y axis (yaw)
	void RotatePitch(scalar_t radians); // rotation along x axis (pitch)
	void RotateRoll(scalar_t radians); // rotation along z axis (roll)
	void Load();  
	void OnAnimate(scalar_t deltaTime);
	void Animate(float yaw, float pitch);
};
#endif