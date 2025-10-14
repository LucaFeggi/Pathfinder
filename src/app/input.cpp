#include "input.hpp"

#include "../config.hpp"

void Input::poll(const SDL_Event &event, bool *commands){
    switch(event.type){
        case SDL_QUIT:
            commands[Commands::QUIT] = true;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) commands[Commands::QUIT] = true;
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) commands[Commands::RENDER] = true;
            break;
        default:
            break;
    }       
}