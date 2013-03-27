#include "graphics.hpp"
#include "world.hpp"

class TestEnvironment {
	Graphical::Engine * _g;
	World::Earth * _p;
public:
	Graphical::Engine * getGraphics(){return _g;}
	World::Earth * getPhysics(){return _p;}
	TestEnvironment(Graphical::Engine *g, World::Earth *p)
	:_g(g),_p(p){}
};