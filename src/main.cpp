#include "app/app.hpp"

#include <iostream>
#include <exception>

int main(int argc, char **argv){
	try{
		App app;
		app.run();
	}catch(const std::exception &e){
		std::cerr << "Fatal error! " << e.what() << "\n";
		return -1;
	}
	return 0;
}