#include "quaternion.h"

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
