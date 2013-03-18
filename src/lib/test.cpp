#include "test.hpp"
::std::vector<TestFactory*> factories;
void Testing::addFactory(TestFactory * factory){
    factories.push_back(factory);
}
size_t Testing::getFactoryCount(){
    return factories.size();
}
const char * Testing::getFactoryName(size_t index){
    return factories[index]->name();
}
void Testing::instance(World::Earth * earth, size_t count, size_t factory_index){
	if(factory_index > Testing::getFactoryCount()-1){
		throw "Out of range";
	}
	TestFactory * f = factories[factory_index];
	float width = f->width();
	for(size_t i = 0; i < count; ++i){
		instances.push_back(f->instance(earth, width*(float)i,0));
	}
}
void Testing::destroy(){
	while(!instances.empty()){
		delete instances.back();
		instances.pop_back();
	}
}

