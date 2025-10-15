#ifndef SDL_INPUT_H
#define SDL_INPUT_H

#include "SDL.h"

namespace Input{
    enum Commands{
        QUIT = 0,
        RENDER,
        TOTAL
    };
	void poll(const SDL_Event &event, bool *commands);
}

#endif // !SDL_INPUT_H
