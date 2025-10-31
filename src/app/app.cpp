#include "app.hpp"

#include "../config.hpp"

#include <string>
#include <stdexcept>

#include "SDL.h"

App::App(){
	if(SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error(std::string("Failed to initialize SDL: ") + SDL_GetError());
	window = std::make_unique<Window>();
	renderer = std::make_unique<Renderer>(*window);
	a_star.run();
	window->show();
	renderer->render(a_star);
}

App::~App(){
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
				renderer->render(a_star);
				input.set_command_inactive(Commands::RENDER);
			}
		}
	}
}
