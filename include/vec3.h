#pragma once

#define EPS 0.00001f
#include <string>
#include <iostream>
#include <format>
#include <math.h>

template <typename T> class Vec3
{
public:
	T x;
	T y;
	T z;

	Vec3(T x, T y, T z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vec3() {}


	bool Equals(const Vec3<T>& other) const
	{
		return (fabs(other.x - x) <= EPS) && (fabs(other.y - y) <= EPS) && (fabs(other.z - z) <= EPS);
	}

	Vec3<T> operator+(const Vec3<T>& other) const
	{
		Vec3<T> result(x + other.x, y + other.y, z + other.z);
		return result;
	}

	Vec3<T> operator-(const Vec3<T>& other) const
	{
		Vec3<T> result(x - other.x, y - other.y, z - other.z);
		return result;
	}

	Vec3<T> operator*(const Vec3<T>& other) const
	{
		Vec3<T> result(x * other.x, y * other.y, z * other.z);
		return result;
	}

	Vec3<T> operator+(const T& offset) const
	{
		Vec3<T> result(offset + x, offset + y, offset + z);
		return result;
	}

	Vec3<T> operator*(const T& scale) const
	{
		Vec3<T> result(scale * x, scale * y, scale * z);
		return result;
	}

	T Dot(Vec3<T>& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	Vec3<T> Cross(Vec3<T>& other) const
	{
		Vec3<T> result(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
		return result;
	}

	void CopyTo(Vec3<T>& other) const
	{
		other.x = x;
		other.y = y;
		other.z = z;
	}

	void Normalize() const 
	{
		T mag = this->Magnitude();
		x /= Magnitude;
		y /= Magnitude;
		z /= Magnitude;
	}

	T Magnitude() const
	{
		T magnitude = x * x + y * y + z * z;
		magnitude = sqrt(magnitude);
		return magnitude;
	}

	void Display()
	{
		std::cout << std::format("[ {:3f}, {:3f}, {:3f} ]", x, y, z) << std::endl;
	}
};
