#pragma once
#include "vec3.h"
#include "quaternion.h"
#include <math.h>

#define TORAD(x) ((x) * (3.1416 / 180.0f))

namespace Rotation
{
	
	Quaternion PointQuaternion(Vec3<float>& v);
	Quaternion GetRotationQuaternion(Vec3<float>& n, float theta);
	Quaternion QuaternionRotate(Quaternion& p, Quaternion& q);
	Quaternion Slerp(Quaternion& q1, Quaternion& q2, float a);
	Vec3<float> VecQuatRot(Vec3<float>& p, Vec3<float>& n, float theta);
}