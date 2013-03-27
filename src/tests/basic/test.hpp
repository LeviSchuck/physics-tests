#pragma once
#include "lib/test.hpp"

class BasicTestFactory : public TestFactory {
public:
	virtual TestInstance * instance(TestEnvironment*, float x, float y);
	virtual float width(){return 10;}
	virtual float length(){return 10;}
	virtual const char * name() {return "Basic Test";}
    BasicTestFactory();
};