#include "window.hpp"

#include <iostream>
#include <string>
#include <stdexcept>

Window::Window(){
    SDL_DisplayMode dm;
    int w, h;
    if(SDL_GetCurrentDisplayMode(0, &dm) != 0){
        std::clog << "Warning! Could not get display mode: " << SDL_GetError() << "\n";
        w = 1280; h = 720;
    }
    else {
        w = static_cast<int>(dm.w * 0.667f);
        h = static_cast<int>(dm.h * 0.667f);
    }

    ptr = SDL_CreateWindow(
        "Pathfinder",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_HIDDEN
    );
    if(ptr == nullptr) throw std::runtime_error(std::string("Failed to create window: ") + SDL_GetError());

    SDL_SetWindowMinimumSize(ptr, w / 5, h / 5);

    SDL_Surface *icon = SDL_LoadBMP("assets/icon/icon.bmp");
    if(icon != nullptr){
        SDL_SetWindowIcon(ptr, icon);
        SDL_FreeSurface(icon);
    }
    else{
        std::clog << "Warning! Could not load window icon 'assets/icon/icon.bmp': " << SDL_GetError() << "\n";
    }
}


Window::~Window(){
    SDL_DestroyWindow(ptr);
}

SDL_Window *Window::get_ptr() const{
    return ptr;
}

void Window::show() const{
    SDL_ShowWindow(ptr);
}