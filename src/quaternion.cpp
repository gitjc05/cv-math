#include "quaternion.h"
#include "vec3.h"

quaternion::quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

quaternion::~quaternion() {};

void quaternion::inverse()
{
	w *= -1;
}

quaternion quaternion::operator+(const quaternion& other)
{
	quaternion result(other.x + x, other.y + y, other.z + z, other.w + w);
	return result;
}

quaternion quaternion::operator+(const float& offset)
{
	quaternion result(offset + x, offset + y, offset + z, offset + w);
	return result;
}

quaternion quaternion::operator*(const quaternion& other)
{
	vec3<float> v0(x, y, z);
	vec3<float> v1(other.x, other.y, other.z);
	float w0 = w;
	float w1 = other.w;

	vec3<float> v2 = v0.cross(v1);
	v2 = v2 + (v0 * w1) + (v1 * w0);
	float w2 = w0 * w1 - v0.dot(v1);
	quaternion result(v2.x, v2.y, v2.z, w2);
	return result;
}
