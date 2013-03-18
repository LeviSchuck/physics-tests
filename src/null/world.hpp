#include "lib/world.hpp"

class NullWorld : public World::Earth {
	virtual void instantiate();
    virtual void tick(float delta);
    virtual size_t addSphere(const float radius);
    virtual size_t addBar(const Vec3 & dimensions);
    virtual size_t addPlane(const Vec3 & origin, const Vec4 & orientation);
    virtual size_t addMesh(const Mesh & mesh);
    virtual size_t compoundShapes(::std::vector<size_t> list);
    virtual size_t makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans);
    virtual size_t makeStaticBody(const size_t index, const Transform & trans);
    //virtual size_t addHinge(size_t first, size_t second, );
    virtual size_t addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis);
    
    virtual void removeConstraint(size_t index);
    virtual void removeShape(size_t shape);
    virtual void removeBody(size_t body);
    
    virtual void transformBody(const size_t index, const Transform & trans);
    virtual const Transform getTransformation(const size_t index);
};