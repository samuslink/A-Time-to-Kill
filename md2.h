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
 
// 模型动画状态 
enum modelState_t 
{ 
	MODEL_IDLE,			// “空闲动画” 
	MODEL_CROUCH,		// “低蹲动画” 
	MODEL_RUN,			// “跑步动画” 
	MODEL_JUMP,			// “跳跃动画” 
	MODEL_FIRE,			// “射击动画” 
	MODEL_DIE
}; 
// 单个顶点 
typedef struct 
{ 
   float point[3]; 
} vector_t; 
 
vector_t operator-(vector_t a, vector_t b); 
vector_t operator*(float f, vector_t b); 
vector_t operator/(vector_t a, vector_t b); 
vector_t operator+(vector_t a, vector_t b); 
 
void CalculateNormal( float *p1, float *p2, float *p3 ); 
// 纹理坐标 
typedef struct 
{ 
   float s; 
   float t; 
} texCoord_t; 
// 纹理坐标索引 
typedef struct 
{ 
   short s; 
   short t; 
} stIndex_t; 
// 某一帧位置的信息 
typedef struct 
{ 
   unsigned char v[3]; 
   unsigned char normalIndex; 
} framePoint_t; 
// 某一单帧信息 
typedef struct 
{ 
   float scale[3]; 
   float translate[3]; 
   char name[16]; 
   framePoint_t fp[1]; 
} frame_t; 
// 某一单个三角形数据 
typedef struct 
{ 
   unsigned short meshIndex[3];		// 顶点索引 
   unsigned short stIndex[3];		// 纹理坐标索引 
} mesh_t; 
 
typedef struct 
{ 
   int ident;		 // MD2文件的标识 "IDP2" 
   int version;		 // 版本号 
   int skinwidth;    // 纹理的宽度 
   int skinheight;   // 纹理的高度 
   int framesize;    // 每一帧的大小（字节数） 
   int numSkins;     // 纹理数目 
   int numXYZ;       // 点的数目 
   int numST;        // 纹理坐标数目 
   int numTris;      // 三角形数目 
   int numGLcmds; 
   int numFrames;    // 帧的总数目 
   int offsetSkins;  // 纹理名称偏移量(64字节) 
   int offsetST;     // 纹理的s-t值偏移 
   int offsetTris;   // 三角形网格偏移 
   int offsetFrames; // 帧数据偏移 
   int offsetGLcmds; // 使用的OpenGL命令类型 
   int offsetEnd;    // 文件结尾 
} modelHeader_t; 
 
 
class CMD2Model : public CObject 
{ 
private: 
 
     int numFrames;		      // 帧的数目 
     int numVertices;         // 顶点的数目 
     int numTriangles;        // 三角形数目 
     int numST;               // 纹理数目 
     int frameSize;           // 每一帧的大小 
     mesh_t *triIndex;        // 三角形链表 
     texCoord_t *st;          // 纹理坐标链表 
     vector_t *vertexList;    // 顶点链表 
     CTexture *modelTex;      // 纹理数据 
 
     void SetupSkin(CTexture *thisTexture); 
 
protected: 
	modelState_t modelState;	// 当前的模型动画状态 
     int currentFrame;        // 动画中的当前帧 
     int nextFrame;           // 动画中的下一帧 
 
public: 
     float interpol;          // 当前帧的插值百分数 
 
     CMD2Model();        // 构造函数 
     ~CMD2Model();       // 析构函数 
     // 同时装入模型和纹理 
     int Load(char *modelFile, char *skinFile); 
     // 装入模型 
     int LoadModel(char *modelFile); 
     // 装入模型的纹理 
     int LoadSkin(char *skinFile); 
     // 设置模型的纹理 
     int SetTexture(CTexture *texture); 
     // 以插值法渲染模型，获取动画效果 
     int AnimateModel(int startFrame, int endFrame, float percent); 
     // 渲染一单帧 
     int RenderFrame(int keyFrame); 
     // 释放模型占用的内存资源 
     void Unload(); 
	// 设置模型的动画状态 
	void SetState(modelState_t state);	 
	// 获取模型的动画状态 
	modelState_t GetState(); 
}; 
 
#endif

