#include <map>
#define BT_USE_DOUBLE_PRECISION
#include <bullet/btBulletDynamicsCommon.h>
#include <bullet/btBulletCollisionCommon.h>
#include "bworld.hpp"
#include <iostream>
namespace Bullet{
	inline btVector3 convert(const Vec3 a){
		return btVector3(
			std::tr1::get<0>(a),
			std::tr1::get<1>(a),
			std::tr1::get<2>(a)
			);
	}
	inline btQuaternion convert(const Vec4 a){
		return btQuaternion(
			std::tr1::get<0>(a),
			std::tr1::get<1>(a),
			std::tr1::get<2>(a),
			std::tr1::get<3>(a)
			);
	}
	inline btTransform convert(const Transform t){
		return btTransform(convert(t.second),convert(t.first));
	}
	enum IndexType {
		I_UNDEFINED = 0,
		I_SHAPE,
		I_RIGID,
		I_CONSTRAINT,
		I_STATIC
	};
	class BulletWorldInternals {
	public:
		size_t newid;
		btDiscreteDynamicsWorld * bt_world;
		btBroadphaseInterface * bt_broadphase;
		btDefaultCollisionConfiguration * bt_collisionConfig;
		btCollisionDispatcher * bt_dispatcher;
		btSequentialImpulseConstraintSolver * bt_solver;
		std::map<size_t, IndexType> types;
		std::map<size_t, btCollisionShape*> shapes;
		std::map<size_t, btRigidBody*> rigid_bodies;
		std::map<size_t, btTypedConstraint*> constraints;


		BulletWorldInternals(){
			newid = 1;
			bt_broadphase = new btAxisSweep3(
				btVector3(-10000, -10000, -10000),
				btVector3(10000, 10000, 10000)
				);
			bt_collisionConfig = new btDefaultCollisionConfiguration();
			bt_dispatcher = new btCollisionDispatcher(bt_collisionConfig);
			bt_solver = new btSequentialImpulseConstraintSolver();
			if(bt_broadphase && bt_collisionConfig && bt_dispatcher && bt_solver){
				bt_world = new btDiscreteDynamicsWorld(
					bt_dispatcher,
					bt_broadphase,
					bt_solver,
					bt_collisionConfig
					);
				bt_world->setGravity(btVector3(0,-9.8,0));
			}
		}
		~BulletWorldInternals(){
			if(bt_world)
				delete bt_world;
			if(bt_solver)
				delete bt_solver;
			if(bt_dispatcher)
				delete bt_dispatcher;
			if(bt_collisionConfig)
				delete bt_collisionConfig;
			if(bt_broadphase)
				delete bt_broadphase;
		}
	};
	BulletWorld::BulletWorld(){
		_i = new BulletWorldInternals();
		size_t platform = addPlane(Vec3(0,1,0),1);
		size_t platformbody = makeStaticBody(platform, Transform(Vec3(0,0,0),Vec4(0,0,0,1)));
	}
	BulletWorld::~BulletWorld(){
		delete _i;
	}
	void BulletWorld::tick(float delta){
		_i->bt_world->stepSimulation(delta);
	}
	size_t BulletWorld::addSphere(const float radius){
		btSphereShape * sphere = new btSphereShape(radius);
		_i->shapes[_i->newid] = sphere;
		_i->types[_i->newid] = I_SHAPE;
		return _i->newid++;
	}
	size_t BulletWorld::addBox(const Vec3 & dimensions){
		btBoxShape *box = new btBoxShape(convert(dimensions)/2.0);
		_i->shapes[_i->newid] = box;
		_i->types[_i->newid] = I_SHAPE;
		return _i->newid++;
	}
	size_t BulletWorld::addPlane(const Vec3 & equation, const float constant){
		btStaticPlaneShape * s = new btStaticPlaneShape(convert(equation),constant);
		_i->shapes[_i->newid] = s;
		_i->types[_i->newid] = I_SHAPE;
		return _i->newid++;
	}
	size_t BulletWorld::addMesh(const Mesh & mesh){
		return 0;
		//return _i->newid++;
	}
	size_t BulletWorld::addCapsule(const float length, const float radius){
		btCapsuleShape *capsule = new btCapsuleShape(radius, length);
		_i->shapes[_i->newid] = capsule;
		_i->types[_i->newid] = I_SHAPE;
		return _i->newid++;
	}
	size_t BulletWorld::compoundShapes(::std::vector< ::std::pair<size_t, Transform> > list){
		return 0;
		//return _i->newid++;
	}
	size_t BulletWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
		if(_i->types[index] != I_SHAPE) throw "Index does not provide a shape.";
		btCollisionShape * shape = _i->shapes[index];
		btVector3 localInertia(0,0,0);
		shape->calculateLocalInertia(mass.first,localInertia);

		btDefaultMotionState * myMotionState;
		myMotionState = new btDefaultMotionState(convert(trans));
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass.first,myMotionState,shape,localInertia);
		btRigidBody *rb = new btRigidBody(rbInfo);
		_i->rigid_bodies[_i->newid] = rb;
		_i->bt_world->addRigidBody(rb);
		_i->types[_i->newid] = I_RIGID;
		return _i->newid++;
	}
	size_t BulletWorld::makeStaticBody(const size_t index, const Transform & trans){
		if(_i->types[index] != I_SHAPE) throw "Index does not provide a shape.";
		btCollisionShape * shape = _i->shapes[index];
		btDefaultMotionState * boundMotionState = new btDefaultMotionState(convert(trans));
		btRigidBody::btRigidBodyConstructionInfo boundRigidBodyCI(0,boundMotionState,shape);
		btRigidBody * rb = new btRigidBody(boundRigidBodyCI);
		_i->rigid_bodies[_i->newid] = rb;
		_i->bt_world->addRigidBody(rb);
		_i->types[_i->newid] = I_STATIC;
		return _i->newid++;
	}
	size_t BulletWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
		return 0;
		//return _i->newid++;
	}
	
	void BulletWorld::removeConstraint(size_t index){
		//Not implemented yet
	}
	void BulletWorld::removeShape(size_t index){
		if(_i->types[index] != I_SHAPE) throw "Index does not provide a shape.";
		_i->types[index] = I_UNDEFINED;
		delete _i->shapes[index];
		_i->shapes.erase(index);
	}
	void BulletWorld::removeBody(size_t index){
		if(!(_i->types[index] == I_RIGID || _i->types[index] == I_STATIC)) throw "Index does not provide a body.";
		_i->types[index] = I_UNDEFINED;
		delete _i->rigid_bodies[index];
		_i->rigid_bodies.erase(index);
	}
	
	void BulletWorld::transformBody(const size_t index, const Transform & trans){
		if(!(_i->types[index] == I_RIGID || _i->types[index] == I_STATIC)) throw "Index does not provide a body.";

		_i->rigid_bodies[index]->setCenterOfMassTransform(convert(trans));
	}
	const Transform BulletWorld::getTransformation(const size_t index){
		if(!(_i->types[index] == I_RIGID || _i->types[index] == I_STATIC)) throw "Index does not provide a body.";
		Transform t;
		auto pos = _i->rigid_bodies[index]->getCenterOfMassPosition();
		auto quat = _i->rigid_bodies[index]->getOrientation().normalized();
		t.first = Vec3(pos.getX(),pos.getY(),pos.getZ());
		t.second = Vec4(quat.getX(),quat.getY(),quat.getZ(),quat.getW());
		/*std::cout << "Body Inertia: ";
		std::cout 
			<< quat.getX() << ", " 
			<< quat.getY() << ", "
			<< quat.getZ() << std::endl;*/
		return t;
	}
	void BulletWorld::setVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) throw "Index does not provide a body.";
		auto v = convert(velocity);
		_i->rigid_bodies[index]->setLinearVelocity(v);
	}
	void BulletWorld::setAngularVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) throw "Index does not provide a body.";
		auto v = convert(velocity);
		_i->rigid_bodies[index]->setAngularVelocity(v);
	}
};
class BulletWorldFactory : public World::EarthFactory {
public:
    virtual World::Earth * instantiate() {
        return new Bullet::BulletWorld();
    }
    BulletWorldFactory(){
        World::EarthFactory::addEarth(this);
    }
    virtual const char * getName(){
    	return "Bullet Physics 2.8";
    }
};
static BulletWorldFactory bwf28;