#pragma once
#include <format>
#include <iostream>

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	~Quaternion();

	Quaternion operator+(const Quaternion& other);
	Quaternion operator+(const float& offset);
	Quaternion operator-(const Quaternion& other);
	Quaternion operator*(const Quaternion& other);
	Quaternion operator*(const float& scale);
	Quaternion operator/(const Quaternion& other);
	void Inverse();
	void RotateInverse();
	void CopyTo(Quaternion& q2);
	bool Equals(Quaternion& other);
	void Display();
	float Dot(Quaternion& q2);
};

