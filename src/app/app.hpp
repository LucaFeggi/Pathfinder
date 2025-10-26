#ifndef APP_H
#define APP_H

#include "input.hpp"
#include "window.hpp"

#include "../simulation/a_star.hpp"
#include "../renderer/renderer.hpp"

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