#ifndef __FONT_H 
#define __FONT_H 
 
#include <windows.h> 
#include <gl/gl.h> 
#include <gl/glu.h> 
 
class CFont 
{ 
private: 
	unsigned int texID;		// ���������id 
	unsigned int callList;	// ������ʾ�б� 
	float r, g, b, a;		// RGBAֵ 
	int screenX, screenY;	// ��Ļ���� 
	float xpos, ypos, zpos;	// ��ά���� 
	void LoadTexture();		// װ��TGA�������� 
	void CreateCallLists();	// ����������ʾ�б� 
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

