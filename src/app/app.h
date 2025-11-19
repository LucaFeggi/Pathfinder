#ifndef APP_H
#define APP_H

#include "input.h"
#include "window.h"

#include "../simulation/a_star.h"
#include "../renderer/renderer.h"

class App{
public:
	bool init();
	void free();
	void run();
private:
	A_Star a_star;
	Input input;
	Window window;
	Renderer renderer;
};

#endif // !APP_H