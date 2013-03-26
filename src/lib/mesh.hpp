#pragma once
#include "vec.hpp"
#include "enums.hpp"

typedef ::std::pair< ::std::vector<Vec3>, ::std::vector<short> > Mesh;
typedef ::std::pair<Vec3,Vec4> Transform;
typedef ::std::pair<float, Vec3> MassProperties;
class Shape {
public:
	Entity_Types type;
	Vec4 data;
	Mesh rawMesh;
	char * meshFile;
	Shape():meshFile(NULL){};
};
typedef ::std::vector< 
    ::std::pair<Shape, Transform>
	>	ShapeList;


