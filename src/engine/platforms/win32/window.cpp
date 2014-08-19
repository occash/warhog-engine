#include "../../window.h"

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

static void grabWindow(WindowData *data)
{
	if (data)
	{
		RECT rect;
		GetClientRect(data->handle, &rect);
		ClientToScreen(data->handle, (LPPOINT)&rect.left);
		ClientToScreen(data->handle, (LPPOINT)&rect.right);
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

Window::Window(int style, char *title, int width, int height) :
	_data(new WindowData)
{
	ULONG windowStyle = WS_CAPTION | WS_MINIMIZEBOX;
	if (style & WindowFlags::Closable) 
		windowStyle |= WS_SYSMENU;
	if (style & WindowFlags::Resizable) 
		windowStyle |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;

	_data->handle = CreateWindow(
		TEXT("WarhogWindow"),
		title,
		windowStyle,
		0, 0, width, height,
		NULL, NULL,
		GetModuleHandle(NULL),
		this
		);
	_data->style = style;
	strcpy(_data->title, title);
	_data->closed = false;
	_data->focused = true;
	_data->minimized = false;
	_data->mouse.show = true;
	_data->mouse.grab = false;

	// Initialize window properties
	RECT rect;
	GetWindowRect(_data->handle, &rect);
	_data->x = rect.left;
	_data->y = rect.top;

	GetClientRect(_data->handle, &rect);
	_data->width = rect.right - rect.left;
	_data->height = rect.bottom - rect.top;

	create(_data->handle);
}

Window::~Window()
{
	destroy(_data->handle);
	DestroyWindow(_data->handle);
	delete _data;
}

int Window::x() const
{
	return _data->x;
}

int Window::y() const
{
	return _data->y;
}

int Window::width() const
{
	return _data->width;
}

int Window::height() const
{
	return _data->height;
}

char *Window::title() const
{
	return _data->title;
}

bool Window::isVisible() const
{
	return IsWindowVisible(_data->handle);
}

bool Window::isGrabMouse() const
{
	return _data->mouse.grab;
}

void Window::setPosition(int x, int y)
{
	_data->x = x;
	_data->y = y;
	SetWindowPos(_data->handle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::setSize(int w, int h)
{
	_data->width = w;
	_data->height = h;
	SetWindowPos(_data->handle, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER);
}

void Window::setTitle(const char *title)
{
	SetWindowText(_data->handle, title);
}

void Window::setVisible(bool v)
{
	ShowWindow(_data->handle, v ? SW_SHOW : SW_HIDE);
}

void Window::setMouseGrab(bool g)
{
	_data->mouse.grab = g;
	grabWindow(g && isVisible() ? _data : nullptr);
}

void Window::show()
{
	setVisible(true);
}

void Window::hide()
{
	setVisible(false);
}

void Window::showFullscreen()
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
}

void Window::close()
{
	setVisible(false);
	if (_data->style & Window::DestroyOnClose)
		DestroyWindow(_data->handle);
}

void Window::update()
{
	MSG message;
	while (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
	{
		if (GetMessage(&message, NULL, 0, 0) == 0) break;
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

bool Window::platformEvent(Window *window, void *msgPtr, long *result)
{
	WindowMsg *msg = reinterpret_cast<WindowMsg *>(msgPtr);
	if (window)
	{
		switch (msg->uMsg)
		{
		case WM_CLOSE:
			window->closeEvent();
			*result = 1;
			return true;
		case WM_ACTIVATE:
			if (window->_data->mouse.grab)
			{
				if (msg->wParam == WA_INACTIVE)
					grabWindow(nullptr);
				else
					grabWindow(window->_data);
			}
			*result = 1;
			return true;
		case WM_MOVE:
			if (window->_data->mouse.grab)
				grabWindow(window->_data);
			window->moveEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
			*result = 1;
			return true;
		case WM_SIZE:
			if (msg->wParam == SIZE_MINIMIZED)
				window->_data->minimized = true;
			else if (msg->wParam == SIZE_RESTORED || msg->wParam == SIZE_MAXIMIZED) 
				if (window->_data->minimized)
					window->_data->minimized = false;

			if (window->_data->style & Window::Resizable) 
			{
				window->_data->width = LOWORD(msg->lParam);
				window->_data->height = HIWORD(msg->lParam);
				if (window->_data->width < 1) 
					window->_data->width = 1;
				if (window->_data->height < 1) 
					window->_data->height = 1;

				window->resizeEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
			}
			if (window->_data->mouse.grab)
				grabWindow(window->_data);
			*result = 1;
			return true;
		case WM_SETFOCUS:
			window->_data->focused = true;
			window->_data->mouse.show = true;
			window->focusInEvent();
			*result = 1;
			return true;
		case WM_KILLFOCUS:
			window->_data->focused = false;
			window->_data->mouse.show = false;
			window->focusOutEvent();
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
				grabWindow(window->_data);
			*result = 1;
			return true;
		case WM_SHOWWINDOW:
			if (msg->wParam == TRUE)
				window->showEvent();
			else
				window->hideEvent();
			*result = 1;
			return true;
		default:
			return false;
		}
	}

	return false;
}

void Window::create(void *data)
{
}

void Window::destroy(void *data)
{
}

void Window::moveEvent(int x, int y)
{
}

void Window::resizeEvent(int w, int h)
{
}

void Window::closeEvent()
{
	close();
}

void Window::focusInEvent()
{
}

void Window::focusOutEvent()
{
}

void Window::showEvent()
{
}

void Window::hideEvent()
{
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		Window *window = reinterpret_cast<Window *>(
			((LPCREATESTRUCT)lParam)->lpCreateParams
			);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, LONG_PTR(window));
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	Window *window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	WindowMsg msg = { hwnd, uMsg, wParam, lParam };
	long result;
	if (Window::platformEvent(window, &msg, &result))
		return result;
	else
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
}