#include <irrlicht/irrlicht.h>
#include "gentity.hpp"
#include "graphics.hpp"

namespace Graphical {
	inline ::irr::scene::ISceneManager * asM(void * m){
		return (::irr::scene::ISceneManager*)m;
	}
	class EntityInternals {
	public:
		::irr::scene::ISceneNode * node;
		Engine * engine;
		::irr::scene::IAnimatedMesh * mesh;
		EntityInternals(){
			mesh = NULL;
			engine = NULL;
			node = NULL;
		}
	};
	Entity::Entity(class Engine * engine, const Entity_Types type, const Vec3 & data){
		_internals = new EntityInternals();
		_internals->engine = engine;
		switch(type){
			case E_BAR:
			{
				_internals->node = asM(engine->manager())->addCubeSceneNode(
					1,NULL,-1,irr::core::vector3df(0, 0, 0),irr::core::vector3df(0, 0, 0),
					irr::core::vector3df(
						std::tr1::get<0>(data),
						std::tr1::get<1>(data),
						std::tr1::get<2>(data))
					);
			}
			break;
			case E_SPHERE:
			{
				_internals->node = asM(engine->manager())->addSphereSceneNode(
					std::tr1::get<0>(data)
					);

			}
			break;
			case E_CAPSULE:
			{
				//Bit of a hackery since they don't have one directly..
				_internals->node = asM(engine->manager())->addEmptySceneNode();
				asM(engine->manager())->addMeshSceneNode(
					asM(engine->manager())->addArrowMesh("arrow",
					irr::video::SColor(255, 255, 0, 0), irr::video::SColor(255, 255, 0, 0),
					4,8,
					std::tr1::get<1>(data)+0.001f,	// 0. arrow's total length
					std::tr1::get<1>(data),			// 1. arrow's cylinder length
					0.001f,               			// 2. arrow cone's height 
					std::tr1::get<0>(data)*2.0f		// 3. arrow's diameter
				), _internals->node);
				asM(engine->manager())->addSphereSceneNode(
					16,
					std::tr1::get<0>(data),
					_internals->node,
					-1,
					irr::core::vector3df(0,std::tr1::get<1>(data)/2.0f,0)
					);
				asM(engine->manager())->addSphereSceneNode(
					16,
					std::tr1::get<0>(data),
					_internals->node,
					-1,
					irr::core::vector3df(0,-std::tr1::get<1>(data)/2.0f,0)
					);

			}
			break;
			default://includes E_MESH
				throw "Invalid Entity Type!";
		}
		_internals->node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
	Entity::Entity(class Engine * engine, const Entity_Types type, const char * mesh){
		_internals = new EntityInternals();
		_internals->engine = engine;
		_internals->mesh = asM(engine->manager())->getMesh(mesh);
		if(!_internals->mesh) throw "There must have been an error loading!";
		_internals->node = asM(engine->manager())->addMeshSceneNode(_internals->mesh);

	}
	Entity::~Entity(){
		delete _internals;
	}
	const Vec3 Entity::getPosition() const{
		Vec3 v(
			_internals->node->getPosition().X,
			_internals->node->getPosition().Y,
			_internals->node->getPosition().Z
			);
		return v;
	}
	void Entity::setPosition(const Vec3 & vec){
		_internals->node->setPosition(irr::core::vector3df(
			std::tr1::get<0>(vec),
			std::tr1::get<1>(vec),
			std::tr1::get<2>(vec)
			));
	}
	void Entity::hide(){
		_internals->node->setVisible(false);
	}
	void Entity::show(){
		_internals->node->setVisible(true);
	}
	void Entity::color(const Vec4 & color){
		irr::video::SColor color2(
			std::tr1::get<0>(color)*255,
			std::tr1::get<1>(color)*255,
			std::tr1::get<2>(color)*255,
			std::tr1::get<3>(color)*255
			);
		
		for(size_t i = 0; i < _internals->node->getMaterialCount(); ++i){
			_internals->node->getMaterial(i).AmbientColor = color2; 
		}
	}
	const Vec4 Entity::getQuatOrientation() const{
		irr::core::quaternion q(
			_internals->node->getRotation().X,
			_internals->node->getRotation().Y,
			_internals->node->getRotation().Z
			);
		Vec4 v(q.X,q.Y,q.Z,q.W);
		return v;
	}
	const Vec3 Entity::getEulerOrientation() const{
		Vec3 v(
			_internals->node->getRotation().X,
			_internals->node->getRotation().Y,
			_internals->node->getRotation().Z
			);
		return v;
	}
	void Entity::setOrientation(const Vec4 & vec){
		irr::core::vector3df rot;
		irr::core::quaternion quat(
			std::tr1::get<0>(vec),
			std::tr1::get<1>(vec),
			std::tr1::get<2>(vec),
			std::tr1::get<3>(vec)
			);
		quat.toEuler(rot);
		_internals->node->setRotation(rot);
	}
	void Entity::setOrientation(const Vec3 & vec){
		_internals->node->setRotation(irr::core::vector3df(
			std::tr1::get<0>(vec),
			std::tr1::get<1>(vec),
			std::tr1::get<2>(vec)
			));
	}
	const Mesh Entity::getMesh() const{
		Mesh m;
		if(_internals->mesh){
			size_t total_indicies = 0, total_vertices = 0;
			for(size_t i = 0; i < _internals->mesh->getMeshBufferCount(); ++i){
				total_indicies += _internals->mesh->getMeshBuffer(i)->getIndexCount();
				total_vertices += _internals->mesh->getMeshBuffer(i)->getVertexCount();
			}
			m.second.reserve(total_indicies);
			m.first.reserve(total_vertices);
			for(size_t i = 0; i < _internals->mesh->getMeshBufferCount(); ++i){
				auto buffer = _internals->mesh->getMeshBuffer(i);
				auto ind = buffer->getIndices();
				for(size_t j = 0; j < buffer->getIndexCount(); ++j){
					m.second.push_back(ind[j]);
				}
				auto vers = buffer->getVertices();
				for(size_t j = 0; j < buffer->getIndexCount(); ++j){
					irr::video::S3DVertex v = *((irr::video::S3DVertex*)(vers)+j);
					auto pos = v.Pos;
					m.first.push_back(Vec3(
						pos.X,
						pos.Y,
						pos.Z
						));

				}
			}
		}

		return m;
	}
}