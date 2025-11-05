#ifndef RENDERER_H
#define RENDERER_H

#include "../app/window.hpp"
#include "../simulation/a_star.hpp"

#include "SDL.h"

class Renderer{
public:
    bool init(const Window &window);
    void free();
    void render(const A_Star &a_star);
private:
    SDL_Renderer *ptr;
    SDL_Window *win_ptr;    // pointing to window->ptr and freed by Window class
};

#endif // !RENDERER_H
