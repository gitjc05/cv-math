#include "quaternion.h"
#include "vec3.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternion::~Quaternion() {};

void Quaternion::Inverse()
{
	x = -x;
	y = -y;
	z = -z;
}

void Quaternion::RotateInverse()
{
	w = -w;
}

void Quaternion::CopyTo(Quaternion& q2)
{
	q2.x = x;
	q2.y = y;
	q2.z = z;
	q2.w = w;
}

Quaternion Quaternion::operator+(const Quaternion& other)
{
	Quaternion result(other.x + x, other.y + y, other.z + z, other.w + w);
	return result;
}

Quaternion Quaternion::operator+(const float& offset)
{
	Quaternion result(offset + x, offset + y, offset + z, offset + w);
	return result;
}

Quaternion Quaternion::operator*(const Quaternion& other)
{
	Vec3<float> v0(x, y, z);
	Vec3<float> v1(other.x, other.y, other.z);
	float w0 = w;
	float w1 = other.w;

	Vec3<float> v2 = v0.Cross(v1);
	v2 = v2 + (v0 * w1) + (v1 * w0);
	float w2 = w0 * w1 - v0.Dot(v1);
	Quaternion result(v2.x, v2.y, v2.z, w2);
	return result;
}

Quaternion Quaternion::operator*(const float& scale)
{
	return Quaternion(
		scale * x,
		scale * y,
		scale * z,
		scale * w
	);
}

Quaternion Quaternion::operator/(const Quaternion& other)
{
	Quaternion qi(-other.x, -other.y, -other.z, other.w);
	Quaternion q;
	CopyTo(q);
	return q * qi;
}

bool Quaternion::Equals(Quaternion& other)
{
	return (fabs(other.x - x) <= EPS) && (fabs(other.y - y) <= EPS) && (fabs(other.z - z) <= EPS) && (fabs(other.w - w) <= EPS);
}

void Quaternion::Display()
{
	std::cout << std::format("[ {:3f}, {:3f}, {:3f}, {:3f} ]", x, y, z, w) << std::endl;
}

float Quaternion::Dot(Quaternion& q2)
{
	return x * q2.x + y * q2.y + z * q2.z + w * q2.w;
}