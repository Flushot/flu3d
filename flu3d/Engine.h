#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
using namespace std;

#include "SceneManager.h"
#include "Window.h"

class Engine {
private:
	static Engine *_instance;
	Window *_window;
	SceneManager *_scene;
	HDC _hDC;
	HGLRC _hRC;
	float _zoom;

protected:
	Engine();
	//Engine(const Engine &);
	//Engine &operator= (const Engine &);

	void project();
	void render();
	void loadScene();

public:
	~Engine();
	static void resize();

	static Engine *getInstance();

	void start();
	void doEvents();
};
