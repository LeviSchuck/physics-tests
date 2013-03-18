#include "world.hpp"
void NullWorld::instantiate(){

}
void NullWorld::tick(float delta){

}
size_t NullWorld::addSphere(const float radius){
	return 1;
}
size_t NullWorld::addBar(const Vec3 & dimensions){
	return 1;
}
size_t NullWorld::addPlane(const Vec3 & origin, const Vec4 & orientation){
	return 1;
}
size_t NullWorld::addMesh(const Mesh & mesh){
	return 1;
}
size_t NullWorld::compoundShapes(::std::vector<size_t> list){
	return 1;
}
size_t NullWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
	return 1;
}
size_t NullWorld::makeStaticBody(const size_t index, const Transform & trans){
	return 1;
}

size_t NullWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
	return 1;
}

void NullWorld::removeConstraint(size_t index){

}
void NullWorld::removeShape(size_t shape){

}
void NullWorld::removeBody(size_t body){

}

void NullWorld::transformBody(const size_t index, const Transform & trans){

}
const Transform NullWorld::getTransformation(const size_t index){
	static Transform t(Vec3(0,0,0),Vec4(0,0,0,1));
	return t;
}