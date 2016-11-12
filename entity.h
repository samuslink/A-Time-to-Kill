#ifndef __ENTITY_H 
#define __ENTITY_H 
 
#include <stdlib.h> 
#include <time.h> 
#include <typeinfo.h> 
 
#include "md2.h" 
#include "object.h" 
#include "camera.h" 
//#include "audiosystem.h" 
#include "terrain.h" 
 
class CEntity : public CMD2Model 
{ 
protected: 
     void OnAnimate(float deltaTime); 
     void OnDraw(CCamera *camera); 
     void OnCollision(CObject *collisionObject); 
     void OnPrepare(); 
 
public: 
     float direction;         // 实体面对的角度 
     //CAudio *entitySound;     // 实体发出的声音，目前每个实体只支持一个声音 
   
     CEntity(); 
     ~CEntity(); 
 
     int stateStart, stateEnd;     // 对应状态的关键帧开始/结束 
     float deltaT; 
     float animSpeed; 
 
//     void LoadAudio(CAudioSystem *audioSystem, char *filename, bool is3DSound); 
}; 
 
#endif
