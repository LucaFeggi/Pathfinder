#include "app.h"

#include "../config.h"

#include <iostream>

#include "SDL.h"

bool App::init(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << "\n";
		goto sdl_fail;
	}
	a_star.init();
	input.init();
	if(!window.init()) goto window_fail;
	if(!renderer.init(window)) goto renderer_fail;

	a_star.run();
	window.show();
	renderer.render(a_star);
	return true;

renderer_fail:
	window.free();
window_fail:
	SDL_Quit();
sdl_fail:
	return false;
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
				renderer.render(a_star);
				input.set_command_inactive(Commands::RENDER);
			}
		}
	}
}