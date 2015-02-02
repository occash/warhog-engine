#include "windowswindow.h"

#include <Windows.h>
#include <winuser.h>

struct WindowData
{
	HWND handle;
	ULONG style;
	char title[256];
	int x, y;
	int width;
	int height;
	bool fullscreen;
	bool closed;
	bool focused;
	bool minimized;

	struct MouseData
	{
		int x, y;
		int button;
		bool grab;
		bool show;
	} mouse;
};

struct WindowMsg
{
	HWND hwnd;
	UINT uMsg;
	WPARAM wParam;
	LPARAM lParam;
};

static void grabWindow(const HWND& handle)
{
	if (handle)
	{
		RECT rect;
		GetClientRect(handle, &rect);
		ClientToScreen(handle, (LPPOINT)&rect.left);
		ClientToScreen(handle, (LPPOINT)&rect.right);
		ClipCursor(&rect);
	}
	else
		ClipCursor(NULL);
}

LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);

static ATOM registerWindowClass()
{
	WNDCLASSEX wc;
	ATOM classAtom;

	// Set window class parameters
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = &windowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(WindowData*);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDC_ICON);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("WarhogWindow");
	wc.hIconSm = NULL;

	classAtom = RegisterClassEx(&wc);
	int err = GetLastError();
	if (!classAtom)
	{
		//TODO: handle error
		return 0;
	}

	return classAtom;
}

static ATOM appWindowClass = registerWindowClass();

WindowsWindow::WindowsWindow()
	: _data(new WindowData)
{
	_data->handle = HWND();
	//_data->style = style;
	strcpy(_data->title, "Window");
	_data->x = 0;
	_data->y = 0;
	_data->width = 640;
	_data->height = 480;
	_data->fullscreen = false;
	_data->closed = false;
	_data->focused = true;
	_data->minimized = false;
	_data->mouse.show = true;
	_data->mouse.grab = false;
	_data->mouse.button = 0;
	_data->mouse.x = 0;
	_data->mouse.y = 0;
}

WindowsWindow::~WindowsWindow()
{
	delete _data;
}

void WindowsWindow::create()
{
	if (_data->handle)
		destroy();

	ULONG windowStyle = WS_CAPTION | WS_MINIMIZEBOX;
	//if (_data->style & WindowFlags::Closable)
		windowStyle |= WS_SYSMENU;
	//if (_data->style & WindowFlags::Resizable)
		windowStyle |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;

	_data->handle = CreateWindow(
		TEXT("WarhogWindow"),
		_data->title,
		windowStyle,
		0, 0, _data->width, _data->height,
		NULL, NULL,
		GetModuleHandle(NULL),
		this
		);

	// Initialize window properties
	RECT rect;
	GetWindowRect(_data->handle, &rect);
	_data->x = rect.left;
	_data->y = rect.top;

	GetClientRect(_data->handle, &rect);
	_data->width = rect.right - rect.left;
	_data->height = rect.bottom - rect.top;
}

void WindowsWindow::destroy()
{
	DestroyWindow(_data->handle);
}

bool WindowsWindow::isVisible() const
{
	return IsWindowVisible(_data->handle);
}

void WindowsWindow::setVisible(bool visible)
{
	ShowWindow(_data->handle, visible ? SW_SHOW : SW_HIDE);
	setMouseGrab(visible ? _data->handle : nullptr);
}

bool WindowsWindow::isFullscreen() const
{
	return _data->fullscreen;
}

void WindowsWindow::setFullscreen(bool fullscreen)
{
	DEVMODE dm;
	dm.dmSize = sizeof(dm);
	dm.dmPelsWidth = _data->width;
	dm.dmPelsHeight = _data->height;
	dm.dmBitsPerPel = 32;
	dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

	ChangeDisplaySettings(&dm, CDS_FULLSCREEN);

	SetWindowLong(_data->handle, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	SetWindowLong(_data->handle, GWL_EXSTYLE, WS_EX_APPWINDOW);

	SetWindowPos(_data->handle, HWND_TOP, 0, 0, _data->width, _data->height, SWP_FRAMECHANGED);
	ShowWindow(_data->handle, SW_SHOW);

	_data->fullscreen = fullscreen;
}

void WindowsWindow::close()
{
	setVisible(false);
	destroy();
}

int WindowsWindow::x() const
{
	return _data->x;
}

int WindowsWindow::y() const
{
	return _data->y;
}

int WindowsWindow::width() const
{
	return _data->width;
}

int WindowsWindow::height() const
{
	return _data->height;
}

void WindowsWindow::move(int x, int y)
{
	_data->x = x;
	_data->y = y;
	SetWindowPos(_data->handle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void WindowsWindow::resize(int w, int h)
{
	_data->width = w;
	_data->height = h;
	SetWindowPos(_data->handle, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

const char *WindowsWindow::title() const
{
	return _data->title;
}

void WindowsWindow::setTitle(const char *title)
{
	SetWindowText(_data->handle, title);
}

bool WindowsWindow::mouseGrab() const
{
	return _data->mouse.grab;
}

void WindowsWindow::setMouseGrab(bool grab)
{
	grabWindow(grab ? _data->handle : nullptr);
}

bool WindowsWindow::platformEvent(WindowsWindow *window, void *msgPtr, long *result)
{
	WindowMsg *msg = reinterpret_cast<WindowMsg *>(msgPtr);
	if (msg->uMsg == WM_NCCREATE)
	{
		WindowsWindow *window = reinterpret_cast<WindowsWindow*>(
			((LPCREATESTRUCT)msg->lParam)->lpCreateParams
			);
		//window->create(msg->hwnd);
		SetWindowLongPtr(msg->hwnd, GWLP_USERDATA, LONG_PTR(window));
		return false;
	}

	if (window)
	{
		switch (msg->uMsg)
		{
		case WM_DESTROY:
			//window->destroy(window->_data->handle);
			*result = 1;
			return true;
		case WM_CLOSE:
			window->close();
			//window->closeEvent();
			*result = 1;
			return true;
		case WM_ACTIVATE:
			if (window->_data->mouse.grab)
			{
				if (msg->wParam == WA_INACTIVE)
					grabWindow(nullptr);
				else
					grabWindow(window->_data->handle);
			}
			*result = 1;
			return true;
		case WM_MOVE:
			if (window->_data->mouse.grab)
				grabWindow(window->_data->handle);
			//window->moveEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
			*result = 1;
			return true;
		case WM_SIZE:
			if (msg->wParam == SIZE_MINIMIZED)
				window->_data->minimized = true;
			else if (msg->wParam == SIZE_RESTORED || msg->wParam == SIZE_MAXIMIZED) 
				if (window->_data->minimized)
					window->_data->minimized = false;

			//if (window->_data->style & Window::Resizable) 
			//{
				window->_data->width = LOWORD(msg->lParam);
				window->_data->height = HIWORD(msg->lParam);
				if (window->_data->width < 1) 
					window->_data->width = 1;
				if (window->_data->height < 1) 
					window->_data->height = 1;

				//window->resizeEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
			//}
			if (window->_data->mouse.grab)
				grabWindow(window->_data->handle);
			*result = 1;
			return true;
		case WM_SETFOCUS:
			window->_data->focused = true;
			window->_data->mouse.show = true;
			//window->focusInEvent();
			*result = 1;
			return true;
		case WM_KILLFOCUS:
			window->_data->focused = false;
			window->_data->mouse.show = false;
			//window->focusOutEvent();
			//TODO: release all keys
			*result = 1;
			return true;
		case WM_ENTERSIZEMOVE:
			if (window->_data->mouse.grab)
				grabWindow(nullptr);
			*result = 1;
			return true;
		case WM_EXITSIZEMOVE:
			if (window->_data->mouse.grab)
				grabWindow(window->_data->handle);
			*result = 1;
			return true;
		case WM_SHOWWINDOW:
			/*if (msg->wParam == TRUE)
				window->showEvent();
			else
				window->hideEvent();*/
			*result = 1;
			return true;
		default:
			return false;
		}
	}

	return false;
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WindowsWindow *window = reinterpret_cast<WindowsWindow*>(
		GetWindowLongPtr(hwnd, GWLP_USERDATA));
	WindowMsg msg = { hwnd, uMsg, wParam, lParam };
	long result;
	if (WindowsWindow::platformEvent(window, &msg, &result))
		return result;
	else
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}