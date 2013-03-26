#include <irrlicht/irrlicht.h>
#include "gentity.hpp"
#include "graphics.hpp"
#include "math.hpp"

namespace Graphical {
	inline ::irr::scene::ISceneManager * asM(void * m){
		return (::irr::scene::ISceneManager*)m;
	}
	class EntityInternals {
	public:
		::irr::scene::ISceneNode * node;
		Engine * engine;
		::std::vector< ::irr::scene::IAnimatedMesh * > meshes;
		EntityInternals(){
			engine = NULL;
			node = NULL;
		}
		~EntityInternals(){
			for_each(meshes.begin(), meshes.end(), [](::irr::scene::IAnimatedMesh * mesh){
				mesh->drop();
			});
		}
		::irr::scene::ISceneNode * makeNode(const Entity_Types type, const Vec3 data, ::irr::scene::ISceneNode * parent = NULL){
			::irr::scene::ISceneNode * node = NULL;
			switch(type){
				case E_BAR:
				{
					node = asM(engine->manager())->addCubeSceneNode(
						1,parent,-1,irr::core::vector3df(0, 0, 0),irr::core::vector3df(0, 0, 0),
						irr::core::vector3df(
							std::tr1::get<0>(data),
							std::tr1::get<1>(data),
							std::tr1::get<2>(data))
						);
				}
				break;
				case E_SPHERE:
				{
					node = asM(engine->manager())->addSphereSceneNode(
						std::tr1::get<0>(data),
						16,
						parent
						);

				}
				break;
				case E_CAPSULE:
				{
					//Bit of a hackery since they don't have one directly..
					node = asM(engine->manager())->addEmptySceneNode(parent);
					asM(engine->manager())->addMeshSceneNode(
						asM(engine->manager())->addArrowMesh("arrow",
						irr::video::SColor(255, 255, 0, 0), irr::video::SColor(255, 255, 0, 0),
						4,8,
						std::tr1::get<1>(data)+0.001f,	// 0. arrow's total length
						std::tr1::get<1>(data),			// 1. arrow's cylinder length
						0.001f,               			// 2. arrow cone's height 
						std::tr1::get<0>(data)*2.0f		// 3. arrow's diameter
					), node);
					asM(engine->manager())->addSphereSceneNode(
						16,
						std::tr1::get<0>(data),
						node,
						-1,
						irr::core::vector3df(0,std::tr1::get<1>(data)/2.0f,0)
						);
					asM(engine->manager())->addSphereSceneNode(
						16,
						std::tr1::get<0>(data),
						node,
						-1,
						irr::core::vector3df(0,-std::tr1::get<1>(data)/2.0f,0)
						);

				}
				break;
				case E_PLANE: break;
				default:
					throw "Invalid Entity Type!";
			}
			return node;
		}
		::irr::scene::ISceneNode * makeNode(const Entity_Types type, const char * mesh, ::irr::scene::ISceneNode * parent = NULL){
			::irr::scene::IAnimatedMesh * imesh = NULL;
			imesh = asM(engine->manager())->getMesh(mesh);
			if(imesh){
				meshes.push_back(imesh);
				return asM(engine->manager())->addMeshSceneNode(imesh,parent);
			}else{
				throw "There must have been an error loading!";
			}
		}
		const Mesh getMesh(const ::irr::scene::IAnimatedMesh * mesh){
			Mesh m;
			size_t total_indicies = 0, total_vertices = 0;
			for(size_t i = 0; i < mesh->getMeshBufferCount(); ++i){
				total_indicies += mesh->getMeshBuffer(i)->getIndexCount();
				total_vertices += mesh->getMeshBuffer(i)->getVertexCount();
			}
			m.second.reserve(total_indicies);
			m.first.reserve(total_vertices);
			for(size_t i = 0; i < mesh->getMeshBufferCount(); ++i){
				auto buffer = mesh->getMeshBuffer(i);
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
			return m;
		}
		const Mesh getMesh(::irr::scene::ISceneNode * node){
            auto n = reinterpret_cast<::irr::scene::IAnimatedMeshSceneNode *>(node);
			return getMesh(n->getMesh());
		}

	};
	Entity::Entity(class Engine * engine){
		_internals = new EntityInternals();
		_internals->engine = engine;
	}
	void Entity::init(const Entity_Types type, const Vec3 data){
		_internals->node = _internals->makeNode(type,data);
		_internals->node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	}
	void Entity::init(const Entity_Types type, const char * mesh){ 
		_internals->node = _internals->makeNode(type,mesh);
	}
	void Entity::init(ShapeList & shapes){
		_internals->node = asM(_internals->engine->manager())->addEmptySceneNode();
		for_each(shapes.begin(),shapes.end(),[&](ShapeList::value_type & shape){
			::irr::scene::ISceneNode * node;
			switch(shape.first.type){
				case E_CAPSULE:
				case E_SPHERE:
				case E_BAR:
				{
					node = _internals->makeNode(shape.first.type,Math::Vec4ToVec3(shape.first.data));
				}
				break;
				case E_MESH:
				{
					node = _internals->makeNode(shape.first.type,shape.first.meshFile);
					shape.first.rawMesh = _internals->getMesh(node);
				}
				break;
				default:
				{
					throw "Not valid shape type!";
				}
			}
			node->setPosition(irr::core::vector3df(
				std::tr1::get<0>(shape.second.first),
				std::tr1::get<1>(shape.second.first),
				std::tr1::get<2>(shape.second.first)
			));
			irr::core::vector3df rot;
			irr::core::quaternion quat(
				std::tr1::get<0>(shape.second.second),
				std::tr1::get<1>(shape.second.second),
				std::tr1::get<2>(shape.second.second),
				std::tr1::get<3>(shape.second.second)
				);
			quat.toEuler(rot);
			node->setRotation(rot);
			
		});
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
	void Entity::color(const Vec4 color){
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
	void Entity::setOrientation(const Vec4 vec){
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
	void Entity::setOrientation(const Vec3 vec){
		_internals->node->setRotation(irr::core::vector3df(
			std::tr1::get<0>(vec),
			std::tr1::get<1>(vec),
			std::tr1::get<2>(vec)
			));
	}
	const Mesh Entity::getMesh() const{
		return _internals->getMesh(_internals->node);
	}
}