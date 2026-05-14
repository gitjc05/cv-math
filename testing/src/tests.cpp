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
}

TEST(Vec3Tests, Equality)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	vec3<float> t1(x, y, z);
	vec3<float> t2(x, y, z);

	bool equality_result = t1.equals(t2);

	ASSERT_TRUE(equality_result);

	t1.x -= 0.22f;
	t2.x -= 0.22f;
	equality_result = t1.equals(t2);
	ASSERT_TRUE(equality_result);

	t2.x += 0.00001;
	equality_result = t1.equals(t2);
	ASSERT_FALSE(equality_result);

	t2 = vec3<float>(x1, y1, z1);
	equality_result = t1.equals(t2);
	ASSERT_FALSE(equality_result);

	t1.x = x1; t1.y = y1; t1.z = z1;
	equality_result = t1.equals(t2);
	ASSERT_TRUE(equality_result);
}

TEST(Vec3Tests, Adding)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	vec3<float> test1(x, y, z);
	vec3<float> test2(x1, y1, z1);
	vec3<float> add_result1 = test1 + test2;
	vec3<float> add_result2 = test2 + test1;

	ASSERT_TRUE(add_result1.x == x + x1);
	ASSERT_TRUE(add_result1.y == y + y1);
	ASSERT_TRUE(add_result1.z == z + z1);

	ASSERT_TRUE(add_result2.equals(add_result1));
	add_result1 = add_result1 + 5.0f;
	add_result2 = add_result2 + (-6.5f);
	ASSERT_FALSE(add_result1.equals(add_result2));
}

TEST(QuaternionTests, Inverse)
{
	EXPECT_TRUE(true);

	int x = 1;
	int y = 0;
	int z = 0;
	int w = 1;
	quaternion q(1, 0, 0, w);

	q.inverse();
	ASSERT_EQ(q.w, -w);
	q.inverse();
	ASSERT_EQ(q.w, w);
}
