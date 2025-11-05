#include "app/app.hpp"

#include <iostream>
#include <exception>

int main(int argc, char **argv){
	App app;
	if(app.init()){
		app.run();
		app.free();
	}
	return 0;
}