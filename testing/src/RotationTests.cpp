#include <gtest/gtest.h>
#include "rotation.h"



TEST(RotationTests, QuaternionRotation)
{
	Vec3<float> p0(1.0f, 2.0f, 0.0f);
	float theta = 90.0f;
	Vec3<float> zAxis(0.0f, 0.0f, 1.0f);
	Vec3<float> expectedP1(-2.0f, 1.0f, 0.0f);

	Vec3<float> p1 = Rotation::VecQuatRot(p0, zAxis, theta);
	p1.Display();
	EXPECT_TRUE(p1.Equals(expectedP1));
}

TEST(RotationTests, slerp)
{
	Vec3<float> p0(1.0f, 2.0f, 0.0f);
	float theta1 = 30.0f;
	float thetaMid = 60.0f;
	float theta2 = 90.0f;
	Vec3<float> zAxis(0.0f, 0.0f, 1.0f);

	Quaternion q1 = Rotation::GetRotationQuaternion(zAxis, theta1);
	Quaternion q2 = Rotation::GetRotationQuaternion(zAxis, theta2);
	Quaternion expectedMidway = Rotation::GetRotationQuaternion(zAxis, thetaMid);

	Quaternion qmid = Rotation::Slerp(q1, q2, 0.5f);
	qmid.Display();
	expectedMidway.Display();
	EXPECT_TRUE(qmid.Equals(expectedMidway));





}