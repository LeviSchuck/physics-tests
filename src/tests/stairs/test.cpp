#include "test.hpp"
#include "lib/testenvironment.hpp"
#include "lib/object.hpp"

const double width = 4.5;
const double depth = 1.5;
const double height = 0.5;
const int many = 4;
const int staircount = 50;
class StairTestInstance : public TestInstance {
    
	std::vector<World::Object*> obs;
public:
    
    inline float randf(){return rand()/((float)RAND_MAX);}
	StairTestInstance(TestEnvironment * env, float x, float y){
        
        const double mult = width+2.0;
       
        for(float j = 0; j < many; j+=1){
            for(int i = staircount; i; i--){
                obs.push_back(new World::Object(env));
                obs.back()->init(E_BOX, Vec4(
                    depth,height,width,0),MassProperties(0,0),
                    Transform(Vec3(x+i*depth,i*height,y+j*width*mult),Vec4(0,0,0,1)));
            }
            obs.push_back(new World::Object(env));
            obs.back()->init(E_SPHERE, Vec4(1,0,0,0),MassProperties(40,0),Transform(Vec3(
                x+staircount*depth,(height+1.0)*staircount,y+j*width*mult
                ),Vec4(0,0,0,1)));
            obs.back()->setVelocity(Vec3(-4-randf()*j,-40-randf()*j*8.0,0));
            obs.back()->setAngularVelocity(Vec3(randf()*j,randf()*j,randf()*j));
            obs.push_back(new World::Object(env));
            obs.back()->init(E_BOX, Vec4(1,5,width*3,0),MassProperties(200,0),Transform(Vec3(x-10,5,y+j*width*mult),Vec4(0,0,0,1)));
        }
        
       
	}
    ~StairTestInstance(){
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

TestInstance * StairTestFactory::instance(TestEnvironment* env, float x, float y){
    return new StairTestInstance(env,x,y);
}
StairTestFactory::StairTestFactory(){
    TestFactory::addFactory(this);
}
float StairTestFactory::length(){
    return many * ::width*4.5;
}
float StairTestFactory::width(){
    return staircount * depth;
}
StairTestFactory _stf;//statically initialize and add this test.


