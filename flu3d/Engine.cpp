#include <math.h>

#include "Engine.h"
#include "Exceptions.h"
#include "Log/Log.h"

Engine::Engine() {
	_window = NULL;
	_hDC = NULL;
	_hRC = NULL;
	_zoom = 1.0f;

	Log::addOutputter(new ODSLogOutputter());
	//Log::addOutputter(new ConsoleLogOutputter());
}
Engine::~Engine() {
	if (_window != NULL) {
		ReleaseDC(_window->getWindowHandle(), _hDC);
		if (_hRC != NULL) {
			wglMakeCurrent(NULL, NULL);
			wglDeleteContext(_hRC);
		}
		delete _window;
	}
	if (_scene != NULL)
		delete _scene;
}

Engine *Engine::_instance = NULL;
Engine *Engine::getInstance() {
	if (_instance == NULL)
		_instance = new Engine();
	return _instance;
};

void Engine::start() {
	Log::info("Starting engine...");
	try {
		// TODO: Resolution, position, pixel format, and some GL options can be pulled from a config file
		int width = 1024;
		int height = 768;
		_window = new Window(
			L"Flu3D",
			0/*GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2*/,
			0/*GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2*/,
			width,
			height );
		// TODO: Fix this ghettoness...
		//_window->OnCreate = Engine::resize;

		_hDC = GetDC(_window->getWindowHandle());
		if (! _hDC)
			throw new EngineInitializationException(
				"GetDC() failed", GetLastError());

		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE; // Unused; Backwards compatible.

		int pixelFormat = ChoosePixelFormat(_hDC, &pfd);
		if (! pixelFormat)
			throw new EngineInitializationException(
				"ChoosePixelFormat() failed", GetLastError());

		if (! SetPixelFormat(_hDC, pixelFormat, &pfd) )
			throw new EngineInitializationException(
				"SetPixelFormat() failed", GetLastError());

		_hRC = wglCreateContext(_hDC);
		if (! _hRC)
			throw new EngineInitializationException(
				"wglCreateContext() failed", GetLastError());

		if ( wglMakeCurrent(_hDC, _hRC) != TRUE )
			throw new EngineInitializationException(
				"wglMakeCurrent() failed", GetLastError());

		// Shading
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);

		// Depth buffer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		// Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Does GL get the hint?
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		// Set up VBO support
		/*
		g_fVBOSupported = IsExtensionSupported("GL_ARB_vertex_buffer_object");
		if(g_fVBOSupported) {
			// Get Pointers To The GL Functions
			glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
			glBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
			glBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
			glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
		}
		*/

		loadScene();
		resize();
	}
	catch (EngineException ex) {
		// Log the exception then bubble it up
		Log::error("Engine initialization failed: " + (string)ex.message);
		throw ex;
	}
}

void Engine::resize() {
	Log::debug("Engine::resize()");

	Engine *engine = Engine::getInstance();
	int width = engine->_window->getWidth();
	int height = engine->_window->getHeight();

	glViewport(0, 0, width, height);
	engine->project();
}

void Engine::project() {
	// This should only be called when the window is resized or zoom is changed.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	/*
	float fov = 45.0f * _zoom;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	int aspect = _window->getWidth() / _window->getHeight();
	float top = tanf(fov * 3.14159f / 360.0f) * nearPlane;
	float bottom = -top;
	float left = aspect * bottom;
	float right = aspect * top;
	glFrustum(left, right, bottom, top, nearPlane, farPlane);
	*/
	gluPerspective(45.0f * _zoom, _window->getWidth() / _window->getHeight(), 0.1f, 100.0f);
}

void Engine::loadScene() {
	_scene = new SceneManager();
	
	// universe (root)
	SceneNode *universe = new NullNode("universe");
	_scene->setRoot(universe);

	// planet1
	TriMeshNode *planet1 = new TriMeshNode(
		"planet1",
		Vector(0.0f, 0.0f, -8.0f),
		Vector(0.0f, 0.0f, 0.0f), // BUG: Rotation is fucked up
		0.06f
	);
	planet1->loadFile("assets/meshes/earth.ms3d", true);
	planet1->applyFixed(
		Material(
			0.5f, 0.5f, 0.5f, 1.0f, // ambient
			0.5f, 0.5f, 0.5f, 1.0f, // diffuse
			0.5f, 0.5f, 0.5f, 1.0f, // specular
			0.0f, 0.0f, 0.0f, 0.0f, // emissive
			0.5f), // shininess
		"assets/textures/earth.bmp"
	);
	universe->addChild(planet1);

	/*
	// planet2
	TriMeshNode *planet2 = new TriMeshNode(
		"planet2",
		Vector(-4.0f, -1.3f, -3.0f),
		Vector(0.0f, 0.0f, 0.0f),
		0.03f
	);
	planet2->loadFile("assets/meshes/earth.ms3d", true);
	planet2->applyFixed(
		Material(
			0.5f, 0.5f, 0.5f, 1.0f, // ambient
			0.5f, 0.5f, 0.5f, 1.0f, // diffuse
			0.5f, 0.5f, 0.5f, 1.0f, // specular
			0.0f, 0.0f, 0.0f, 0.0f, // emissive
			0.5f), // shininess
		"assets/textures/wood.bmp"
	);
	universe->addChild(planet2);
	*/

	// andromeda
	TriMeshNode *andromeda = new TriMeshNode(
		"andromeda",
		Vector(28.0f, 0.0f, 14.0f),
		Vector(0.0f, 0.0f, 90.0f),
		.53f
	);
	andromeda->loadFile("assets/meshes/andromeda.ms3d");
	planet1->addChild(andromeda); // orbits planet

	LightNode *light0 = static_cast<LightNode *>(
		universe->addChild(
			new LightNode(
				"light0",
				Vector(-2.0f, -1.0f, -3.0f)
			)
		)
	);

	SoundNode *engineSound = new SoundNode("engine_sound");
	engineSound->loadFile("assets/sounds/engine.wav");
	andromeda->addChild(engineSound); // attached to andromeda

	// light
	SceneNode *light1 = universe->addChild(
		new LightNode(
			"light1",
			Vector(0.0f, 0.0f, -3.5f)
		)
	);

	/*
	srand(GetTickCount());
	for (int i = 0; i < 1024; ++i) {
		// stars
		universe->addChild(
			new TestNode(
				"star",
				Vector(
					(float)rand() * 1.1f + 5.2f, 
					(float)rand() * 1.1f + 5.2f, 
					-(float)(rand() * 6.1f + 6.2f) ),
				Vector(0.0f, 0.0f, 0.0f),
				1.0f
			)
		);
	}
	*/

	_scene->bake();
}

void Engine::render() {
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Manipulate scene
	Vector rot, trans;

	SceneNode *universe = _scene->getRoot();

	SceneNode *planet1 = universe->findChild("planet1");
	rot = planet1->getRotation();
	rot.x = float( ((int)rot.x - 1) % 360 );
	planet1->setRotation(rot);

	SceneNode *andromeda = planet1->findChild("andromeda");
	rot = andromeda->getRotation();
	rot.x = float( ((int)rot.x + 1) % 360 );
	rot.y = float( ((int)rot.y + 1) % 360 );
	rot.z = float( ((int)rot.z + 1) % 360 );
	andromeda->setRotation(rot);

	LightNode *light1 = static_cast<LightNode *>( universe->findChild("light1") );
	rot = light1->getRotation();
	rot.x = float( ((int)rot.x + 1) % 360 );
	light1->setRotation(rot);

	// Render scene
	_scene->render();
	SwapBuffers(_hDC);
}

void Engine::doEvents() {
	render();
	Sleep(1);
}
