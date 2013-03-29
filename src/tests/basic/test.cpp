#include "test.hpp"
#include "lib/testenvironment.hpp"
#include "lib/object.hpp"


class BasicTestInstance : public TestInstance {
	std::vector<World::Object*> obs;
public:
    
	BasicTestInstance(TestEnvironment * env, float x, float y){
        for(int i = 0; i < 20; i++){
            obs.push_back(new World::Object(env));
            obs.back()->init(E_SPHERE, Vec4(1,0,0,0),MassProperties(4,0),Transform(Vec3(
                x+(rand() % 100)/10.f,i*2.1f,y+rand() % 10
                ),Vec4(0,0,0,1)));
            obs.push_back(new World::Object(env));
            obs.back()->init(E_BOX, Vec4((rand() % 100)/10.f,(rand() % 100)/10.f,(rand() % 100)/10.f,0),MassProperties((rand() % 100)/40.f,0),Transform(Vec3(
                x+(rand() % 100)/10.f,i*2.1f,y+rand() % 10
                ),Vec4(0,0,0,1)));
            obs.push_back(new World::Object(env));
            obs.back()->init(E_BOX, Vec4(
                1,1,1,0),MassProperties((rand() % 100)/40.f,0),
                Transform(Vec3(
                x+(rand() % 100)/10.f,i*2.1f,y+rand() % 10
                ),Vec4(0,0,0,1)));
        }
       
	}
    ~BasicTestInstance(){
    	for_each(obs.begin(),obs.end(),[](World::Object * obj){
    		delete obj;
    	});
    }
    virtual void update(){
        for_each(obs.begin(),obs.end(),[](World::Object * obj){
            obj->sync();
        });
    }
};

TestInstance * BasicTestFactory::instance(TestEnvironment* env, float x, float y){
    return new BasicTestInstance(env,x,y);
}
BasicTestFactory::BasicTestFactory(){
    TestFactory::addFactory(this);
}
BasicTestFactory _btf;//statically initialize and add this test.


