#ifndef APP_H
#define APP_H

#include "input.hpp"
#include "window.hpp"

#include "../simulation/a_star.hpp"
#include "../renderer/renderer.hpp"

#include <memory>

class App{
public:
	App();
	~App();
	void run();
private:
	A_Star a_star;
	Input input;
	std::unique_ptr<Window> window;
	std::unique_ptr<Renderer> renderer;
};

#endif // !APP_H
