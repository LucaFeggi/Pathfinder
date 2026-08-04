#ifndef WINDOW_H
#define WINDOW_H

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

#endif	// !WINDOW_H
