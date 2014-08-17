#include "../../window.h"

#include <Windows.h>
#include <winuser.h>

struct WindowData
{
	HWND handle;
	ULONG style;
	int x, y;
	int width;
	int height;
	bool closed;
	/*int flags;
	bool minimized;
	bool focused;*/
};

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

Window::Window(int style) :
	_data(new WindowData)
{
	ULONG windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_VISIBLE;
	if (style & WindowStyle::Closable) 
		windowStyle |= WS_SYSMENU;
	if (style & WindowStyle::Resizable) 
		windowStyle |= WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;

	_data->handle = CreateWindow(
		TEXT("WarhogWindow"),
		TEXT("Warhog Engine"),
		windowStyle,
		0, 0, 640, 480,
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

	create((void*)_data->handle);
}

Window::~Window()
{
	destroy((void*)_data->handle);
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
	CloseWindow(_data->handle);
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

void Window::event(Window::Event e)
{
	switch (e)
	{
	case Window::Move:
		moveEvent();
		break;
	case Window::Resize:
		resizeEvent();
		break;
	case Window::Close:
		closeEvent();
		break;
	case Window::Visible:
		visibleEvent();
		break;
	default:
		break;
	}
}

void Window::create(void *data)
{
}

void Window::destroy(void *data)
{
}

void Window::moveEvent()
{
}

void Window::resizeEvent()
{
}

void Window::closeEvent()
{
	close();
}

void Window::visibleEvent()
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
	if (window)
	{
		switch (uMsg)
		{
		case WM_CLOSE:
			window->event(Window::Close);
			break;
		case WM_MOVE:
			window->event(Window::Move);
			break;
		case WM_SIZE:
			window->event(Window::Resize);
			break;
		case WM_SHOWWINDOW:
			window->event(Window::Visible);
			break;
		default:
			break;
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}