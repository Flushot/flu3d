#pragma once

#include <windows.h>
#include <string>

class Window {
private:
	wchar_t *_title;
	wchar_t _className[16];
	int _x, _y;
	int _width, _height;
	HWND _hWnd;
	HINSTANCE _hInstance;
	bool _isCreated;
	bool _isRegistered;

	void getRandomClassName(wchar_t *in, int len);
	void create();

protected:
	static LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	// Callbacks
	static void (*OnCreate)();
	static void (*OnResize)(unsigned int state, int width, int height);

	Window(wchar_t *title, int x, int y, int width, int height);
	~Window();

	void show();
	void refresh();

	int getX() const { return _x; }
	int getY() const { return _y; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	wchar_t *getTitle() const { return _title; }
	void setTitle(wchar_t *title);
	HWND getWindowHandle() const { return _hWnd; }
};
