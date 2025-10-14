#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "SDL.h"

namespace Input{
    enum Commands{
        QUIT,    // Quit the application
        RENDER,  // Toggle rendering
        TOTAL    // Total number of commands
    };
	void poll(const SDL_Event &event, bool *commands);
}

#endif // !SDL_INPUT_H
