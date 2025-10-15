#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

namespace Input{
    enum Commands{
        QUIT = 0,
        RENDER,
        TOTAL
    };
	void poll(const SDL_Event &event, bool *commands);
}

#endif // !INPUT_H
