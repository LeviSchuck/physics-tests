#include <map>
#define dSINGLE
#include <ode/ode.h>

#include "oworld.hpp"

namespace ODE {
	enum IndexType {
		I_UNDEFINED = 0,
		I_SHAPE,
		I_RIGID,
		I_CONSTRAINT,
		I_STATIC
	};
	enum ShapeType {
		S_UNDEFINED = 0,
		S_BOX,
		S_SPHERE
	};
    static dJointGroupID contactgroup = dJointGroupCreate(4000);
    static dWorldID stworld;
    static void nearCallback (void *data, dGeomID o1, dGeomID o2){
        dBodyID b1 = dGeomGetBody(o1);
        dBodyID b2 = dGeomGetBody(o2);
        dContact contact;
        contact.surface.mode = dContactBounce | dContactSoftCFM;
        // friction parameter
        contact.surface.mu = dInfinity;
        // bounce is the amount of "bouncyness".
        contact.surface.bounce = 0.1;
        // bounce_vel is the minimum incoming velocity to cause a bounce
        contact.surface.bounce_vel = 0.1;
        // constraint force mixing parameter
        contact.surface.soft_cfm = 0.001;
        if (int numc = dCollide (o1,o2,1,&contact.geom,sizeof(dContact))) {
            dJointID c = dJointCreateContact (stworld,contactgroup,&contact);
            dJointAttach (c,b1,b2);
        }
    }
	class ODEWorldInternals {
	public:
		dWorldID world;
		dSpaceID space;
		
		std::map<size_t, dBodyID> bodies;
		std::map<size_t, dGeomID> shapes;
		std::map<size_t, IndexType> types;
		std::map<size_t, ShapeType> shapeTypes;
        size_t newid;
        
		
		ODEWorldInternals(){
            dInitODE();
			world = dWorldCreate();
			space = dSimpleSpaceCreate(0);
            newid = 1;
			dWorldSetGravity(world, 0.0, -9.8, 0.0);
            dCreatePlane(space, 0, 1, 0, 0);
		}
		~ODEWorldInternals(){

		}

	};
	ODEWorld::ODEWorld(){
		_i = new ODEWorldInternals();
	}
	ODEWorld::~ODEWorld(){
		delete _i;
	}
	void ODEWorld::tick(float delta){
        if(delta == 0) return;
        stworld = _i->world;
        dSpaceCollide(_i->space, 0, &nearCallback);
		dWorldQuickStep(_i->world, delta);
        if(contactgroup)
            dJointGroupEmpty(contactgroup);
	}
	size_t ODEWorld::addSphere(const float radius){
		_i->types[_i->newid] = I_SHAPE;
		_i->shapes[_i->newid] = dCreateSphere(_i->space, radius);
		_i->shapeTypes[_i->newid] = S_SPHERE;
		return _i->newid++;
	}
	size_t ODEWorld::addBox(const Vec3 & dimensions){
		_i->types[_i->newid] = I_SHAPE;
		_i->shapes[_i->newid] = dCreateBox(
			_i->space,
			std::tr1::get<0>(dimensions)/2.0,
			std::tr1::get<1>(dimensions)/2.0,
			std::tr1::get<2>(dimensions)/2.0
			);
		_i->shapeTypes[_i->newid] = S_BOX;
		
		return _i->newid++;
	}
	size_t ODEWorld::addPlane(const Vec3 & equation, const float constant){
		return _i->newid++;
	}
	size_t ODEWorld::addMesh(const Mesh & mesh){
		return _i->newid++;
	}
	size_t ODEWorld::addCapsule(const float length, const float radius){
		return _i->newid++;
	}
	size_t ODEWorld::compoundShapes(::std::vector< ::std::pair<size_t, Transform> > list){
		return _i->newid++;
	}
	size_t ODEWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
		if(mass.first <= 0) return makeStaticBody(index,trans);
		_i->types[_i->newid] = I_RIGID;
		_i->bodies[_i->newid] = dBodyCreate(_i->world);
		dGeomSetBody(_i->shapes[index],_i->bodies[_i->newid]);
		dBodySetPosition(_i->bodies[_i->newid],
			std::tr1::get<0>(trans.first),
			std::tr1::get<1>(trans.first),
			std::tr1::get<2>(trans.first)
			);
        dQuaternion q = {
            (float)std::tr1::get<3>(trans.second),
            (float)std::tr1::get<0>(trans.second),
            (float)std::tr1::get<1>(trans.second),
            (float)std::tr1::get<2>(trans.second)
        };
		dBodySetQuaternion(_i->bodies[_i->newid],q);
		dMass m;
		switch(_i->shapeTypes[index]){
			case S_BOX:
			{
				dVector3 size;
				dGeomBoxGetLengths(_i->shapes[index],size);
				dMassSetBoxTotal(&m, mass.first, size[0],size[1],size[2]);
			}
			break;
			case S_SPHERE:
			{
                double rad = dGeomSphereGetRadius(_i->shapes[index]);
				dMassSetSphereTotal(&m, mass.first, rad);
			}
			break;
		}
		dBodySetMass(_i->bodies[_i->newid], &m);
		return _i->newid++;
	}
	size_t ODEWorld::makeStaticBody(const size_t index, const Transform & trans){
		//_i->types[_i->newid] = I_STATIC;
		dGeomSetPosition(_i->shapes[index],
			std::tr1::get<0>(trans.first),
			std::tr1::get<1>(trans.first),
			std::tr1::get<2>(trans.first)
			);
        dQuaternion q = {
            (float)std::tr1::get<3>(trans.second),
            (float)std::tr1::get<0>(trans.second),
            (float)std::tr1::get<1>(trans.second),
            (float)std::tr1::get<2>(trans.second)
        };
		dGeomSetQuaternion(_i->shapes[index],q);
		return index;
	}

	size_t ODEWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
		return _i->newid++;
	}

	void ODEWorld::removeConstraint(size_t index){
		//ODE world
	}
	void ODEWorld::removeShape(size_t shape){
		//ODE World doesn't give back shape information
	}
	void ODEWorld::removeBody(size_t body){
		//TODO
	}

	void ODEWorld::transformBody(const size_t index, const Transform & trans){
		//
	}
	const Transform ODEWorld::getTransformation(const size_t index){
		Transform t;
        if(_i->types[index] == I_SHAPE){
            //really a static body.
            auto d = dGeomGetPosition(_i->shapes[index]);
            t.first = Vec3(d[0],d[1],d[2]);
            dQuaternion q;
            dGeomGetQuaternion(_i->shapes[index],q);
            t.second = Vec4(q[1],q[2],q[3],q[0]);
        }
        if(_i->types[index] == I_RIGID){
            auto d = dBodyGetPosition(_i->bodies[index]);
            t.first = Vec3(d[0],d[1],d[2]);
            auto q = dBodyGetQuaternion(_i->bodies[index]);
            t.second = Vec4(q[1],q[2],q[3],q[0]);
        }
		return t;
	}
	void ODEWorld::setVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) return;
		dBodySetLinearVel(_i->bodies[index],
			std::tr1::get<0>(velocity),
			std::tr1::get<1>(velocity),
			std::tr1::get<2>(velocity)
			);
	}
	void ODEWorld::setAngularVelocity(const size_t index, const Vec3 velocity){
		if(_i->types[index] != I_RIGID) return;
		dBodySetAngularVel(_i->bodies[index],
			std::tr1::get<0>(velocity),
			std::tr1::get<1>(velocity),
			std::tr1::get<2>(velocity)
			);
	}
	class ODEWorldFactory : public World::EarthFactory {
	public:
		virtual World::Earth * instantiate() {
			return new ODE::ODEWorld();
		}
		ODEWorldFactory(){
			World::EarthFactory::addEarth(this);
		}
		virtual const char * getName(){
			return "ODE";
		}
	};
	static ODEWorldFactory owf;
};