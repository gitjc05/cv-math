#include <gtest/gtest.h>
#include "quaternion.h"
#include "vec3.h"
#include "complex.h"

TEST(ComplexTests, Equality)
{
	Complex c1(1.0, 2.0);
	Complex c1_eq(1.0, 2.0);
	Complex c2(4.0, 1.0);

	EXPECT_TRUE(c1.IsEqual(c1_eq));
	EXPECT_TRUE(c1_eq.IsEqual(c1));
	EXPECT_FALSE(c1.IsEqual(c2));

}

TEST(ComplexTests, Addition)
{
	Complex c1(1.0, 2.0);
	Complex c2(4.0, 1.0);

	Complex result(5.0, 3.0);

	Complex sum = c1 + c2;

	EXPECT_TRUE(result.IsEqual(sum));
	EXPECT_FALSE(c1.IsEqual(sum));

	Complex sum2 = c2 - result;

	EXPECT_FALSE(result.IsEqual(sum2));
	result.r = -1.0f;
	result.j = -2.0f;
	EXPECT_TRUE(result.IsEqual(sum2));
}

TEST(Vec3Tests, Equality)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	Vec3<float> t1(x, y, z);
	Vec3<float> t2(x, y, z);

	bool equality_result = t1.Equals(t2);

	EXPECT_TRUE(equality_result);

	t1.x -= 0.22f;
	t2.x -= 0.22f;
	equality_result = t1.Equals(t2);
	EXPECT_TRUE(equality_result);

	t2.x += 0.0001;
	equality_result = t1.Equals(t2);
	EXPECT_FALSE(equality_result);

	t2 = Vec3<float>(x1, y1, z1);
	equality_result = t1.Equals(t2);
	EXPECT_FALSE(equality_result);

	t1.x = x1; t1.y = y1; t1.z = z1;
	equality_result = t1.Equals(t2);
	EXPECT_TRUE(equality_result);
}

TEST(Vec3Tests, Adding)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	Vec3<float> test1(x, y, z);
	Vec3<float> test2(x1, y1, z1);
	Vec3<float> add_result1 = test1 + test2;
	Vec3<float> add_result2 = test2 + test1;

	EXPECT_TRUE(add_result1.x == x + x1);
	EXPECT_TRUE(add_result1.y == y + y1);
	EXPECT_TRUE(add_result1.z == z + z1);

	EXPECT_TRUE(add_result2.Equals(add_result1));
	add_result1 = add_result1 + 5.0f;
	add_result2 = add_result2 + (-6.5f);
	EXPECT_FALSE(add_result1.Equals(add_result2));
}

TEST(Vec3Tests, Multiplying)
{
	std::vector<float> xIns = { 0.5f, 1.0f, 2.0f, 2000.0f, 123103.0f, 0.5f, 0.1f, 10.0f, 10800.0f, 12.6f };
	std::vector<float> yIns = { 0.123f, 1230.0f, 13.3f, 0.222f, 0.2223f, 123.0f, 8376.0f, 1.002f, 22.02201f, 1.6f };
	std::vector<float> zIns = { 0.14f, 0.3123f, 0.324f, 1.23f, 3.44f, 3.14f, 2.17f, 1.203f, 303.0f, 67.420f };


	for (int i = 0; i < 5; i++)
	{
		Vec3 result(xIns[i] * xIns[i + 5], yIns[i] * yIns[i + 5], zIns[i] * zIns[i + 5]);
		Vec3 m1(xIns[i], yIns[i], zIns[i]);
		Vec3 m2(xIns[i + 5], yIns[i + 5], zIns[i + 5]);
		Vec3 product = m1 * m2;
		EXPECT_TRUE(product.Equals(result));
		EXPECT_FALSE(product.Equals(m1));
		EXPECT_FALSE(product.Equals(m2));
	}
}

TEST(QuaternionTests, Inverse)
{
	EXPECT_TRUE(true);

	int x = 1;
	int y = 0.2;
	int z = 0.2;
	int w = 1;
	Quaternion q(1, 0, 0, w);


	q.Inverse();
	EXPECT_EQ(q.x, -x);
	EXPECT_EQ(q.y, -y);
	EXPECT_EQ(q.z, -z);


	q.RotateInverse();
	EXPECT_EQ(q.w, -w);
	q.RotateInverse();
	EXPECT_EQ(q.w, w);
	q.Inverse();
	EXPECT_EQ(q.x, x);
	EXPECT_EQ(q.y, y);
	EXPECT_EQ(q.z, z);

}
