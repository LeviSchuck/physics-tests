#pragma once

#include <vector>

#include "world.hpp"

class Testing;
class TestInstance;
class TestFactory;
class TestFactory {
public:
	virtual TestInstance * instance(World::Earth*, float x, float y) = 0;
	virtual float width() = 0;
	virtual float length() = 0;
	virtual const char * name() = 0;
};
class Testing {
	::std::vector<TestInstance*> instances;
public:
	void instance(World::Earth*, size_t count, size_t factory_index);
	void destroy();
	static void addFactory(TestFactory * factory);
	static size_t getFactoryCount();
	static const char * getFactoryName(size_t index);

};

class TestInstance {
public:
	virtual float difference(const TestInstance & other) {
		return 1;
	}
	virtual ~TestInstance() {};
};