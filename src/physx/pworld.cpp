#include <map>
#define NDEBUG
#include <PxPhysicsAPI.h> 
#include <PxExtensionsAPI.h> 
#include <PxDefaultErrorCallback.h>
#include <PxDefaultAllocator.h> 
#include <PxDefaultSimulationFilterShader.h>
#include <PxDefaultCpuDispatcher.h>
#include <PxShapeExt.h>
#include <PxSimpleFactory.h>

#include "pworld.hpp"

using namespace physx;


namespace PhysX {
	enum IndexType {
		I_UNDEFINED = 0,
		I_SHAPE,
		I_RIGID,
		I_CONSTRAINT,
		I_STATIC
	};
	inline PxVec3 convert(const Vec3 a){
		return PxVec3(
			std::tr1::get<0>(a),
			std::tr1::get<1>(a),
			std::tr1::get<2>(a)
			);
	}
	inline PxQuat convert(const Vec4 a){
		return PxQuat(
			std::tr1::get<0>(a),
			std::tr1::get<1>(a),
			std::tr1::get<2>(a),
			std::tr1::get<3>(a)
			);
	}
	inline PxTransform convert(const Transform t){
		return PxTransform(convert(t.first),convert(t.second));
	}
	class PhysXWorldInternals {
	public:
		size_t newid;
		PxPhysics * gPhysicsSDK;
		PxFoundation * foundation;
		PxDefaultErrorCallback gDefaultErrorCallback;
		PxDefaultAllocator gDefaultAllocatorCallback;
		PxSimulationFilterShader gDefaultFilterShader;
		PxScene * gScene;
		PxReal myTimestep;
		std::map<size_t, PxRigidBody*> bodies;
		std::map<size_t, PxRigidStatic*> statics;
		std::map<size_t, PxGeometry*> shapes; 
		std::map<size_t, IndexType> types;
		PxMaterial * defaultMaterial;

		PhysXWorldInternals(){
			newid = 1;
			gPhysicsSDK = NULL;
			gScene = NULL;
			myTimestep = 1.0f/60.0f;
			gDefaultFilterShader=PxDefaultSimulationFilterShader;
			foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
			bool recordMemoryAllocations = true;
			auto mProfileZoneManager = &PxProfileZoneManager::createProfileZoneManager(foundation);
			gPhysicsSDK =PxCreatePhysics(PX_PHYSICS_VERSION, *foundation,
			PxTolerancesScale(), recordMemoryAllocations, mProfileZoneManager );
			PxInitExtensions(*gPhysicsSDK);
			PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
			sceneDesc.gravity=PxVec3(0.0f, -9.8f, 0.0f);
			if(!sceneDesc.cpuDispatcher) {
				PxDefaultCpuDispatcher* mCpuDispatcher = PxDefaultCpuDispatcherCreate(1);
				sceneDesc.cpuDispatcher = mCpuDispatcher;
			} 
			if(!sceneDesc.filterShader)
				sceneDesc.filterShader  = gDefaultFilterShader;
			gScene = gPhysicsSDK->createScene(sceneDesc);
			gScene->setVisualizationParameter(PxVisualizationParameter::eSCALE,				 1.0);
			gScene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES,	1.0f);
			defaultMaterial = gPhysicsSDK->createMaterial(0.5,0.5,0.1);
			PxTransform pose = PxTransform(PxVec3(0.0f, 0, 0.0f),PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
			PxRigidStatic * plane = gPhysicsSDK->createRigidStatic(pose);
			PxShape* shape = plane->createShape(PxPlaneGeometry(), *defaultMaterial);
			gScene->addActor(*plane);

		}
		~PhysXWorldInternals(){
			//Bah, I'll think about memory later.
		}
	};
	PhysXWorld::PhysXWorld(){
		_i = new PhysXWorldInternals();
	}
	PhysXWorld::~PhysXWorld(){
		delete _i;
	}
	void PhysXWorld::tick(float delta){
		_i->gScene->simulate(delta); 
		while(!_i->gScene->fetchResults())     
		{
			// do something useful        
		}
	}
	size_t PhysXWorld::addSphere(const float radius){
		_i->types[_i->newid] = I_SHAPE;
		_i->shapes[_i->newid] = new PxSphereGeometry(radius);
		return _i->newid++;
	}
	size_t PhysXWorld::addBox(const Vec3 & dimensions){
		_i->types[_i->newid] = I_SHAPE;
		_i->shapes[_i->newid] = new PxBoxGeometry(
			std::tr1::get<0>(dimensions)/2.0,
			std::tr1::get<1>(dimensions)/2.0,
			std::tr1::get<2>(dimensions)/2.0
			);
		
		return _i->newid++;
	}
	size_t PhysXWorld::addPlane(const Vec3 & equation, const float constant){
		return _i->newid++;
	}
	size_t PhysXWorld::addMesh(const Mesh & mesh){
		return _i->newid++;
	}
	size_t PhysXWorld::addCapsule(const float length, const float radius){
		return _i->newid++;
	}
	size_t PhysXWorld::compoundShapes(::std::vector< ::std::pair<size_t, Transform> > list){
		return _i->newid++;
	}
	size_t PhysXWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
		if(mass.first <= 0) return makeStaticBody(index,trans);
		_i->types[_i->newid] = I_RIGID;
		_i->bodies[_i->newid] = PxCreateDynamic(*(_i->gPhysicsSDK),convert(trans),*(_i->shapes[index]),*(_i->defaultMaterial),1.0);
		_i->bodies[_i->newid]->setMass(mass.first);
		_i->gScene->addActor(*(_i->bodies[_i->newid]));
		return _i->newid++;
	}
	size_t PhysXWorld::makeStaticBody(const size_t index, const Transform & trans){
		_i->types[_i->newid] = I_STATIC;
		_i->statics[_i->newid] = PxCreateStatic(*(_i->gPhysicsSDK),convert(trans),*(_i->shapes[index]),*(_i->defaultMaterial));
		_i->gScene->addActor(*(_i->statics[_i->newid]));
		return _i->newid++;
	}

	size_t PhysXWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
		return _i->newid++;
	}

	void PhysXWorld::removeConstraint(size_t index){
		//PhysX world
	}
	void PhysXWorld::removeShape(size_t shape){
		//PhysX World doesn't give back shape information
	}
	void PhysXWorld::removeBody(size_t body){
		//TODO
	}

	void PhysXWorld::transformBody(const size_t index, const Transform & trans){
		//
	}
	const Transform PhysXWorld::getTransformation(const size_t index){
		Transform t;
		PxShape** shapes;
		PxU32 nShapes;
		if(_i->types[index] == I_RIGID){
 			nShapes = _i->bodies[index]->getNbShapes();
			shapes=new PxShape*[nShapes];
			_i->bodies[index]->getShapes(shapes, nShapes);  
		}
		if(_i->types[index] == I_STATIC){
			nShapes = _i->statics[index]->getNbShapes();
			shapes=new PxShape*[nShapes];
			_i->statics[index]->getShapes(shapes, nShapes);  
		}
		   
		while (nShapes--) 
		{ 
			PxShape * pShape = shapes[nShapes];
			PxTransform pT = PxShapeExt::getGlobalPose(*pShape);
			t.first = Vec3(pT.p.x, pT.p.y, pT.p.z);
			t.second = Vec4(pT.q.x, pT.q.y, pT.q.z, pT.q.w);
		} 
		delete [] shapes;
		return t;
	}
	void PhysXWorld::setVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) return;
		_i->bodies[index]->setLinearVelocity(convert(velocity));
	}
	void PhysXWorld::setAngularVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) return;
		_i->bodies[index]->setAngularVelocity(convert(velocity));
	}
	class PhysXWorldFactory : public World::EarthFactory {
	public:
		virtual World::Earth * instantiate() {
			return new PhysX::PhysXWorld();
		}
		PhysXWorldFactory(){
			World::EarthFactory::addEarth(this);
		}
		virtual const char * getName(){
			return "PhysX";
		}
	};
	static PhysXWorldFactory pxwf;

};
