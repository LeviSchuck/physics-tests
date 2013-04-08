#include <iostream>
#include <sys/time.h>

#include "lib/graphics.hpp"
#include "lib/world.hpp"
#include "lib/test.hpp"
#include "lib/testenvironment.hpp"


int main(int argc, char* argv[]){
	const size_t index = 3;
	const size_t test_index = 0;
	Graphical::Engine * graphics = new Graphical::Engine;
	graphics->setup();
	graphics->manager();
	World::Earth * earth = World::EarthFactory::getEarthFactory(index)->instantiate();
	TestEnvironment te(graphics,earth);
	Testing t;
	std::cout << "Engine: " << World::EarthFactory::getEarthFactory(index)->getName() << std::endl;
	t.instantiate(&te,5,test_index);


	double elapsedTime = 0;
	while(!graphics->exitRequested()){
		timeval t1, t2;
		gettimeofday(&t1, NULL);
		graphics->render();
		earth->tick(elapsedTime/1000.f);
		t.update();
		gettimeofday(&t2, NULL);
		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0 + (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
	}
	graphics->closeup();
	delete graphics;
	delete earth;
	return 0;
}
