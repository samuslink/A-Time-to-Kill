#define WIN32_MEAN_AND_LEAN    
#define WIN32_EXTRA_LEAN      
#include "oglwindow.h"  
   
bool bLMB = false;      // 鼠标左键    
bool bRMB = false;      // 鼠标右键    
LPARAM Drag;            // 鼠标拖动    

// 设置OpenGL像素格式    
void COGLWindow::SetupPixelFormat()   
{   
    int pixelFormat;   
    PIXELFORMATDESCRIPTOR pfd = {    
        sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小     
        1,                                // 版本号     
        PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图     
        PFD_SUPPORT_OPENGL |              // 支持 OpenGL     
        PFD_DOUBLEBUFFER,                 // 双缓存模式     
        PFD_TYPE_RGBA,                    // RGBA 颜色模式     
        24,                               // 24 位颜色深度     
        0, 0, 0, 0, 0, 0,                 // 忽略颜色位     
        0,                                // 没有非透明度缓存     
        0,                                // 忽略移位位     
        0,                                // 无累加缓存     
        0, 0, 0, 0,                       // 忽略累加位     
        32,                               // 32 位深度缓存         
        0,                                // 无模板缓存     
        0,                                // 无辅助缓存     
        PFD_MAIN_PLANE,                   // 主层     
        0,                                // 保留     
        0, 0, 0                           // 忽略层,可见性和损毁掩模     
    };     
    pixelFormat = ChoosePixelFormat(hDC, &pfd);   
   
    SetPixelFormat(hDC, pixelFormat, &pfd);   
}   
   
// 设置调色板    
void COGLWindow::SetupPalette()   
{   
    int pixelFormat = GetPixelFormat(hDC);   
    PIXELFORMATDESCRIPTOR pfd;   
    LOGPALETTE* pPal;   
    int paletteSize;   
   
    int redMask, greenMask, blueMask;   
    int i;   
   
    DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);   
   
    if (pfd.dwFlags & PFD_NEED_PALETTE)   
        paletteSize = 1 << pfd.cColorBits;   
    else   
        return;   
   
    pPal = (LOGPALETTE*)LocalAlloc(LPTR, sizeof(LOGPALETTE) + paletteSize * sizeof(PALETTEENTRY));   
    pPal->palVersion = 0x300;   
    pPal->palNumEntries = (short)paletteSize;   
   
    //  生成一个简单的RGB颜色调色板    
    redMask   = (1 << pfd.cRedBits)   - 1;   
    greenMask = (1 << pfd.cGreenBits) - 1;   
    blueMask  = (1 << pfd.cBlueBits)  - 1;   
   
    for (i=0; i<paletteSize; ++i)   
    {   pPal->palPalEntry[i].peRed = (BYTE)(   
            (((i >> pfd.cRedShift) & redMask) * 255) / redMask);   
        pPal->palPalEntry[i].peGreen = (BYTE)(   
            (((i >> pfd.cGreenShift) & greenMask) * 255) / greenMask);   
        pPal->palPalEntry[i].peBlue = (BYTE)(   
            (((i >> pfd.cBlueShift) & blueMask) * 255) / blueMask);   
        pPal->palPalEntry[i].peFlags = 0;   
    }   
   
    hPalette = CreatePalette(pPal);   
    LocalFree(pPal);   
   
    if (hPalette)   
    {   
        DeleteObject(SelectPalette(hDC, hPalette, FALSE));   
        RealizePalette(hDC);   
    }   
}   

// 创建窗口    
bool COGLWindow::Create()   
{   
    hDC = GetDC(hWnd);   
    SetupPixelFormat();   
    SetupPalette();   
    hGLRC = wglCreateContext(hDC);   
    wglMakeCurrent(hDC, hGLRC);   
   
    return !OnCreate();   
}   
   
// 销毁窗口    
void COGLWindow::Destroy()   
{   
    if (hGLRC)   
    {      
        wglMakeCurrent(hDC, NULL);   
        wglDeleteContext(hGLRC);   
    }   
    if (hPalette)   
    {      
        DeleteObject(hPalette);   
    }   
   
    SetWindowLong(hWnd, GWL_USERDATA, (LONG)NULL);   
   
    DestroyWindow(hWnd);   
   
    // if we're in fullscreen, get out of it    
    EndFullScreen();   
}   
   
// 调色板改变    
void COGLWindow::PaletteChanged(WPARAM wParam)   
{   
    if (hGLRC && hPalette && (HWND)wParam != hWnd)   
    {      
        wglMakeCurrent(hDC, hGLRC);   
        UnrealizeObject(hPalette);   
        SelectPalette(hDC, hPalette, FALSE);   
        RealizePalette(hDC);   
    }   
}   
   
// 查询新的调色板    
BOOL COGLWindow::QueryNewPalette()   
{   
    if (hGLRC && hPalette)   
    {      
        wglMakeCurrent(hDC, hGLRC);   
        UnrealizeObject(hPalette);   
        SelectPalette(hDC, hPalette, FALSE);   
        RealizePalette(hDC);   
   
        return TRUE;   
    }   
    return FALSE;   
}   
   
// 绘制窗口    
void COGLWindow::Paint()   
{   
    PAINTSTRUCT ps;   
    BeginPaint(hWnd, &ps);   
    EndPaint(hWnd, &ps);   
}   
   
// 窗口缩放    
void COGLWindow::Size()   
{   
    if (width > height)   
        aspect = width;   
    else   
        aspect = height;   
   
    if (hGLRC)   
    {   
        glViewport(0, 0, width, height);   
        glMatrixMode(GL_PROJECTION);   
        glLoadIdentity();   
   
        float nearClip = 1.0f / 100.0f;   
        float farClip  = 256.0f;//127.0f;    
   
        gluPerspective(54.0f, (float)width/(float)height, 0.1f, 200.0f);   
   
        OnSize();   
   
        glMatrixMode(GL_MODELVIEW);   
        glLoadIdentity();   
    }   
}   
   
float COGLWindow::GetNormalizedPosX(LPARAM lParam)   
{      
    return mouseSensitivity * (float)((short)LOWORD(lParam) - width/2) / aspect;   
}   
   
float COGLWindow::GetNormalizedPosY(LPARAM lParam)   
{   
    return mouseSensitivity * (float)((short)HIWORD(lParam) - height/2) / aspect;   
}   
   
// 获取鼠标光标的位置    
int COGLWindow::GetMouseX(LPARAM lParam)   
{   
    return LOWORD(lParam);   
}   
   
// 获取鼠标光标的位置    
int COGLWindow::GetMouseY(LPARAM lParam)   
{   
    return HIWORD(lParam);   
}   
   
// 窗口消息处理函数    
LRESULT APIENTRY WndProcOGL(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)   
{   
    COGLWindow *glWindow = (COGLWindow*)GetWindowLong(hWnd, GWL_USERDATA);   
    int result;
    // 确保窗口已经创建    
    if ((glWindow == NULL) && (uMsg != WM_CREATE))   
    {      
        return DefWindowProc(hWnd, uMsg, wParam, lParam);   
    }   
   
    // 消息循环    
    switch (uMsg)   
    {      
        case WM_CREATE:         // 创建窗口    
        {   
            HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);   
            glWindow = (COGLWindow*)(((LPCREATESTRUCT)lParam)->lpCreateParams);   
   
            SetWindowLong(hWnd, GWL_USERDATA, (LONG)glWindow);   
            glWindow->hWnd = hWnd;   
   
            return glWindow->Create();   
        }   
        case WM_QUIT:   
        case WM_CLOSE:  // 窗口关闭 
			result = MessageBox(hWnd,"Are you sure you want to close this application?","WM_CLOSE Message Processor",MB_YESNO|MB_ICONQUESTION);

			//does the user want to close
			if(result == IDYES)
			{
				glWindow->Destroy();   
				PostQuitMessage(0); 
				//call default handler
				return(DefWindowProc(hWnd,uMsg,wParam,lParam));
			}//end if
			else //throw message away
				return(0);     
        case WM_DESTROY:            // 窗口销毁    
            glWindow->Destroy();
            PostQuitMessage(0);   
            return 0;   
   
        case WM_ACTIVATEAPP:        // 激活应用程序    
               
            if (wParam)   
            {      
                if (glWindow->fullscreen)   
                    glWindow->BeginFullScreen(glWindow->width, glWindow->height, glWindow->bits);   
   
                ShowWindow(hWnd, SW_RESTORE);   
                UpdateWindow(hWnd);   
            }   
            else   
            {      
                ShowWindow(hWnd, SW_MINIMIZE);   
                UpdateWindow(hWnd);   
                   
                if (glWindow->fullscreen)   
                    glWindow->EndFullScreen();   
            }   
            return 0;   
   
        case WM_PALETTECHANGED:     // 调色板改变    
            glWindow->PaletteChanged(wParam);   
            return 0;   
   
        case WM_QUERYNEWPALETTE:        // 新调色板    
            return glWindow->QueryNewPalette();   
   
        case WM_PAINT:              // 绘制窗口    
            glWindow->Paint();   
            return 0;   
   
        case WM_SIZE:               // 窗口缩放    
            if (wParam != SIZE_MINIMIZED)   
            {      
                glWindow->width = LOWORD(lParam);   
                glWindow->height= HIWORD(lParam);   
                glWindow->Size();   
            }   
            return 0;   
   
        case WM_LBUTTONDOWN:        // 按下鼠标左键      
                SetCapture(hWnd);   
                Drag = lParam;   
                bLMB = true;   
                glWindow->OnMouseDownL(glWindow->GetNormalizedPosX(lParam), glWindow->GetNormalizedPosY(lParam));     
            break;   
   
        case WM_RBUTTONDOWN:        // 按下鼠标右键      
                SetCapture(hWnd);   
                Drag = lParam;   
                bRMB = true;   
                glWindow->OnMouseDownR(glWindow->GetNormalizedPosX(lParam), glWindow->GetNormalizedPosY(lParam));     
            break;   
   
        case WM_MOUSEMOVE:          // 鼠标移动    
        {      
           // if (!glWindow->useDInput)   
			//{
			int oldX,oldY;
			oldX = glWindow->mouseX;
			oldY = glWindow->mouseY;

			glWindow->mouseX = glWindow->GetMouseX(lParam);
			glWindow->mouseY = glWindow->GetMouseY(lParam);

			glWindow->OnMouseMove(glWindow->mouseX - oldX, glWindow->mouseY - oldY);
			/*
			    int x  = glWindow->mouseX = glWindow->GetMouseX(lParam); 
				int y  = glWindow->mouseY = glWindow->GetMouseY(lParam);
                int dx = x - glWindow->GetMouseX(Drag); 
                int dy = y - glWindow->GetMouseY(Drag); 
				glWindow->OnMouseMove(dx,dy);
                glWindow->OnMouseMove(x,y, glWindow->width, glWindow->height); 
                if (GetCapture() == hWnd)   
                {   
                    // 鼠标左键    
                    if (bLMB)   
                    {   
                        glWindow->OnMouseDragL(x,y, dx,dy);   
                    }   
                       
                    // 鼠标右键    
                    if (bRMB)   
                    {      
                        glWindow->OnMouseDragR(x,y, dx,dy);   
                    }   
   
                    Drag = lParam;  
					
                }
				//std::cin.ignore();
				// } 
				*/
            break;   
        }   
   
        case WM_LBUTTONUP:          // 释放鼠标左键    
          //  if (!glWindow->useDInput)   
           // {   
                if ((GetCapture() == hWnd) && !bRMB)   
                {   
                    ReleaseCapture();   
                }   
   
                bLMB = false;   
                glWindow->OnMouseUpL();   
           // }   
            break;   
   
        case WM_RBUTTONUP:          // 释放鼠标右键    
           // if (!glWindow->useDInput)   
           // {   
                if ((GetCapture() == hWnd) && !bLMB)   
                {   
                    ReleaseCapture();   
                }   
                bRMB = false;   
                glWindow->OnMouseUpR();   
           // }   
            break;   
   
        case WM_KEYUP:   
         //   if (!glWindow->useDInput)   
           // {   
                glWindow->OnKeyUp((int)wParam);   
           // }   
            return 0;   
   
        case WM_KEYDOWN:   
         //   if (!glWindow->useDInput)   
           // {   
                glWindow->OnKeyDown((int)wParam);   
           // }   
            return 0;   

        default:   
            break;   
    }   
    return DefWindowProc(hWnd, uMsg, wParam, lParam);   
}   
   
// 注册窗口类    
bool COGLWindow::RegisterWindow(HINSTANCE hInst)   
{   
    WNDCLASS windowClass;       // 窗口类    
   
    windowClass.style        = 0;   
    windowClass.lpfnWndProc  = WndProcOGL;   
    windowClass.cbClsExtra   = 0;   
    windowClass.cbWndExtra   = 0;   
    windowClass.hInstance    = hInst;   
    windowClass.hIcon        = 0;   
    windowClass.hCursor      = LoadCursor(NULL, IDC_ARROW);   
    windowClass.hbrBackground = NULL;   
    windowClass.lpszMenuName     = NULL;   
    windowClass.lpszClassName = "Engine";   
    // 注册窗口类    
    if (!RegisterClass(&windowClass))   
        return false;   
   
    return true;   
}   
// 进入全屏显示状态    
void COGLWindow::BeginFullScreen(int width, int height, int bits)   
{   
    // 保存当前的显示状态    
    iPrevWidth = GetSystemMetrics(SM_CXSCREEN);   
    iPrevHeight = GetSystemMetrics(SM_CYSCREEN);   
       
    // 设置新的显示状态    
    DEVMODE dm;   
    memset(&dm, 0, sizeof(dm));   
    dm.dmSize   = sizeof(DEVMODE);   
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;   
    dm.dmPelsWidth  = width;   
    dm.dmPelsHeight = height;   
    dm.dmBitsPerPel = bits;   
    ChangeDisplaySettings(&dm, CDS_FULLSCREEN);   
}   
   
// 结束全屏模式    
void COGLWindow::EndFullScreen()   
{   
    ChangeDisplaySettings(NULL, 0);   
}   
   
// 构造函数    
COGLWindow::COGLWindow(const char *szName, bool fscreen, int w, int h, int b)   
{   
    RECT windowRect;   
    DWORD dwStyle;   
    DWORD dwExStyle;   
   
    fullscreen = fscreen;   
    width = w;   
    height = h;   
    bits = b;   
   
    windowRect.left = (long)0;   
    windowRect.right = (long)width;   
    windowRect.top = (long)0;   
    windowRect.bottom = (long)height;   
   
    if (fullscreen)   
    {   
        dwExStyle = WS_EX_APPWINDOW;   
        dwStyle = WS_POPUP;   
    }   
    else   
    {   
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   
        dwStyle = WS_OVERLAPPEDWINDOW;   
    }   
   
    AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);   
       
    // 创建窗口    
    if (fullscreen)   
    {   
        BeginFullScreen(width, height, bits);   
        hWnd = CreateWindowEx(NULL, "Engine", szName, dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,   
                          0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),   
                          NULL, NULL, (HINSTANCE)GetModuleHandle(NULL), (void*)this);   
    }   
    else   
    {   
   
        hWnd = CreateWindowEx(NULL, "Engine", szName, dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,   
                          0, 0, width, height, NULL, NULL, (HINSTANCE)GetModuleHandle(NULL),(void*)this);   
    }   
   
    if (hWnd == NULL)    
        throw "ERROR: Creating OpenGL Window!";   
   
    ShowWindow(hWnd, SW_SHOW);   
    UpdateWindow(hWnd);   
   
    mouseSensitivity = 2.0f;   
   
    //inputSystem = new CInputSystem;   
//    useDInput = inputSystem->Initialize(hWnd, (HINSTANCE)GetModuleHandle(NULL), true, IS_USEKEYBOARD | IS_USEMOUSE);   
    SetForegroundWindow(hWnd);   
    SetCapture(hWnd);   
    SetFocus(hWnd);   
   
    if (useDInput)   
    {   
        //inputSystem->AcquireAll();   
        //inputSystem->Update();   
    }   
   
    ShowCursor(FALSE);   
}   
   
// 析构函数    
COGLWindow::~COGLWindow()   
{   
//    delete inputSystem;   
    if (hGLRC)   
        Destroy();   
    if (fullscreen)   
        EndFullScreen();   
    ShowCursor(TRUE);   
}  
