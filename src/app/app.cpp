#include "app.hpp"

#include "input.hpp"

#include "../config.hpp"

#include "SDL.h"

App::App(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
		return;
	}
	a_star.run();
	window = std::make_unique<Window>();
	renderer = std::make_unique<Renderer>(*window);
	window->show();
	renderer->render(*window, a_star);
}

App::~App(){
	SDL_Quit();
}

void App::run(){
	SDL_Event event;
	bool commands[Input::Commands::TOTAL] = { false };
	while(true){
		if(SDL_WaitEvent(&event)){
			Input::poll(event, commands);
			if(commands[Input::Commands::QUIT]){
				return;
			}
			if(commands[Input::Commands::RENDER]){
				renderer->render(*window, a_star);
				commands[Input::Commands::RENDER] = false;
			}
		}
	}
}