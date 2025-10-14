#include "window.hpp"

Window::Window(){
    SDL_DisplayMode dm;
    int w, h;
    if(SDL_GetCurrentDisplayMode(0, &dm) != 0){
        SDL_Log("Could not get display mode: %s", SDL_GetError());
        w = 1280;
        h = 720;
    }
    else {
        w = (int)(dm.w * 0.667f);
        h = (int)(dm.h * 0.667f);
    }

    ptr = SDL_CreateWindow(
        "Pathfinder",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_HIDDEN
    );
    if(ptr == nullptr){
        SDL_Log("Error: Could not create window: %s", SDL_GetError());
        return;
    }

    SDL_SetWindowMinimumSize(ptr, w / 5, h / 5);

    SDL_Surface *icon = SDL_LoadBMP("assets/icon/icon.bmp");
    if(icon != nullptr){
        SDL_SetWindowIcon(ptr, icon);
        SDL_FreeSurface(icon);
    }
    else{
        SDL_Log("Warning: Could not load window icon 'res/bpm/icon.bmp': %s", SDL_GetError());
    }
}

Window::~Window(){
    if(ptr != nullptr){
        SDL_DestroyWindow(ptr);
        ptr = nullptr;
    }
}

SDL_Window *Window::get_ptr() const{
    return ptr;
}

void Window::show() const{
    SDL_ShowWindow(ptr);
}