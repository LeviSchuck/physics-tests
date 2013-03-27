#pragma once

#include <vector>

#include "world.hpp"

class Testing;
class TestInstance;
class TestFactory;
class TestEnvironment;
class TestFactory {
public:
	virtual TestInstance * instance(TestEnvironment*, float x, float y) = 0;
	virtual float width() = 0;
	virtual float length() = 0;
	virtual const char * name() = 0;
	static void addFactory(TestFactory * factory);
	static size_t getFactoryCount();
	static const char * getFactoryName(size_t index);
};
class Testing {
	::std::vector<TestInstance*> instances;
public:
	void instantiate(TestEnvironment*, size_t count, size_t factory_index);
	void destroy();
	void update();

};

class TestInstance {
protected:
	size_t id;
public:
	virtual void update() = 0;
	virtual float difference(const TestInstance & other) {
		return 0;
	}
	virtual ~TestInstance() {};
};