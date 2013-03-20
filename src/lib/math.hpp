#pragma once
#include "vec.hpp"

namespace Math{
	const Vec3 QuaternionToEuler(Vec4);
	const Vec4 EulerToQuaternion(Vec3);
};