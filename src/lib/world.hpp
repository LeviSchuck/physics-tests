#pragma once
#include <vector>
#include "vec.hpp"
#include "mesh.hpp"
namespace World {
	class Earth {
	public:
		virtual void instantiate() = 0;
		virtual void tick(float delta) = 0;
		virtual size_t addSphere(const float radius) = 0;
		virtual size_t addBar(const Vec3 & dimensions) = 0;
		virtual size_t addPlane(const Vec3 & origin, const Vec4 & orientation) = 0;
		virtual size_t addMesh(const Mesh & mesh) = 0;
		virtual size_t compoundShapes(::std::vector< ::std::pair<size_t, Transform> > list) = 0;
		virtual size_t makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans) = 0;
		virtual size_t makeStaticBody(const size_t index, const Transform & trans) = 0;
		//virtual size_t addHinge(size_t first, size_t second, );
		virtual size_t addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis) = 0;

		virtual void removeConstraint(size_t index) = 0;
		virtual void removeShape(size_t shape) = 0;
		virtual void removeBody(size_t body) = 0;

		virtual void transformBody(const size_t index, const Transform & trans) = 0;
		virtual const Transform getTransformation(const size_t index) = 0;

		virtual ~Earth() {};
	};
};