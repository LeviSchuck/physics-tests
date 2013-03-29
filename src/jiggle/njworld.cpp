#include "njworld.hpp"

void JiggleWorld::tick(float delta){
	auto bodies = getBodies();
	for_each(bodies.begin(),bodies.end(),[&](size_t index){
		Transform t = getTransformation(index);
		Vec3 a = t.first;
		Vec3 b = Vec3(
			std::tr1::get<0>(a)+((rand() % 100)-50)/100.0f*delta,
			std::tr1::get<1>(a)+((rand() % 100)-50)/100.0f*delta,
			std::tr1::get<2>(a)+((rand() % 100)-50)/100.0f*delta
			);
		t.first = b;
		transformBody(index,t);
	});
	
}
class JiggleWorldFactory : public World::EarthFactory {
public:
    virtual World::Earth * instantiate() {
        return new JiggleWorld();
    }
    JiggleWorldFactory(){
        World::EarthFactory::addEarth(this);
    }
    virtual const char * getName(){
    	return "Jiggle World";
    }
};
static JiggleWorldFactory jwf;