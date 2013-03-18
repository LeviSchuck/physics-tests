#include "world.hpp"
void Bullet::BulletWorld::instantiate(){

}
void Bullet::BulletWorld::tick(float delta){

}
size_t Bullet::BulletWorld::addSphere(const float radius){
	return 1;
}
size_t Bullet::BulletWorld::addBar(const vec3 & dimensions){
	return 1;
}
size_t Bullet::BulletWorld::addPlane(const vec3 & origin, const vec4 & orientation){
	return 1;
}
size_t Bullet::BulletWorld::addMesh(const Mesh & mesh){
	return 1;
}
size_t Bullet::BulletWorld::compoundShapes(::std::vector<size_t> list){
	return 1;
}
size_t Bullet::BulletWorld::makeRigidBody(const size_t index, const MassProperties & mass, const Transform & trans){
	return 1;
}
size_t Bullet::BulletWorld::makeStaticBody(const size_t index, const Transform & trans){
	return 1;
}

size_t Bullet::BulletWorld::addPoint2Point(size_t first, size_t second, const Vec3 firstAxis, const Vec3 secondAxis){
	return 1;
}

void Bullet::BulletWorld::removeConstraint(size_t index){

}
void Bullet::BulletWorld::removeShape(size_t shape){

}
void Bullet::BulletWorld::removeBody(size_t body){

}

void Bullet::BulletWorld::transformBody(const size_t index, const Transform & trans){

}
const Transform Bullet::BulletWorld::getTransformation(const size_t index){
	static Transform t(Vec3(0,0,0),Vec4(0,0,0,1));
	return t;
}