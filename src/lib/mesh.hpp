#pragma once
#include "vec.hpp"
#include "enums.hpp"

typedef ::std::pair< ::std::vector<Vec3>, ::std::vector<short> > Mesh;
typedef ::std::pair<Vec3,Vec4> Transform;
typedef ::std::pair<float, Vec3> MassProperties;
typedef ::std::vector< 
    ::std::tr1::tuple<bool,
		::std::pair<
			::std::pair<Entity_Types, Vec3>,
			::std::pair<Entity_Types, Mesh>
			>,
		Transform
		>
	>	ShapeList;
//The above is basically a list of shapes to create
//The first bool specifies which to use, true for meshes
//The first is used on false, for procedural shapes
//The second is used on true, for defined meshes
//The third specifies the orientation of the shape
//Since this will be a compound object.

