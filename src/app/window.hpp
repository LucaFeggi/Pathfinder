#ifndef WINDOW_H
#define WINDOW_H

#include "SDL.h"

class Window{
public:
	Window();
	~Window();
	void show() const;
	SDL_Window *get_ptr() const;
private:
	SDL_Window *ptr;
};

#endif	// !WINDOW_H
