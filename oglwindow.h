#ifndef __OGLWINDOW_H__ 
#define __OGLWINDOW_H__ 
 
#include <windows.h> 
#include <gl\gl.h> 
#include <gl\glu.h> 

//#include "inputsystem.h" 
 
class COGLWindow 
{ 
protected: 
	HWND		hWnd;	// window handle 
	HDC		hDC;		// device context 
	HPALETTE	hPalette;	// palette 
	HGLRC	hGLRC;	// rendering context 
 
private: 
 
	// the WndProc 
	friend LRESULT APIENTRY WndProcOGL(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); 
 
	void SetupPixelFormat();		// setup the pixel format 
	void SetupPalette();		// setup the palette 
	// Windows message handling functions 
	bool Create();					// WM_CREATE 
	void Destroy();				// WM_DESTROY 
	void PaletteChanged(WPARAM wParam);// WM_PALETTECHANGED 
	BOOL QueryNewPalette();			// WM_QUERYNEWPALETTE 
	void Paint();					// WM_PAINT 
	void Size();					// WM_SIZE 
	void MouseMove(int x, int y);		// WM_MOUSEMOVE 
 
	int GetMouseX(LPARAM lParam);		// get true mouse coordinates 
	int GetMouseY(LPARAM lParam); 
 
	float GetNormalizedPosX(LPARAM lParam);	// get normalized mouse coordinates 
	float GetNormalizedPosY(LPARAM lParam);	// between (-1.0 and 1.0) 
 
	int iPrevWidth; 
	int iPrevHeight; 
	void BeginFullScreen(int w, int h, int b); 
	void EndFullScreen(); 
 
public: 
	int width; 
	int height; 
	int centerX; 
	int centerY; 
	int bits; 
	int aspect; 
	int mouseX; 
	int mouseY; 
	bool fullscreen; 

	float mouseSensitivity; 
 
	bool useDInput;	// true if dinput is enabled 
	//CInputSystem *inputSystem; 
 
protected: 
	virtual bool OnCreate() { return true; } 
	virtual bool OnClose() { return true; } 
	virtual void OnSize() { } 
	virtual void OnMouseDownL(float x, float y) { } 
	virtual void OnMouseDownR(float x, float y) { } 
	virtual void OnMouseUpL() { } 
	virtual void OnMouseUpR() { } 
	virtual void OnMouseMove(int x, int y, int centerX, int centerY) { } 
	virtual void OnMouseMove(int deltaX, int deltaY) { } 
	virtual void OnMouseDragL(int x, int y, int dx, int dy) { } 
	virtual void OnMouseDragR(int x, int y, int dx, int dy) { } 
	virtual void OnCommand(WORD wNotifyCode, WORD wID, HWND hWndCtrl) { } 
	virtual void OnContextMenu(HWND hWnd, int x, int y) { } 
	virtual void OnKeyUp(int nVirtKey) { } 
	virtual void OnInitMenu(HMENU hMenu) { } 
	virtual void OnKeyDown(int nVirtKey) { } 
	virtual void OnChar(char c) { } 
 
public: 
	COGLWindow() {} 
	COGLWindow(const char *szName, bool fscreen, int w, int h, int b); 
	virtual ~COGLWindow(); 
	// this must be called before the class is used 
	static bool RegisterWindow(HINSTANCE hInstance);
}; 
 
#endif
