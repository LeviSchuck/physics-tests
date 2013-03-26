#include "object.hpp"
namespace World {
	Object::Object(const Entity_Types type, const Vec3 & data, const MassProperties & mass, World::Earth *){
		
	}
	Object::Object(const Entity_Types type, const char * mesh, const MassProperties & mass, World::Earth *){

	}
	Object::~Object(){
		if(_g) delete _g;
		if(_p) delete _p;
	}
	
	const Vec3 Object::getPosition() const{
		Vec3 v;
		return v;
	}
	const Vec4 Object::getQuatOrientation() const{
		Vec4 v;
		return v;
	}
	const Vec3 Object::getEulerOrientation() const{
		Vec3 v;
		return v;
	}
	void Object::setPosition(const Vec3 & vec){

	}
	void Object::setOrientation(const Vec4 & vec){

	}
	void Object::setOrientation(const Vec3 & vec){

	}

	void Object::hideGraphics(){

	}
	void Object::showGraphics(){

	}
	void Object::hidePhysics(){

	}
	void Object::showPhysics(){

	}

	void Object::color(const Vec4 & color){

	}

	const Mesh & Object::getMesh() const{
		static Mesh m;
		return m;
	}
};