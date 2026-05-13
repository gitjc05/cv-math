#include <gtest/gtest.h>
#include "quaternion.h"
#include "vec3.h"


TEST(Vec3, Equality)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	vec3 t1(x, y, z);
	vec3 t2(x, y, z);

	bool equality_result = t1.equals(t2);

	ASSERT_TRUE(equality_result);

	t1.x -= 0.22f;
	t2.x -= 0.22f;
	equality_result = t1.equals(t2);
	ASSERT_TRUE(equality_result);

	t2.x += 0.00001;
	equality_result = t1.equals(t2);
	ASSERT_FALSE(equality_result);

	t2 = vec3(x1, y1, z1);
	equality_result = t1.equals(t2);
	ASSERT_FALSE(equality_result);

	t1.x = x1; t1.y = y1; t1.z = z1;
	equality_result = t1.equals(t2);
	ASSERT_TRUE(equality_result);
}

TEST(Vec3, Adding)
{
	float x = 12.22, y = -209.0, z = 20.0f;
	float x1 = 20.0f, y1 = 304.09, z1 = 900.234;

	vec3 test1(x, y, z);
	vec3 test2(x1, y1, z1);
	vec3 add_result1 = test1 + test2;
	vec3 add_result2 = test2 + test1;

	ASSERT_TRUE(add_result1.x == x + x1);
	ASSERT_TRUE(add_result1.y == y + y1);
	ASSERT_TRUE(add_result1.z == z + z1);

	ASSERT_TRUE(add_result2.equals(add_result1));
	add_result1 = add_result1 + 5.0f;
	add_result2 = add_result2 + (-6.5f);
	ASSERT_FALSE(add_result1.equals(add_result2));
}

TEST(Quaternion, Inverse)
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
