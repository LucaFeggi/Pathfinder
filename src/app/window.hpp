#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "SDL.h"

class Window{
public:
	bool init();
	void free();
	void show() const;
	SDL_Window *get_ptr() const;
private:
	SDL_Window *ptr = nullptr;
};

#endif	// !WINDOW_HPP
