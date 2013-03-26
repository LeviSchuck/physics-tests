#include "object.hpp"
#include "pentity.hpp"
#include "gentity.hpp"
#include "math.hpp"
namespace World {
	class ObjectContents {
	public:
		Entity_Types _type;
		Graphical::Entity * _g;
		Physical::Entity * _p;
		World::Earth * _earth;
		Graphical::Engine * _engine;
		bool _static;
		ObjectContents(World::Earth * earth, Graphical::Engine * engine):
		_earth(earth), _engine(engine), _static(false) {

		}
		~ObjectContents(){
			if(_p) delete _p;
			if(_g) delete _g;
		}
	};
	Object::Object(World::Earth * earth, Graphical::Engine * engine){
		_contents = new ObjectContents(earth,engine);
	}
	void Object::init(
		const Entity_Types type,
		const char * mesh,
		const MassProperties mass,
		const Transform t){
		_contents->_type = type;
		_contents->_g = new Graphical::Entity(_contents->_engine, type, mesh);
		_contents->_g->setOrientation(t.second);
		_contents->_g->setPosition(t.first);
		_contents->_p = new Physical::Entity(type, _contents->_static, _contents->_earth);
		_contents->_p->init(_contents->_g->getMesh(), mass, t);
	}
	void Object::init(
		const Entity_Types type,
		const Vec4 data,
		const MassProperties mass,
		const Transform t){
		_contents->_type = type;
		_contents->_g = new Graphical::Entity(_contents->_engine, type, Math::Vec4ToVec3(data));
		_contents->_g->setOrientation(t.second);
		_contents->_g->setPosition(t.first);
		_contents->_p = new Physical::Entity(type, _contents->_static, _contents->_earth);
		_contents->_p->init(Math::Vec4ToVec3(data), mass, t, Math::VecLast(data));

	}
	void Object::init(
		const Entity_Types type,
		const ShapeList & list,
		const MassProperties mass,
        const Transform t){
		//TODO
	}
	Object::~Object(){
		delete _contents;
	}
	
	const Vec3 Object::getPosition() const{
		if(_contents->_p){
			return _contents->_p->getPosition();
		}
		if(_contents->_g){
			return _contents->_g->getPosition();
		}
		Vec3 v;
		return v;
	}
	const Vec4 Object::getQuatOrientation() const{
		if(_contents->_p){
			return _contents->_p->getQuatOrientation();
		}
		if(_contents->_g){
			return _contents->_g->getQuatOrientation();
		}
		Vec4 v;
		return v;
	}
	const Vec3 Object::getEulerOrientation() const{
		if(_contents->_p){
			return _contents->_p->getEulerOrientation();
		}
		if(_contents->_g){
			return _contents->_g->getEulerOrientation();
		}
		Vec3 v;
		return v;
	}
	void Object::setPosition(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setPosition(vec);
		}
		if(_contents->_g){
			_contents->_g->setPosition(vec);
		}
	}
	void Object::setOrientation(const Vec4 vec){
		if(_contents->_p){
			_contents->_p->setOrientation(vec);
		}
		if(_contents->_g){
			_contents->_g->setOrientation(vec);
		}
	}
	void Object::setOrientation(const Vec3 vec){
		if(_contents->_p){
			_contents->_p->setOrientation(vec);
		}
		if(_contents->_g){
			_contents->_g->setOrientation(vec);
		}
	}
	void Object::setStatic(bool s){
		_contents->_static = s;
	}

	void Object::hideGraphics(){
		if(_contents->_g){
			_contents->_g->hide();
		}
	}
	void Object::showGraphics(){
		if(_contents->_g){
			_contents->_g->show();
		}
	}

	void Object::color(const Vec4 color){
		if(_contents->_g){
			_contents->_g->color(color);
		}
	}
	const Entity_Types Object::type() const {
		return _contents->_type;
	}

	const Mesh & Object::getMesh() const{
		static Mesh m;
		return m;
	}
};