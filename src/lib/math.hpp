#pragma once
#include "vec.hpp"

namespace Math{
	const Vec3 QuaternionToEuler(const Vec4);
	const Vec4 EulerToQuaternion(const Vec3);
	const Vec4 Vec3ToVec4(const Vec3);
	const Vec3 Vec4ToVec3(const Vec4);
	const Scalar VecLast(const Vec4);
	const Scalar VecLast(const Vec3);
};