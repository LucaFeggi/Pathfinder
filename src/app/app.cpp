#include "app.hpp"

#include "../config.hpp"

#include "SDL.h"

bool App::init(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("Error: failed to initialize SDL %s", SDL_GetError());
		return false;
	}
	if(!window.init()) return false;
	if(!renderer.init(window)) return false;

	a_star.run();
	window.show();
	renderer.render(window, a_star);
	return true;
}

void App::free(){
	renderer.free();
	window.free();
	SDL_Quit();
}

void App::run(){
	SDL_Event event;
	while(true){
		if(SDL_WaitEvent(&event)){
			input.poll(event);
			if(input.is_command_active(Commands::QUIT)){
				return;
			}
			if(input.is_command_active(Commands::RENDER)){
				renderer.render(window, a_star);
				input.set_command_inactive(Commands::RENDER);
			}
		}
	}
}