#include "lib/testenvironment.hpp"
#include "test.hpp"

::std::vector<TestFactory*> testfactories;
void TestFactory::addFactory(TestFactory * factory){
    testfactories.push_back(factory);
}
size_t TestFactory::getFactoryCount(){
    return testfactories.size();
}
const char * TestFactory::getFactoryName(size_t index){
    return testfactories[index]->name();
}
void Testing::instantiate(TestEnvironment * env, size_t count, size_t factory_index){
	if(factory_index > TestFactory::getFactoryCount()-1){
		throw "Out of range";
	}
	TestFactory * f = testfactories[factory_index];
	float width = f->width();
	for(size_t i = 0; i < count; ++i){
		instances.push_back(f->instance(env, width*(float)i,0));
	}
}
void Testing::destroy(){
	while(!instances.empty()){
		delete instances.back();
		instances.pop_back();
	}
}

