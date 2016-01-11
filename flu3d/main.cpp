#include "main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Engine *engine = Engine::getInstance();
	engine->start();

	MSG msg;
	while (true) {
		if ( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		engine->doEvents();
	}

	delete engine;
	return msg.wParam;
}
