#include "world.hpp"

namespace World {
	static std::vector<EarthFactory *> factories;
	void EarthFactory::addEarth(EarthFactory * factory){
		factories.push_back(factory);
	}
	size_t EarthFactory::getEarthCount(){
		return factories.size();
	}
	const char * EarthFactory::getEarthName(size_t index){
		return factories[index]->getName();
	}
	EarthFactory * EarthFactory::getEarthFactory(size_t index){
		return factories[index];
	}
};