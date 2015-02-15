#include "windowswindow.h"
#include "windowsinput.h"

#include <Windows.h>
#include <winuser.h>

#include <bitset>

struct WindowData
{
    HWND handle = HWND();
    bool visible = false;
    NativeWindow::Styles styles = NativeWindow::Clozable | NativeWindow::Resizable;
    NativeWindow::States states = NativeWindow::Normal;
    char title[256];
    int x = 0, y = 0;
    int width = 640;
    int height = 480;

    struct MouseData
    {
        int x = 0, y = 0;
        int button = 0;
        bool grab = false;
        bool visible = true;
    } mouse;

	struct KeyData
	{
		std::bitset<Input::NUM_KEYS> keys;
	} keyboard;
};

struct WindowMsg
{
    HWND hwnd;
    UINT uMsg;
    WPARAM wParam;
    LPARAM lParam;
};

static void GrabCursor(const HWND& handle, bool grab)
{
    if (grab)
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

static unsigned int translateKey(unsigned int vkey)
{
	unsigned int ret = 0;
	switch (vkey)
	{
	case VK_ESCAPE: ret = Input::KEY_ESC; break;
	case VK_TAB: ret = Input::KEY_TAB; break;
	case VK_RETURN: ret = Input::KEY_RETURN; break;
	case VK_BACK: ret = Input::KEY_BACKSPACE; break;
	case VK_DELETE: ret = Input::KEY_DELETE; break;
	case VK_INSERT: ret = Input::KEY_INSERT; break;
	case VK_HOME: ret = Input::KEY_HOME; break;
	case VK_END: ret = Input::KEY_END; break;
	case VK_PRIOR: ret = Input::KEY_PGUP; break;
	case VK_NEXT: ret = Input::KEY_PGDOWN; break;
	case VK_LEFT: ret = Input::KEY_LEFT; break;
	case VK_RIGHT: ret = Input::KEY_RIGHT; break;
	case VK_UP: ret = Input::KEY_UP; break;
	case VK_DOWN: ret = Input::KEY_DOWN; break;
	case VK_SHIFT: ret = Input::KEY_SHIFT; break;
	case VK_MENU: ret = Input::KEY_ALT; break;
	case VK_CONTROL: ret = Input::KEY_CTRL; break;
	case VK_SCROLL: ret = Input::KEY_SCROLL; break;
	case VK_CAPITAL: ret = Input::KEY_CAPS; break;
	case VK_NUMLOCK: ret = Input::KEY_NUM; break;
	case VK_F1: ret = Input::KEY_F1; break;
	case VK_F2: ret = Input::KEY_F2; break;
	case VK_F3: ret = Input::KEY_F3; break;
	case VK_F4: ret = Input::KEY_F4; break;
	case VK_F5: ret = Input::KEY_F5; break;
	case VK_F6: ret = Input::KEY_F6; break;
	case VK_F7: ret = Input::KEY_F7; break;
	case VK_F8: ret = Input::KEY_F8; break;
	case VK_F9: ret = Input::KEY_F9; break;
	case VK_F10: ret = Input::KEY_F10; break;
	case VK_F11: ret = Input::KEY_F11; break;
	case VK_F12: ret = Input::KEY_F12; break;
	default:
		ret = MapVirtualKey(vkey, MAPVK_VK_TO_CHAR);
		if (ret >= Input::KEY_ESC) ret = 0;
		else if (ret >= 'A' && ret <= 'Z') ret -= 'A' - 'a';
	}
	return ret;
}

LRESULT CALLBACK windowProc(HWND, UINT, WPARAM, LPARAM);

static bool registerWindowClass()
{
    WNDCLASSEX wc;
    ATOM classAtom;

    // Set window class parameters
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc = &windowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(WindowData *);
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
        return false;
    }

    return true;
}

static bool classRegistered = false;

WindowsWindow::WindowsWindow()
    : _data(new WindowData)
{
    strcpy(_data->title, "Warhog Engine");
}

WindowsWindow::~WindowsWindow()
{
    delete _data;
}

void WindowsWindow::create()
{
    if (!classRegistered)
        classRegistered = registerWindowClass();

    if (_data->handle)
        destroy();

    ULONG windowStyle = WS_CAPTION | WS_MINIMIZEBOX;
    if (_data->styles & NativeWindow::Clozable)
        windowStyle |= WS_SYSMENU;
    if (_data->styles & NativeWindow::Resizable)
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
    return _data->visible;
}

void WindowsWindow::setVisible(bool visible)
{
    int showState = 0;
    if (_data->states & NativeWindow::Active)
    {
        if (_data->states & NativeWindow::Mimimized)
            showState = SW_SHOWMINIMIZED;
        else if (_data->states & NativeWindow::Maximized)
            showState = SW_SHOWMAXIMIZED;
        else
            showState = SW_SHOW;
    }
    else
    {
        if (_data->states & NativeWindow::Normal)
            showState = SW_SHOWNOACTIVATE;
        else if (_data->states & NativeWindow::Mimimized)
            showState = SW_MINIMIZE;
        else if (_data->states & NativeWindow::Maximized)
            showState = SW_MAXIMIZE;
    }

    _data->visible = visible;
    ShowWindow(_data->handle, visible ? showState : SW_HIDE);
    setMouseGrab(_data->mouse.grab);
}

NativeWindow::States WindowsWindow::states()
{
    return _data->states;
}

void WindowsWindow::setStates(NativeWindow::States states)
{
    _data->states = states;
}

/*  bool WindowsWindow::isFullscreen() const
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
    }*/

int WindowsWindow::x() const
{
    return _data->x;
}

int WindowsWindow::y() const
{
    return _data->y;
}

void WindowsWindow::move(int x, int y)
{
    _data->x = x;
    _data->y = y;
    SetWindowPos(_data->handle, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

int WindowsWindow::width() const
{
    return _data->width;
}

int WindowsWindow::height() const
{
    return _data->height;
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
    strcpy(_data->title, title);
    SetWindowText(_data->handle, title);
}

bool WindowsWindow::isMouseGrabbed() const
{
    return _data->mouse.grab;
}

void WindowsWindow::setMouseGrab(bool grab)
{
    _data->mouse.grab = grab;
    GrabCursor(_data->handle, grab);
}

bool WindowsWindow::isCursorVisible() const
{
    return _data->mouse.visible;
}

void WindowsWindow::setCursorVisible(bool visible)
{
    _data->mouse.visible = visible;
    //SetCursor(visible ? LoadCursor(NULL, IDC_ARROW) : NULL);
}

void *WindowsWindow::handle() const
{
    return _data->handle;
}

bool WindowsWindow::platformEvent(WindowsWindow *window, void *msgPtr, long *result)
{
    WindowMsg *msg = reinterpret_cast<WindowMsg *>(msgPtr);
    if (msg->uMsg == WM_NCCREATE)
    {
        WindowsWindow *window = reinterpret_cast<WindowsWindow *>(
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
            window->setVisible(false);
            window->destroy();
            //window->closeEvent();
            *result = 1;
            return true;
        case WM_ACTIVATE:
            if (msg->wParam == WA_INACTIVE)
            {
                window->_data->states &= ~NativeWindow::Active;
                if (window->_data->mouse.grab)
                    GrabCursor(nullptr, false);
            }
            else
            {
                window->_data->states |= NativeWindow::Active;
                if (window->_data->mouse.grab)
                    GrabCursor(window->_data->handle, true);
            }
            *result = 1;
            return true;
        case WM_MOVE:
            if (window->_data->mouse.grab)
                GrabCursor(window->_data->handle, true);
            //window->moveEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
            *result = 1;
            return true;
        case WM_SIZE:
            if (msg->wParam == SIZE_MINIMIZED)
                window->_data->states |= NativeWindow::Mimimized;
            else if (msg->wParam == SIZE_MAXIMIZED)
                window->_data->states |= NativeWindow::Maximized;
            else if (msg->wParam == SIZE_RESTORED)
            {
                window->_data->states &= ~NativeWindow::Mimimized;
                window->_data->states &= ~NativeWindow::Maximized;
            }

            window->_data->width = LOWORD(msg->lParam);
            window->_data->height = HIWORD(msg->lParam);
            if (window->_data->width < 1)
                window->_data->width = 1;
            if (window->_data->height < 1)
                window->_data->height = 1;

            //window->resizeEvent(LOWORD(msg->lParam), HIWORD(msg->lParam));
            if (window->_data->mouse.grab)
                GrabCursor(window->_data->handle, true);
            *result = 1;
            return true;
        /*  case WM_SETFOCUS:
            window->_data->states |= NativeWindow::Active;
            //window->focusInEvent();
             result = 1;
            return true;
            case WM_KILLFOCUS:
            window->_data->states &= ~NativeWindow::Active;
            //window->focusOutEvent();
            //TODO: release all keys
             result = 1;
            return true;*/
        case WM_ENTERSIZEMOVE:
            if (window->_data->mouse.grab)
                GrabCursor(nullptr, false);
            *result = 1;
            return true;
        case WM_EXITSIZEMOVE:
            if (window->_data->mouse.grab)
                GrabCursor(window->_data->handle, true);
            *result = 1;
            return true;
        case WM_SHOWWINDOW:
            window->_data->visible = (msg->wParam == TRUE);
            /*  if (msg->wParam == TRUE)
                window->showEvent();
                else
                window->hideEvent();*/
            *result = 1;
            return true;
        case WM_SETCURSOR:
            if (LOWORD(msg->lParam) == HTCLIENT)
            {
                SetCursor(window->_data->mouse.visible ?
                          LoadCursor(NULL, IDC_ARROW) : NULL);
            }
            *result = 1;
            return true;
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			unsigned int key = translateKey((unsigned int)msg->wParam);
			window->_data->keyboard.keys.set(key, true);
			*result = 1;
			return true;
		}
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			unsigned int key = translateKey((unsigned int)msg->wParam);
			window->_data->keyboard.keys.set(key, false);
			*result = 1;
			return true;
		}
        default:
            return false;
        }
    }

    return false;
}

LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WindowsWindow *window = reinterpret_cast<WindowsWindow *>(
                                GetWindowLongPtr(hwnd, GWLP_USERDATA));
    WindowMsg msg = { hwnd, uMsg, wParam, lParam };
    long result;
    if (WindowsWindow::platformEvent(window, &msg, &result))
        return result;
    else
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
}