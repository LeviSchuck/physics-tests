#include <math.h>
#include "math.hpp"

namespace Math{
	const Vec3 QuaternionToEuler(const Vec4 quat){
		Vec3 vec;
		double x,y,z,w;
		double yaw,pitch,roll;

		x = std::tr1::get<0>(quat);
		y = std::tr1::get<1>(quat);
		z = std::tr1::get<2>(quat);
		w = std::tr1::get<3>(quat);

		yaw = atan2(2.0*y*w - 2.0*x*z, 1.0 - 2.0*y*y - 2.0*z*z);
		pitch = asin(2.0*x*y + 2.0*z*w);
		roll = atan2(2.0*x*w - 2.0*y*z, 1.0 - 2.0*x*x - 2.0*z*z);
		//adjust for deg here if needed, currently in radians
		std::tr1::get<0>(vec) = yaw;
		std::tr1::get<1>(vec) = pitch;
		std::tr1::get<2>(vec) = roll;
		return vec;
	}
	const Vec4 EulerToQuaternion(const Vec3 vec){
		double x,y,z,w;
		double c1,c2,c3;
		double s1,s2,s3;
		double yaw,pitch,roll;
		Vec4 quat;

		yaw = std::tr1::get<0>(vec);
		pitch = std::tr1::get<1>(vec);
		roll = std::tr1::get<2>(vec);
		//Adjust for deg here if needed
		//The rest assumes radians
		c1 = cos(yaw/2.0);
		c2 = cos(pitch/2.0);
		c3 = cos(roll/2.0);
		s1 = sin(yaw/2.0);
		s2 = sin(pitch/2.0);
		s3 = sin(roll/2.0);

		w = c1*c2*c3 - s1*s2*s3;
		x = s1*s2*c3 + c1*c2*s3;
		y = s1*c2*c3 + c1*s2*s3;
		z = c1*s2*c3 - s1*c2*s3;

		std::tr1::get<0>(quat) = x;
		std::tr1::get<1>(quat) = y;
		std::tr1::get<2>(quat) = z;
		std::tr1::get<3>(quat) = w;
		return quat;
	}
	const Vec4 Vec3ToVec4(const Vec3 v){
		Vec4 r;
		std::tr1::get<0>(r) = std::tr1::get<0>(v);
		std::tr1::get<1>(r) = std::tr1::get<1>(v);
		std::tr1::get<2>(r) = std::tr1::get<2>(v);
		return r;
	}
	const Vec3 Vec4ToVec3(const Vec4 v){
		Vec3 r;
		std::tr1::get<0>(r) = std::tr1::get<0>(v);
		std::tr1::get<1>(r) = std::tr1::get<1>(v);
		std::tr1::get<2>(r) = std::tr1::get<2>(v);
		return r;
	}
	const Scalar VecLast(const Vec4 v){
		return std::tr1::get<3>(v);
	}
	const Scalar VecLast(const Vec3 v){
		return std::tr1::get<2>(v);
	}

};