
#include <iostream>

#include "lib/graphics.hpp"
#include "lib/world.hpp"
#include "lib/test.hpp"
#include "lib/testenvironment.hpp"


int main(int argc, char* argv[]){
	Graphical::Engine * graphics = new Graphical::Engine;
	graphics->setup();
	std::cout << "Initiate0" << std::endl;
	graphics->manager();
	World::Earth * earth = World::EarthFactory::getEarthFactory(0)->instantiate();
	TestEnvironment te(graphics,earth);
	Testing t;
	std::cout << "Initiate1" << std::endl;
	t.instantiate(&te,1,0);



	while(!graphics->exitRequested()){
		graphics->render();
		t.update();
	}
	graphics->closeup();
	delete graphics;
	delete earth;
	return 0;
}
