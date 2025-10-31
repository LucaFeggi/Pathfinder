#include "input.hpp"

#include "../config.hpp"

Input::Input() noexcept : command{ false } {}

void Input::poll(const SDL_Event &event){
    switch(event.type){
        case SDL_QUIT:
            command[Commands::QUIT] = true;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE) set_command_active(Commands::QUIT);
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) set_command_active(Commands::RENDER);
            break;
        default:
            break;
    }       
}

bool Input::is_command_active(const Commands comm) const{
    return command[comm];
}

void Input::set_command_active(const Commands comm){
    command[comm] = true;
}

void Input::set_command_inactive(const Commands comm){
    command[comm] = false;
}