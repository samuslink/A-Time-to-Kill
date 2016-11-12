#ifndef __FONT_H 
#define __FONT_H 
 
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
 
class CFont 
{ 
private: 
	unsigned int texID;		// 字体的纹理id 
	unsigned int callList;	// 字体显示列表 
	float r, g, b, a;		// RGBA值 
	int screenX, screenY;	// 屏幕坐标 
	float xpos, ypos, zpos;	// 三维坐标 
	void LoadTexture();		// 装入TGA字体纹理 
	void CreateCallLists();	// 创建字体显示列表 
public: 
	CFont(); 
	CFont(char *name, int size); 
	~CFont(); 
	void Build(char *name, int size); 
	void ClearFont(); 
	void Print(const char *str, ...); 
	void SetPos2D(int x, int y) { screenX = x; screenY = y; } 
	void SetPos3D(float x, float y, float z) { xpos = x; ypos = y; zpos = z; } 
	void SetRGB(float red, float green, float blue) { r = red; g = green; b = blue; a = 1.0; } 
	void SetRGBA(float red, float green, float blue, float alpha) { r = red; g = green; b = blue; a = alpha; } 
}; 
 
#endif

