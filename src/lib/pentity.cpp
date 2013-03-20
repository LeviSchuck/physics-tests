#include <utility>
#include "pentity.hpp"
#include "math.hpp"

namespace Physical {
	Entity::Entity(const Entity_Types type, const bool s, World::Earth * world){
		_world = world;
		_type = type;
		_body_index = 0;
		_static = s;
	}
	Entity::~Entity(){
		_world->removeBody(_body_index);
		for_each(_shape_index.begin(),_shape_index.end(),[this](size_t shape){
			_world->removeShape(shape);
		});
	}
	void Entity::init(const Mesh & m, const MassProperties mass, const Transform t){
		size_t shape = createShape(_type, m);
		_shape_index.push_back(shape);
		//create body
		makeBody(t, mass);
	}
	void Entity::init(const Vec3 data, const MassProperties mass, const Transform t){
		size_t shape = createShape(_type, data);
		_shape_index.push_back(shape);
		//create body
		makeBody(t, mass);
	}
	void Entity::init(const ShapeList & list, const MassProperties mass, const Transform t){
		std::vector< ::std::pair<size_t, Transform> > shapes;
		size_t compound;
		//Create the shapes
		for_each(list.begin(), list.end(), [&](ShapeList::value_type shape){
			if(std::tr1::get<0>(shape)){
				//Mesh!
				size_t s = createShape(
					std::tr1::get<1>(shape).second.first,
					std::tr1::get<1>(shape).second.second
					);
				Transform t = std::tr1::get<2>(shape);
				::std::pair<size_t, Transform> p(s,t);
				shapes.push_back(p);
			}else{
				size_t s = createShape(
					std::tr1::get<1>(shape).first.first,
					std::tr1::get<1>(shape).first.second
					);
				Transform t = std::tr1::get<2>(shape);
				::std::pair<size_t, Transform> p(s,t);
				shapes.push_back(p);
			}
		});
		//Got a list of shapes, make the compound shape
		compound = _world->compoundShapes(shapes);
		//Put it back on with the compound object first
		_shape_index.push_back(compound);
		for_each(shapes.begin(),shapes.end(),[&](decltype(shapes)::value_type s){
			_shape_index.push_back(s.first);
		});
		//create body
		makeBody(t, mass);
	}
	void Entity::makeBody(const Transform t, const MassProperties mass){
		size_t shape = _shape_index.front();
		if(_static){
			_body_index = _world->makeStaticBody(shape, t);
		}else{
			_body_index = _world->makeRigidBody(shape, mass, t);
		}
	}
	size_t Entity::createShape(const Entity_Types type, const Mesh & m){
		return 0;
	}
	size_t Entity::createShape(const Entity_Types type, const Vec3 data){
		return 0;
	}

	const Vec3 Entity::getPosition() const{
		Transform t = _world->getTransformation(_body_index);
		return t.first;
	}
	const Vec4 Entity::getQuatOrientation() const{
		Transform t = _world->getTransformation(_body_index);
		return t.second;
	}
	const Vec3 Entity::getEulerOrientation() const{
		Transform t = _world->getTransformation(_body_index);
		return Math::QuaternionToEuler(t.second);
	}
	const Transform Entity::getTransform() const {
		Transform t;
		return _world->getTransformation(_body_index);
	}
	void Entity::setPosition(const Vec3 vec){
		Transform t = _world->getTransformation(_body_index);
		t.first = vec;
		_world->transformBody(_body_index,t);
	}
	void Entity::setOrientation(const Vec4 vec){
		Transform t = _world->getTransformation(_body_index);
		t.second = vec;
		_world->transformBody(_body_index,t);
	}
	void Entity::setOrientation(const Vec3 vec){
		setOrientation(Math::EulerToQuaternion(vec));
	}
};