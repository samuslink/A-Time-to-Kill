#ifndef __MD2_H 
#define __MD2_H 
 
#include <windows.h>			// standard Windows app include 
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <gl/gl.h>				// standard OpenGL include 
#include <gl/glu.h>				// OpenGL utilties 
 
#include "object.h" 
#include "texture.h" 
#include "vector.h" 
 
#define MAX_FRAMES 512 
 
// ģ�Ͷ���״̬ 
enum modelState_t 
{ 
	MODEL_IDLE,			// �����ж����� 
	MODEL_CROUCH,		// ���Ͷ׶����� 
	MODEL_RUN,			// ���ܲ������� 
	MODEL_JUMP,			// ����Ծ������ 
	MODEL_FIRE,			// ����������� 
	MODEL_DIE
}; 
// �������� 
typedef struct 
{ 
   float point[3]; 
} vector_t; 
 
vector_t operator-(vector_t a, vector_t b); 
vector_t operator*(float f, vector_t b); 
vector_t operator/(vector_t a, vector_t b); 
vector_t operator+(vector_t a, vector_t b); 
 
void CalculateNormal( float *p1, float *p2, float *p3 ); 
// �������� 
typedef struct 
{ 
   float s; 
   float t; 
} texCoord_t; 
// ������������ 
typedef struct 
{ 
   short s; 
   short t; 
} stIndex_t; 
// ĳһ֡λ�õ���Ϣ 
typedef struct 
{ 
   unsigned char v[3]; 
   unsigned char normalIndex; 
} framePoint_t; 
// ĳһ��֡��Ϣ 
typedef struct 
{ 
   float scale[3]; 
   float translate[3]; 
   char name[16]; 
   framePoint_t fp[1]; 
} frame_t; 
// ĳһ�������������� 
typedef struct 
{ 
   unsigned short meshIndex[3];		// �������� 
   unsigned short stIndex[3];		// ������������ 
} mesh_t; 
 
typedef struct 
{ 
   int ident;		 // MD2�ļ��ı�ʶ "IDP2" 
   int version;		 // �汾�� 
   int skinwidth;    // ����Ŀ�� 
   int skinheight;   // ����ĸ߶� 
   int framesize;    // ÿһ֡�Ĵ�С���ֽ����� 
   int numSkins;     // ������Ŀ 
   int numXYZ;       // �����Ŀ 
   int numST;        // ����������Ŀ 
   int numTris;      // ��������Ŀ 
   int numGLcmds; 
   int numFrames;    // ֡������Ŀ 
   int offsetSkins;  // ��������ƫ����(64�ֽ�) 
   int offsetST;     // �����s-tֵƫ�� 
   int offsetTris;   // ����������ƫ�� 
   int offsetFrames; // ֡����ƫ�� 
   int offsetGLcmds; // ʹ�õ�OpenGL�������� 
   int offsetEnd;    // �ļ���β 
} modelHeader_t; 
 
 
class CMD2Model : public CObject 
{ 
private: 
 
     int numFrames;		      // ֡����Ŀ 
     int numVertices;         // �������Ŀ 
     int numTriangles;        // ��������Ŀ 
     int numST;               // ������Ŀ 
     int frameSize;           // ÿһ֡�Ĵ�С 
     mesh_t *triIndex;        // ���������� 
     texCoord_t *st;          // ������������ 
     vector_t *vertexList;    // �������� 
     CTexture *modelTex;      // �������� 
 
     void SetupSkin(CTexture *thisTexture); 
 
protected: 
	modelState_t modelState;	// ��ǰ��ģ�Ͷ���״̬ 
     int currentFrame;        // �����еĵ�ǰ֡ 
     int nextFrame;           // �����е���һ֡ 
 
public: 
     float interpol;          // ��ǰ֡�Ĳ�ֵ�ٷ��� 
 
     CMD2Model();        // ���캯�� 
     ~CMD2Model();       // �������� 
     // ͬʱװ��ģ�ͺ����� 
     int Load(char *modelFile, char *skinFile); 
     // װ��ģ�� 
     int LoadModel(char *modelFile); 
     // װ��ģ�͵����� 
     int LoadSkin(char *skinFile); 
     // ����ģ�͵����� 
     int SetTexture(CTexture *texture); 
     // �Բ�ֵ����Ⱦģ�ͣ���ȡ����Ч�� 
     int AnimateModel(int startFrame, int endFrame, float percent); 
     // ��Ⱦһ��֡ 
     int RenderFrame(int keyFrame); 
     // �ͷ�ģ��ռ�õ��ڴ���Դ 
     void Unload(); 
	// ����ģ�͵Ķ���״̬ 
	void SetState(modelState_t state);	 
	// ��ȡģ�͵Ķ���״̬ 
	modelState_t GetState(); 
}; 
 
#endif

