#include "vec3.h"
#include <math.h>

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

bool vec3::equals(const vec3& other)
{
	return (fabs(other.x - x) <= EPS) && (fabs(other.y - y) <= EPS) && (fabs(other.z - z) <= EPS);
}

vec3 vec3::operator+(const vec3& other)
{
	vec3 result(x + other.x, y + other.y, z + other.z);
	return result;
}

vec3 vec3::operator-(const vec3& other)
{
	vec3 result(x - other.x, y - other.y, z - other.z);
	return result;
}

vec3 vec3::operator*(const vec3& other)
{
	vec3 result(x * other.x, y * other.y, z * other.z);
	return result;
}

vec3 vec3::operator+(const float& offset)
{
	vec3 result(offset + x, offset + y, offset + z);
	return result;
}

vec3 vec3::operator*(const float& scale)
{
	vec3 result(scale * x, scale * y, scale * z);
	return result;
}

float vec3::dot(vec3& other)
{
	return (x * other.x) + (y * other.y) + (z * other.z);
}