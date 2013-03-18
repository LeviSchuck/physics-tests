#include "pentity.hpp"
namespace Physical {
	Entity::Entity(const Entity_Types type, const Vec3 & data, const MassProperties & mass, World::Earth *){

	}
	Entity::Entity(const Entity_Types type, const Mesh & mesh, const MassProperties & mass, World::Earth *){

	}
	Entity::~Entity(){

	}
	const Vec3 Entity::getPosition() const{
		Vec3 v;
		return v;
	}
	void Entity::setPosition(const Vec3 & vec){

	}
	void Entity::hide(){

	}
	void Entity::show(){

	}
	const Vec4 Entity::getQuatOrientation() const{
		Vec4 v;
		return v;
	}
	const Vec3 Entity::getEulerOrientation() const{
		Vec3 v;
		return v;
	}
	void Entity::setOrientation(const Vec4 & vec){

	}
	void Entity::setOrientation(const Vec3 & vec){

	}
};