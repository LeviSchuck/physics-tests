#pragma once
#include "lib/test.hpp"

class StairTestFactory : public TestFactory {
public:
	virtual TestInstance * instance(TestEnvironment*, float x, float y);
	virtual float width();
	virtual float length();
	virtual const char * name() {return "Basic Test";}
    StairTestFactory();
};