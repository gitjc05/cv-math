#pragma once


class quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	~quaternion();

	quaternion operator+(const quaternion& other);
	quaternion operator+(const float& offset);
	quaternion operator-(const quaternion& other);
	quaternion operator*(const quaternion& other);
	quaternion operator/(const quaternion& other);
	void inverse();

};

