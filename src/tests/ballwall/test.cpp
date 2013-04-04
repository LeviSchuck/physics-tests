#include "test.hpp"
#include "lib/testenvironment.hpp"
#include "lib/object.hpp"


class BallWallTestInstance : public TestInstance {
	std::vector<World::Object*> obs;
public:
    
	BallWallTestInstance(TestEnvironment * env, float x, float y){
        double aoffset = -1.0*20.0*50.0/2.0;
        for(int i = 0; i < 50; i++){
            Vec4 color(rand()/((float)RAND_MAX), rand()/((float)RAND_MAX), rand()/((float)RAND_MAX),1);
            double offset = i*20.0;
            for(int j = 0; j < 3; j++){
                obs.push_back(new World::Object(env));
                obs.back()->init(E_BOX, Vec4(1,10,10,0),MassProperties(0,0),Transform(Vec3(x+10+j*50,10,y+offset+aoffset),Vec4(0,0,0,1)));
                obs.back()->setColor(color);
            }
            obs.push_back(new World::Object(env));
            obs.back()->init(E_SPHERE, Vec4(1,0,0,0),MassProperties(0.4,0),Transform(Vec3(x-40.0,15,y+offset+aoffset),Vec4(0,0,0,1)));
            obs.back()->setVelocity(Vec3(6*i,0,0));
            obs.back()->setColor(color);
        }
        
       
	}
    ~BallWallTestInstance(){
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

TestInstance * BallWallTestFactory::instance(TestEnvironment* env, float x, float y){
    return new BallWallTestInstance(env,x,y);
}
BallWallTestFactory::BallWallTestFactory(){
    TestFactory::addFactory(this);
}
BallWallTestFactory _bwtf;//statically initialize and add this test.


