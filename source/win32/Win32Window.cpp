/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/// "THE BEER-WARE LICENSE" (Revision 42):
/// <mikko.romppainen@kamk.fi> wrote this file.  As long as you retain this notice you
/// can do whatever you want with this stuff. If we meet some day, and you think
/// this stuff is worth it, you can buy me a beer in return. Mikko Romppainen.
/// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#include <Win32Window.h>
#include <graphics/GraphicsApplication.h>
#include <EGL/eglplatform.h>
#include <iostream>
#include <gl/GLU.h>

namespace engine
{
	LRESULT WINAPI WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;                       // handle to device context 
		RECT rcClient;                 // client area rectangle 
		POINT ptClientUL;              // client upper left corner 
		POINT ptClientLR;              // client lower right corner 
		static POINTS ptsBegin;        // beginning point 
		static POINTS ptsEnd;          // new endpoint 
		static POINTS ptsPrevEnd;      // previous endpoint 
		static BOOL fPrevLine = FALSE; // previous line flag 

		LRESULT  lRet = 1;
		switch (uMsg)
		{
		case WM_CREATE:
			break;
		case WM_LBUTTONDOWN:

			// Capture mouse input. 

			SetCapture(hwnd);

			// Retrieve the screen coordinates of the client area, 
			// and convert them into client coordinates. 

			GetClientRect(hwnd, &rcClient);
			ptClientUL.x = rcClient.left;
			ptClientUL.y = rcClient.top;

			// Add one to the right and bottom sides, because the 
			// coordinates retrieved by GetClientRect do not 
			// include the far left and lowermost pixels. 

			ptClientLR.x = rcClient.right + 1;
			ptClientLR.y = rcClient.bottom + 1;
			ClientToScreen(hwnd, &ptClientUL);
			ClientToScreen(hwnd, &ptClientLR);

			// Copy the client coordinates of the client area 
			// to the rcClient structure. 
			
			//Confine the mouse cursor 
			// to the client area by passing the rcClient structure 
			// to the ClipCursor function. 

			/*SetRect(&rcClient, ptClientUL.x, ptClientUL.y,
				ptClientLR.x, ptClientLR.y);
			ClipCursor(&rcClient);*/

			// Convert the cursor coordinates into a POINTS 
			// structure, which defines the beginning point of the 
			// line drawn during a WM_MOUSEMOVE message. 

			ptsBegin = MAKEPOINTS(lParam);
			InputManager::getMouseX();
			InputManager::getMouseY();
			return 0;

		case WM_MOUSEMOVE:

			// When moving the mouse, the user must hold down 
			// the left mouse button to draw lines. 

			if (wParam & MK_LBUTTON|| wParam & MK_RBUTTON)
			{

				// Retrieve a device context (DC) for the client area. 

				hdc = GetDC(hwnd);

				// The following function ensures that pixels of 
				// the previously drawn line are set to white and 
				// those of the new line are set to black. 

				SetROP2(hdc, R2_NOTXORPEN);

				// If a line was drawn during an earlier WM_MOUSEMOVE 
				// message, draw over it. This erases the line by 
				// setting the color of its pixels to white. 

				if (fPrevLine)
				{
					MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
						(LPPOINT)NULL);
					LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
				}

				// Convert the current cursor coordinates to a 
				// POINTS structure, and then draw a new line. 

				ptsEnd = MAKEPOINTS(lParam);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
				LineTo(hdc, ptsEnd.x, ptsEnd.y);

				// Set the previous line flag, save the ending 
				// point of the new line, and then release the DC. 

				fPrevLine = TRUE;
				ptsPrevEnd = ptsEnd;
				ReleaseDC(hwnd, hdc);
			}
			break;

		
			if (wParam & MK_LBUTTON)
			{

				// Retrieve a device context (DC) for the client area. 

				hdc = GetDC(hwnd);

				// The following function ensures that pixels of 
				// the previously drawn line are set to white and 
				// those of the new line are set to black. 

				SetROP2(hdc, R2_NOTXORPEN);

				// If a line was drawn during an earlier WM_MOUSEMOVE 
				// message, draw over it. This erases the line by 
				// setting the color of its pixels to white. 

				if (fPrevLine)
				{
					MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
						(LPPOINT)NULL);
					LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
				}

				// Convert the current cursor coordinates to a 
				// POINTS structure, and then draw a new line. 

				ptsEnd = MAKEPOINTS(lParam);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
				LineTo(hdc, ptsEnd.x, ptsEnd.y);

				// Set the previous line flag, save the ending 
				// point of the new line, and then release the DC. 

				fPrevLine = TRUE;
				ptsPrevEnd = ptsEnd;
				ReleaseDC(hwnd, hdc);
			}
			break;

		case WM_LBUTTONUP:

			// The user has finished drawing the line. Reset the 
			// previous line flag, release the mouse cursor, and 
			// release the mouse capture. 

			fPrevLine = FALSE;
			ClipCursor(NULL);
			ReleaseCapture();
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

			//left MOUSE BUTTON PRESS ENDS_______________________________________________

			// When moving the mouse, the user must hold down 
			// the right mouse button to draw lines. 

		case WM_RBUTTONDOWN:

			SetCapture(hwnd);

			// Retrieve the screen coordinates of the client area, 
			// and convert them into client coordinates. 

			GetClientRect(hwnd, &rcClient);
			ptClientUL.x = rcClient.left;
			ptClientUL.y = rcClient.top;

			// Add one to the right and bottom sides, because the 
			// coordinates retrieved by GetClientRect do not 
			// include the far left and lowermost pixels. 

			ptClientLR.x = rcClient.right + 1;
			ptClientLR.y = rcClient.bottom + 1;
			ClientToScreen(hwnd, &ptClientUL);
			ClientToScreen(hwnd, &ptClientLR);

			// Convert the cursor coordinates into a POINTS 
			// structure, which defines the beginning point of the 
			// line drawn during a WM_MOUSEMOVE message. 

			ptsBegin = MAKEPOINTS(lParam);
			InputManager::getMouseX();
			InputManager::getMouseY();
			return 0;

			//case WM_MOUSEMOVE:

			//when moving the mouse, the user must hold down the right mouse button to draw lines.

			/*if (wParam & MK_RBUTTON)
			{

				// Retrieve a device context (DC) for the client area. 

				hdc = GetDC(hwnd);

				// The following function ensures that pixels of 
				// the previously drawn line are set to white and 
				// those of the new line are set to black. 

				SetROP2(hdc, R2_NOTXORPEN);

				// If a line was drawn during an earlier WM_MOUSEMOVE 
				// message, draw over it. This erases the line by 
				// setting the color of its pixels to white. 

				if (fPrevLine)
				{
					MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
						(LPPOINT)NULL);
					LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
				}

				// Convert the current cursor coordinates to a 
				// POINTS structure, and then draw a new line. 

				ptsEnd = MAKEPOINTS(lParam);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
				LineTo(hdc, ptsEnd.x, ptsEnd.y);

				// Set the previous line flag, save the ending 
				// point of the new line, and then release the DC. 

				fPrevLine = TRUE;
				ptsPrevEnd = ptsEnd;
				ReleaseDC(hwnd, hdc);
			}
			break;*/
			
					
			if (wParam & MK_RBUTTON)
			{

				// Retrieve a device context (DC) for the client area. 

				hdc = GetDC(hwnd);

				// The following function ensures that pixels of 
				// the previously drawn line are set to white and 
				// those of the new line are set to black. 

				SetROP2(hdc, R2_NOTXORPEN);

				// If a line was drawn during an earlier WM_MOUSEMOVE 
				// message, draw over it. This erases the line by 
				// setting the color of its pixels to white. 

				if (fPrevLine)
				{
					MoveToEx(hdc, ptsBegin.x, ptsBegin.y,
						(LPPOINT)NULL);
					LineTo(hdc, ptsPrevEnd.x, ptsPrevEnd.y);
				}

				// Convert the current cursor coordinates to a 
				// POINTS structure, and then draw a new line. 

				ptsEnd = MAKEPOINTS(lParam);
				MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
				LineTo(hdc, ptsEnd.x, ptsEnd.y);

				// Set the previous line flag, save the ending 
				// point of the new line, and then release the DC. 

				fPrevLine = TRUE;
				ptsPrevEnd = ptsEnd;
				ReleaseDC(hwnd, hdc);
			}
			break;

		case WM_RBUTTONUP:

			// The user has finished drawing the line. Reset the 
			// previous line flag, release the mouse cursor, and 
			// release the mouse capture. 

			fPrevLine = FALSE;
			ClipCursor(NULL);
			ReleaseCapture();
			return 0;

		
			PostQuitMessage(0);
			break;

		

		case WM_PAINT:
		{
			Win32Window *window = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hwnd, GWL_USERDATA);			
			// Call application render and pass pointer to Graphics-object.
 			window->getApplication()->render(window, window->getGraphics());
			ValidateRect(window->getNativeWindow(), NULL);
		}
		break;

		
		case WM_CHAR:
		{
			POINT      point;
//			Win32Window *esContext = (Win32Window*)(LONG_PTR)GetWindowLongPtr(hWnd, GWL_USERDATA);
			GetCursorPos(&point);
		}
		break;

		default:
			lRet = DefWindowProc(hwnd, uMsg, wParam, lParam);
			break;
		}

		return lRet;
	}



	Win32Window::Win32Window(int width, int height, const std::wstring& title)
		: Window()
		, hwnd(NULL)
		, m_active(false) // Assume not yet active
		
	{
		setSize(width, height); // Set size to base class

		WNDCLASS wndclass = { 0 };
		DWORD    wStyle = 0;
		RECT     windowRect;
		HINSTANCE hInstance = GetModuleHandle(NULL);
		
		wndclass.style = CS_OWNDC;
		wndclass.lpfnWndProc = (WNDPROC)WindowProc;
		wndclass.hInstance = hInstance;
		wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszClassName = L"opengles2.0";

		if (!RegisterClass(&wndclass))
			return; // fail!
		
		wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

		// Adjust the window rectangle so that the client area has
		// the correct number of pixels
		windowRect.left = 0;
		windowRect.top = 0;
		windowRect.right = width - windowRect.left;
		windowRect.bottom = height - windowRect.top;

		AdjustWindowRect(&windowRect, wStyle, FALSE);
		
		hwnd = CreateWindow(
			L"opengles2.0",
			title.c_str(),
			wStyle,
			0,
			0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			NULL,
			NULL,
			hInstance,
			NULL);

		// Set the ESContext* to the GWL_USERDATA so that it is available to the 
		// ESWindowProc
		SetWindowLongPtr(hwnd, GWL_USERDATA, (LONG)(LONG_PTR)this);
		
		if (hwnd == NULL)
		{
			// TODO: Unregister window class if fail
			return; // fail!
		}

		ShowWindow(hwnd, TRUE);

		// success!
		m_active = true;
	}


	Win32Window::~Win32Window()
	{
	}


	// Returns native window handle
	EGLNativeWindowType Win32Window::getNativeWindow() const
	{
		return hwnd;
	}


	bool Win32Window::updateMessages()
	{
		MSG msg = { 0 };
		int gotMsg = (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0);
		if (gotMsg)
		{
			if (msg.message == WM_QUIT)
			{
				m_active = false;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			SendMessage(getNativeWindow(), WM_PAINT, 0, 0);
		}
		return m_active;
	}

	InputManager::InputManager()
	{
		
		
	}
	InputManager::~InputManager()
	{

	}

	void InputManager::getMouseX()
	{
			POINT p;
		if (GetCursorPos(&p))
		{
			std::cout<<"X = coordinate " << p.x<<std::endl;
			
		}
		//cursor position now in p.x
	}

	void InputManager::getMouseY()
	{
		POINT p;
		if (GetCursorPos(&p))
		{			
			std::cout << "Y = coordinate " << p.y<<std::endl;
		}
		//cursor position now in p.y
	}
		
}