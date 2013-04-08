#include <iostream>
#include <sys/time.h>

#include "lib/graphics.hpp"
#include "lib/world.hpp"
#include "lib/test.hpp"
#include "lib/testenvironment.hpp"


int main(int argc, char* argv[]){
	const size_t index = 3;
	const size_t test_index = 2;
	Graphical::Engine * graphics = new Graphical::Engine;
	graphics->setup();
	graphics->manager();
	World::Earth * bullet = World::EarthFactory::getEarthFactory(2)->instantiate();
	TestEnvironment te1(graphics,bullet);
    World::Earth * physx = World::EarthFactory::getEarthFactory(3)->instantiate();
	TestEnvironment te2(graphics,physx);
    World::Earth * ode = World::EarthFactory::getEarthFactory(4)->instantiate();
	TestEnvironment te3(graphics,ode);
	Testing t1,t2,t3;
	//std::cout << "Engine: " << World::EarthFactory::getEarthFactory(index)->getName() << std::endl;
	//t1.instantiate(&te1,5,test_index);
    //t2.instantiate(&te2,5,test_index);
    t3.instantiate(&te3,5,test_index);

	double elapsedTime = 0;
	while(!graphics->exitRequested()){
		timeval _t1, _t2;
		gettimeofday(&_t1, NULL);
		graphics->render();
		bullet->tick(elapsedTime/1000.f);
        physx->tick(elapsedTime/1000.f);
        ode->tick(elapsedTime/1000.f);
		t1.update();
        t2.update();
        t3.update();
		gettimeofday(&_t2, NULL);
		elapsedTime = (_t2.tv_sec - _t1.tv_sec) * 1000.0 + (_t2.tv_usec - _t1.tv_usec) / 1000.0;   // us to ms
	}
	graphics->closeup();
	delete graphics;
	delete physx;
    delete bullet;
	return 0;
}
