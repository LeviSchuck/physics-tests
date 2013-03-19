#pragma once
#include <tr1/tuple>
#include <vector>

typedef ::std::tr1::tuple<float,float,float> Vec3;
typedef ::std::tr1::tuple<float,float,float,float> Vec4;
typedef ::std::pair< ::std::vector<Vec3>, ::std::vector<short> > Mesh;
typedef ::std::tr1::tuple<Vec3,Vec4> Transform;
typedef ::std::tr1::tuple<float, Vec3> MassProperties;
