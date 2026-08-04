#include "app/app.hpp"

int main(int argc, char *argv[]){
	App app;
	if(app.init()){
		app.run();
		app.free();
	}
	return 0;
}
