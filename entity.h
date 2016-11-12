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
     float direction;         // ʵ����ԵĽǶ� 
     //CAudio *entitySound;     // ʵ�巢����������Ŀǰÿ��ʵ��ֻ֧��һ������ 
   
     CEntity(); 
     ~CEntity(); 
 
     int stateStart, stateEnd;     // ��Ӧ״̬�Ĺؼ�֡��ʼ/���� 
     float deltaT; 
     float animSpeed; 
 
//     void LoadAudio(CAudioSystem *audioSystem, char *filename, bool is3DSound); 
}; 
 
#endif
