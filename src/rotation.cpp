#include "rotation.h"
#include <math.h>


namespace Rotation
{

	Quaternion PointQuaternion(Vec3<float>& v)
	{
		Quaternion result(v.x, v.y, v.z, 0.0f);
		return result;
	}

	Quaternion GetRotationQuaternion(Vec3<float>& n, float theta)
	{
		Vec3<float> v;
		float s = sinf(TORAD(theta/2.0f));
		v = n * s;
		float w = cosf(TORAD(theta/2.0f));

		Quaternion q(v.x, v.y, v.z, w);
		return q;
	}

	Quaternion QuaternionRotate(Quaternion& p, Quaternion& q)
	{
		Quaternion qInverse;
		q.CopyTo(qInverse);
		qInverse.Inverse();
		Quaternion p2 = q * p;
		p2 = p2 * qInverse;
		return p2;
	}

	Vec3<float> VecQuatRot(Vec3<float>& p, Vec3<float>& n, float theta)
	{
		Quaternion q = GetRotationQuaternion(n, theta);
		Quaternion p0 = PointQuaternion(p);
		Quaternion p1 = QuaternionRotate(p0, q);

		Vec3<float> result(p1.x, p1.y, p1.z);
		return result;
	}

	Quaternion Slerp(Quaternion& q1, Quaternion& q2, float a)
	{
		float qDot = q1.Dot(q2);

		float thetaR = acos(qDot);
		float sinTheta = sin(thetaR);

		float s1 = sin((1 - a) * thetaR) / sinTheta;
		float s2 = sin(a * thetaR) / sinTheta;
		return (q1 * s1) + (q2 * s2);
	}
}