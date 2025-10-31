#ifndef RENDERER_H
#define RENDERER_H

#include "../app/window.hpp"
#include "../simulation/a_star.hpp"

#include "SDL.h"

class Renderer{
public:
    Renderer(const Window &window);
    ~Renderer();
    void render(const A_Star &a_star);
private:
    SDL_Renderer *ptr;
    const Window &window;
};

#endif // !RENDERER_H
