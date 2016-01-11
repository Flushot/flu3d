#include "Window.h"
#include <string>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

Window::Window(wchar_t *title, int x, int y, int width, int height) {
	srand((unsigned)time(0));

	_hInstance = (HINSTANCE)GetModuleHandle(NULL);
	_title = title;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_isCreated = false;
	_isRegistered = false;
	create();
}
Window::~Window() {
	if (_isRegistered)
		UnregisterClass((wchar_t *)&_className, _hInstance);
}

void Window::getRandomClassName(wchar_t *in, int len) {
	const int min = 97;
	const int max = 122;
	int range = (max - min) + 1;
	for (int i = 0; i < len; ++i)
		in[i] = min + int(range * rand() / (RAND_MAX + 1.0));
	in[len] = 0;
}

void Window::create() {
	getRandomClassName((wchar_t *)&_className, 16);

	WNDCLASSEX wcx;
	wcx.lpszClassName = _className;
	wcx.lpszMenuName = NULL;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style = NULL;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hIconSm = wcx.hIcon;
	wcx.hInstance = _hInstance;
	wcx.lpfnWndProc = windowProc;
	int ret = RegisterClassEx(&wcx);
	assert(ret != 0 && "RegisterClassEx() failed");
	_isRegistered = true;

	_hWnd = CreateWindowEx(
		NULL,
		_className, 
		_title, 
		WS_OVERLAPPEDWINDOW, 
		_x, 
		_y, 
		_width, 
		_height, 
		NULL, 
		NULL, 
		wcx.hInstance, 
		NULL);
	assert(_hWnd && "CreateWindow() failed");

	_isCreated = true;
	show();
	refresh();
}

LRESULT CALLBACK Window::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE:
			if (OnCreate) OnCreate();
			return 0;
		case WM_SIZE:
			if (OnResize) OnResize(wParam, LOWORD(lParam), HIWORD(lParam));
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

void Window::show() {
	ShowWindow(_hWnd, SW_SHOWDEFAULT);
}

void Window::refresh() {
	UpdateWindow(_hWnd);
}

void Window::setTitle(wchar_t *title) {
	SetWindowText(_hWnd, title);
}

void (*Window::OnCreate)() = NULL;
void (*Window::OnResize)(unsigned int state, int width, int height) = NULL;
